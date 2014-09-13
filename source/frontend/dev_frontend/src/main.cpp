
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

//struct dual_quat {
//
//	vec4 l;
//	quat r;
//
//	inline static vec4 epsilon_half (const vec4 & a, const vec4 & b) {
//		return{
//			real (.5) * ( a.x * b.w + a.w * b.x - a.z * b.y + a.y * b.z ),
//			real (.5) * ( a.y * b.w + a.z * b.x + a.w * b.y - a.x * b.z ),
//			real (.5) * ( a.z * b.w - a.y * b.x + a.x * b.y + a.w * b.z ),
//
//			real (.5) * ( a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z )
//		};
//	}
//
//	static dual_quat from_tq (const vec3 & t, const quat & q) {
//		return{
//				{
//					//real (.5) * (t_v.x * r_v.w + t_v.y * r_v.v.z - t_v.z * r_v.v.y),
//					//real (.5) * (-t_v.x * r_v.v.z + t_v.y * r_v.w + t_v.z * r_v.v.x),
//					//real (.5) * (t_v.x * r_v.v.y - t_v.y * r_v.v.x + t_v.z * r_v.w),
//					//real (-.5) * (t_v.x * r_v.v.x + t_v.y * r_v.v.y + t_v.z * r_v.v.z)
//					real (-0.5) * (+t.x * q.x + t.y * q.y + t.z * q.z ),
//					real (+0.5) * (+t.x * q.w + t.y * q.z - t.z * q.y ),
//					real (+0.5) * (-t.x * q.z + t.y * q.w + t.z * q.x ),
//					real (+0.5) * (+t.x * q.y - t.y * q.x + t.z * q.w )
//				},
//				q
//		};
//	}
//
//	static dual_quat pure_t (const vec3 & t) {
//		return{
//				{
//					real (.5) * t.x,
//					real (.5) * t.y,
//					real (.5) * t.z,
//					real (.5)
//				},
//				{ .0, .0, .0, 1.0}
//		};
//	}
//
//	static dual_quat rot_point (const vec3 & t, const quat & r) {
//		quat hr;
//		vec4 tt;
//
//		tt.xyz = t;
//		tt.w = 1.0;
//
//		hr.xyzw = epsilon_half (r.xyzw, tt);
//
//		return{
//			epsilon_half (tt, r.xyzw),
//			r - hr
//		};
//	}
//
//	inline vec3 transform (const vec3 & v) const {
//		return
//			(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w + l.xyz) + l.xyz * r.w - r.xyz * l.w) * real (2) + v;
//			//v +
//			//(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w) * real (2)) +
//			//((l.xyz * r.w) - (r.xyz * l.w) + (math::cross (r.xyz, l.xyz)) * real (2));
//	}
//
//	inline dual_quat normalize () const {
//
//		vec4 n = math::normalize (r.xyzw);
//		vec4 d = l - n * math::dot (n, l);
//		quat q;
//
//		q.xyzw = n;
//
//		return {
//			d,
//			q
//		};
//	}
//
//	inline dual_quat conj () const {
//		return{
//				{ -l.x, -l.y, -l.z, l.w },
//				{ -r.x, -r.y, -r.z, r.w}
//		};
//	}
//
//	inline dual_quat operator * (const dual_quat & q) const {
//		dual_quat t;
//
//		t.r = r * q.r;
//		t.l = r.xyzw * q.l + q.l * r.xyzw;
//
//		return t;
//	}
//
//	inline vec3 operator * (const vec3 & v) const {
//
//	}
//
//	//inline static dual_quat blend (const dual_quat & q1, const dual_quat & q2, real weight) {
//	//	return {
//	//		(q1.l * (real (1) - weight)) + (q2.l * weight),
//	//		(q1.r * (real (1) - weight)) + (q2.r * weight)
//	//	};
//	//}
//
//};

struct dual_quat {

	vec4 d;
	quat r;

	inline vec3 transform (const vec3 & v) const {
		return
		//	(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w + l.xyz) + l.xyz * r.w - r.xyz * l.w) * real (2) + v;
		v +
		(math::cross (r.xyz, math::cross (r.xyz, v) + v * r.w) * real (2)) +
		((d.xyz * r.w) - (r.xyz * d.w) + (math::cross (r.xyz, d.xyz)) * real (2));
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

		vec4 dual;
		dual.x =  real (0.5) * ( m.m12 * real_q.w + m.m13 * real_q.z - m.m14 * real_q.y);
		dual.y =  real (0.5) * (-m.m12 * real_q.z + m.m13 * real_q.w + m.m14 * real_q.x);
		dual.z =  real (0.5) * ( m.m12 * real_q.y - m.m13 * real_q.x + m.m14 * real_q.w);
		dual.w = -real (0.5) * ( m.m12 * real_q.x + m.m13 * real_q.y + m.m14 * real_q.z);
		return {
			dual,
			real_q
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
};

struct bone {
	vec3 t;
	quat r;

	inline tbone transform (const tbone & b) {
		return tbone {
			b.ot + t,
			b.or * r,
			b.t + (b.r * t),
			b.r * r
		};
	}
};

bone bones [] = {
		{{-1, .0, .0}, {1.0, .0, .0, .0}},
		{{1, .0, .0}, {1.0, .0, .0, .0}},
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
	{{1, -.5, -.5}, {2, 2}, 0.},
	{{1, -.5, .5},  {2, 2}, 0.},
	{{1, .5, -.5},  {2, 2}, 0.},
	{{1, .5, .5},   {2, 2}, 0.}
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

			if (angle > .5) {
				mult = -1.;
				angle = .5;
			} else if (angle < -.5) {
				mult = 1.;
				angle = -.5;
			}

			return;
		} else if (message.id () == id::message::render) {

			// update bone animation
			bone temp_bones [3];
			temp_bones [0] = bone{{-1., .0, .0}, quat::from_axis ({.5, 1.0, 1.0}, angle)};
			temp_bones [1] = bone{{1, .0, .0}, quat::from_axis ({.0, .0, 1.0}, angle)};
			temp_bones [2] = bones [2];

			const mat4 & view = _camera->properties [id::graphics::camera_view];
			const mat4 & proj = _camera->properties [id::graphics::camera_proj];

			// project
			mat4 m_vp = view * proj;

			tbone t_bones [3];
			t_bones [0] = {
				bones [0].t,
				bones [0].r,
				temp_bones [0].t,
				temp_bones [0].r
			};

			for (int i = 1; i < 3; ++i) {
				t_bones [i] = temp_bones [i].transform (t_bones [i - 1]);
			}

			vec3 t_screen_bones [3];
			for (int i = 0; i < 3; ++i) {
				t_screen_bones [i] = transform_to_screen (m_vp, t_bones [i].t);
			}

			for (int i = 1; i < 3; ++i) {
				draw_bones (t_screen_bones [i - 1], t_screen_bones [i]);
			}

			// transform and render (software) verts
			for (auto v : vert_data) {

				tbone b1 = t_bones [v.bones.x];
				tbone b2 = t_bones [v.bones.y];

				auto q1 = dual_quat::from_matrix (b1.bone_matrix ());
				auto q2 = dual_quat::from_matrix (b2.bone_matrix ());

				auto q = dual_quat::blend (q1, q2, v.weight);

				vec3 tv = q.transform (v.pos);
				tv = transform_to_screen (m_vp, tv);

				//if (v.pos.x == 0.0)
					draw_rect (tv, 0.01F, {1.0, .0, .0, 1.});
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