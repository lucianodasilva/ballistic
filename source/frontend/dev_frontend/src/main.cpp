
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.graphics.render_list.h>

#include <map>
#include <chrono>
#include <limits>

using namespace ballistic;

ballistic::ifrontend *			_frontend;
ballistic::graphics::idevice *	_device;

ballistic::graphics::imesh *	_mesh;

#ifdef BALLISTIC_OS_WINDOWS
#	include "ballistic.win_frontend.h"

ballistic::ifrontend * create_frontend ( const point & size ) {
	return new ballistic::win_desktop::frontend (size);
}

#elif defined (BALLISTIC_OS_DARWIN)
#	include "ballistic.mac_frontend.h"
#	include <GLUT/GLUT.h>
ballistic::ifrontend * create_frontend (const point & size) {
	return new ballistic::mac_desktop::frontend (size);
}
#endif

#ifdef BALLISTIC_DESKTOP_GL
#	include <ballistic.graphics.opengl.h>

ballistic::graphics::idevice * create_device () {
	return new ballistic::graphics::opengl_device ();
}

#endif

ballistic::res_id_t res_rig ("rigged.entity", "resources/rigging.xml");
ballistic::res_id_t res_overlay_text ("overlay_text.entity", "resources/rigging.xml");
ballistic::res_id_t res_camera ("camera.entity", "resources/rigging.xml");

ballistic::res_id_t res_default_material ("default_material.effect", "resources/default_material.fx");
ballistic::res_id_t res_overlay_material ("overlay_material.effect", "resources/overlay_material.fx");

struct dual_quat {

	quat d;
	quat r;

	inline vec3 transform (const vec3 & v) const {
		return
		(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w + d.xyz) + d.xyz * r.w - r.xyz * d.w) * real (2) + v;
		//v +
		//(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w) * real (2)) +
		//((d.xyz * r.w) - (r.xyz * d.w) + (math::cross (r.xyz, d.xyz)) * real (2));
	}

	inline static dual_quat blend (const dual_quat & q1, const dual_quat & q2, real weight) {
		return {
			math::lerp (q1.d, q2.d, weight),
			math::lerp (q1.r, q2.r, weight)
		};
	}

	inline static dual_quat from_matrix (const mat4 & m ) {

		quat real_q;

		real const trace = m.m00 + m.m05 + m.m10;

		if (trace > real (0)) {
			real const r = std::sqrt (real (1) + trace);
			real const invr = real (0.5) / r;
			real_q.w = real (0.5) * r;
			real_q.x = (m.m06 - m.m09) * invr;
			real_q.y = (m.m08 - m.m02) * invr;
			real_q.z = (m.m01 - m.m04) * invr;
		} else if (m.m00 > m.m05 && m.m00 > m.m10 ) {
			real const r = std::sqrt (real (1) + m.m00 - m.m05 - m.m10);
			real const invr = real (0.5) / r;
			real_q.x = real (0.5) * r;
			real_q.y = (m.m01 + m.m04) * invr;
			real_q.z = (m.m08 + m.m02) * invr;
			real_q.w = (m.m06 - m.m09) * invr;
		} else if (m.m05 > m.m10) {
			real const r = std::sqrt (real (1) + m.m05 - m.m00 - m.m10);
			real const invr = real (0.5) / r;
			real_q.x = (m.m01 + m.m04) * invr;
			real_q.y = real (0.5) * r;
			real_q.z = (m.m06 + m.m09) * invr;
			real_q.w = (m.m08 - m.m02) * invr;
		} else {
			real const r = std::sqrt (real (1) + m.m10 - m.m00 - m.m05);
			real const invr = real (0.5) / r;
			real_q.x = (m.m08 + m.m02) * invr;
			real_q.y = (m.m06 + m.m09) * invr;
			real_q.z = real (0.5) * r;
			real_q.w = (m.m01 - m.m04) * invr;
		}

		quat dual;
		dual.x =  real (0.5) * ( m.m12 * real_q.w + m.m13 * real_q.z - m.m14 * real_q.y);
		dual.y =  real (0.5) * (-m.m12 * real_q.z + m.m13 * real_q.w + m.m14 * real_q.x);
		dual.z =  real (0.5) * ( m.m12 * real_q.y - m.m13 * real_q.x + m.m14 * real_q.w);
		dual.w = -real (0.5) * ( m.m12 * real_q.x + m.m13 * real_q.y + m.m14 * real_q.z);
		return {
			dual,
			real_q
		};
	}

	inline static dual_quat from_bone (const vec3 & p, const quat & q) {

		const float qx = q.x, qy = q.y, qz = q.z, qw = q.w;

		const float tx = p.x, ty = p.y, tz = p.z;

		return{
				{
					0.5f*(tx*qw + ty*qz - tz*qy),
					0.5f*(-tx*qz + ty*qw + tz*qx),
					0.5f*(tx*qy - ty*qx + tz*qw),
					-0.5f*(tx*qx + ty*qy + tz*qz)
				},
				{qx, qy, qz, qw}
		};
	}

	inline dual_quat operator * (const dual_quat & v) {
		return{
			r * v.d + d * v.r,
			r * v.r
		};
	}

};

struct tbone {
	vec3 ot;
	quat or;

	vec3 t;
	quat r;

	mat4 bone_matrix () {
		mat4 inv_pose = (or.to_matrix () * mat4::make_translation (ot)).invert ();
		mat4 pose = r.to_matrix () * mat4::make_translation (t);

		return inv_pose * pose;
	}

	dual_quat bone_quat () {
		dual_quat inv = dual_quat::from_bone (-ot, or);
		dual_quat pose = dual_quat::from_bone (t, r);

		return pose * inv;
	}

	inline tbone transform (const tbone & b) {
		return tbone{
			b.ot + (b.or * ot),
			b.or,
			b.t + (b.r * t),
			b.r * r
		};
	}
};

struct bone {
	vec3 t;
	quat r;

	inline tbone transform (const tbone & b) {
		return tbone {
			t, 
			r,
			b.t + (b.r * t),
			b.r * r
		};
	}
};

bone bones [] = {
		{{-1, .0, .0}, {1.0, .0, .0, .0}},
		{{1, .0, .0}, {1.0, .0, .0, .0}}
};

struct skinned_vert {
	vec3	pos;
	uvec2	bones;
	real	weight;
};

skinned_vert vert_data [] = {
	{{-1, -.5, -.5},{0, 0}, 0.},
	{{-1, -.5, .5}, {0, 0}, 0.},
	{{-1, .5, -.5}, {0, 0}, 0.},
	{{-1, .5, .5},  {0, 0}, 0.},
	{{.0, -.5, -.5},{0, 1}, 0.5},
	{{.0, -.5, .5}, {0, 1}, 0.5},
	{{.0, .5, -.5}, {0, 1}, 0.5},
	{{.0, .5, .5},  {0, 1}, 0.5},
	{{1, -.5, -.5}, {1, 1}, 0.},
	{{1, -.5, .5},  {1, 1}, 0.},
	{{1, .5, -.5},  {1, 1}, 0.},
	{{1, .5, .5},   {1, 1}, 0.}
};

inline vec3 transform_to_screen (const mat4 & vp_matrix, const vec3 & v) {
	vec3 r = vp_matrix * v;

	r.x /= r.z;
	r.y /= r.z;
	r.z = .0;

	return r;
}

inline void draw_rect (const vec3 & center, real size, const color & color_v) {
	ballistic::graphics::opengl_debug::draw_rect (center - vec3 {size, size, .0}, center + vec3 {size, size, .0}, color_v);
}

inline void draw_bones (const vec3 & parent, const vec3 & child) {
	ballistic::graphics::opengl_debug::draw_line (parent, child, {.0, 1.0, .0, 1.});
	draw_rect (parent, 0.01F, {.0, 1.0, .0, 1.});
}

// -----------
class rigged : public ballistic::component {
private:

	property < graphics::material * > * _material;
	entity * _camera;

public:

	real
		mult = 1.,
		angle = 0.;

	rigged () : _camera (nullptr) {
	
	}

	static void require_properties (entity_type * new_type, component_info & info) {
		new_type->properties.require < graphics::material * > (id::graphics::material);
	}

	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
		component::setup (parent, parameters);

		_material = parent->properties.aquire < graphics::material * > (id::graphics::material);

		_camera = game::instance.entities [text_to_id ("mah_camerah")];
		
		game::instance.global_notifier.attach (id::message::render, this);
		game::instance.global_notifier.attach (id::message::update, this);
	}

	virtual void terminate () {
		game::instance.global_notifier.detach (id::message::render, this);
		game::instance.global_notifier.detach (id::message::update, this);
	}

	virtual void notify (ballistic::entity * sender, ballistic::message & message) {
		using namespace ballistic::graphics;

		if (message.id () == id::message::update) {

			real time = message [id::frame_time];
			angle += (0.5F * mult) * time;

			if (angle > 1.5) {
				mult = -1.;
				angle = 1.5;
			} else if (angle < -1.5) {
				mult = 1.;
				angle = -1.5;
			}

			return;
		} else if (message.id () == id::message::render) {

			// update bone animation
			tbone temp_bones [2];
			temp_bones [0] = tbone{bones [0].t, bones [0].r, {-1., .0, 1.0}, quat::from_axis ({.0, .0, 1.0}, angle)};
			temp_bones [1] = tbone{bones [1].t, bones [1].r, {1, .0, .0}, quat::from_axis (math::normalize (vec3 {1.5, .0, 2.0}), angle * 1.5)};

			const mat4 & view = _camera->properties [id::graphics::camera_view];
			const mat4 & proj = _camera->properties [id::graphics::camera_proj];

			// project
			mat4 m_vp = view * proj;

			tbone t_bones [2];
			t_bones [0] = {
				bones [0].t,
				bones [0].r,
				temp_bones [0].t,
				temp_bones [0].r
			};

			for (int i = 1; i < 2; ++i) {
				t_bones [i] = temp_bones [i].transform (t_bones [i - 1]);
			}

			for (int i = 0; i < 2; ++i) {
				vec3 b_center = transform_to_screen (m_vp, t_bones [i].t);
				vec3 b_vector = transform_to_screen (m_vp, t_bones [i].t + (t_bones [i].r * vec3 {.5, .0, .0}));

				draw_bones (b_center, b_vector);
			}

			// transform and render (software) verts
			for (auto v : vert_data) {

				tbone b1 = t_bones [v.bones.x];
				tbone b2 = t_bones [v.bones.y];

				dual_quat q;

				mat4 m;

				if (v.weight == 0) {
					m = b1.bone_matrix ();
					q = b1.bone_quat ();//dual_quat::from_matrix (b1.bone_matrix ());
				} else {

					mat4 m1 = b1.bone_matrix ();
					mat4 m2 = b2.bone_matrix ();

					auto q1 = b1.bone_quat ();//dual_quat::from_matrix (b1.bone_matrix ());
					auto q2 = b2.bone_quat ();//dual_quat::from_matrix (b2.bone_matrix ());

					q = dual_quat::blend (q1, q2, v.weight);

					m = (m1 * (real (1) - v.weight)) + (m2 * v.weight);
				}



				//if (v.pos.x == 0.0)
				{
					vec3 dtv = q.transform (v.pos);
					dtv = transform_to_screen (m_vp, dtv);

					draw_rect (dtv, 0.01F, {1.0, .0, .0, 1.});

					vec3 mtv = m * v.pos;
					mtv = transform_to_screen (m_vp, mtv);

					draw_rect (mtv, 0.01F, {.0, .0, 1.0, 1.});
				}
			}
			
		}
	}

};

int main ( int argc, char ** argv) {

	debug_init();

	_frontend = create_frontend ({800, 800});
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->clear_color ({.0F, .6F, 1.F, 1.F});
	
	game & g = game::instance;
	// initialize
	g.initialize ();
	g.frontend (_frontend);

	// setup game stuffs
	ballistic::graphics::define_resources (_device);

	ballistic::component::declare < rigged > (text_to_id ("rigged"));

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);
	graphics->material_effect (g.resources [res_default_material]);
	graphics->overlay_effect (g.resources [res_overlay_material]);

	g.systems.attach (graphics);

	// create entities
	g.entities.create (res_camera, text_to_id ("mah_camerah"));
	g.entities.create (res_rig);
	g.entities.create(res_overlay_text);

	glDisable (GL_CULL_FACE);
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	_frontend->do_event_loop ();

	return 0;
}