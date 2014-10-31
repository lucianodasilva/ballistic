
#include <ballistic.base.h>
#include <ballistic.graphics.h>
#include <ballistic.frontend.h>

#include <map>
#include <chrono>
#include <limits>

using namespace ballistic;

ballistic::ifrontend *			_frontend;
ballistic::graphics::idevice *	_device;

ballistic::graphics::imesh *	_mesh;



#ifdef BALLISTIC_OS_WINDOWS

ballistic::ifrontend * create_frontend (game & game_ref, const point & size ) {
	return new ballistic::desktop::frontend (game_ref, size);
}

#elif defined (BALLISTIC_OS_DARWIN)
#	include <GLUT/GLUT.h>
ballistic::ifrontend * create_frontend (const point & size) {
	return new ballistic::desktop::frontend (size);
}
#endif

#ifdef BALLISTIC_DESKTOP_GL
#	include <ballistic.graphics.opengl.h>

ballistic::graphics::idevice * create_device () {
	return new ballistic::graphics::opengl_device ();
}

#endif

ballistic::res_id_t 
	res_rig ("rigged.entity", "resources/rigging.xml"),
	res_overlay_text ("overlay_text.entity", "resources/rigging.xml"),
	res_camera ("camera.entity", "resources/rigging.xml"),
	res_default_material ("default_material.effect", "resources/default_material.fx"),
	res_overlay_material ("overlay_material.effect", "resources/overlay_material.fx");

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
class rigged_demo : public ballistic::component {
private:

	property < graphics::material * > * _material;
	entity * _camera;

public:

	real
		mult = 1.,
		angle = 0.;

	rigged_demo () : _camera (nullptr) {
	
	}

	static void require_properties (entity_type * new_type, component_info & info) {
		new_type->properties.require < graphics::material * > (id::graphics::material);
	}

	virtual void setup (ballistic::containers::property_container & parameters) {
		component::setup (parameters);

		_material = parent ().properties.aquire < graphics::material * > (id::graphics::material);

		_camera = game ().entities [text_to_id ("mah_camerah")];
		
		game ().global_notifier.attach (id::message::render, this);
		game ().global_notifier.attach (id::message::update, this);
	}

	virtual void terminate () {
		game ().global_notifier.detach (id::message::render, this);
		game ().global_notifier.detach (id::message::update, this);
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
			temp_bones [0] = tbone{bones [0].t, bones [0].r, {-1., .0, .0}, quat::from_axis ({.0, .0, 1.0}, angle)};
			temp_bones [1] = tbone{bones [1].t, bones [1].r, {1, .0, .0}, quat::from_axis (math::normalize (vec3 {1.0, .0, 1.0}), angle)};

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

				//dual_quat q;

				mat4 m;

				if (v.weight == 0) {
					m = b1.bone_matrix ();
					//q = dual_quat::from_matrix (b1.bone_matrix ());
				} else {

					mat4 m1 = b1.bone_matrix ();
					mat4 m2 = b2.bone_matrix ();

					//auto q1 = dual_quat::from_matrix (b1.bone_matrix ());
					//auto q2 = dual_quat::from_matrix (b2.bone_matrix ());
					//
					//q = dual_quat::blend (q1, q2, v.weight);

					m = (m1 * (real (1) - v.weight)) + (m2 * v.weight);
				}



				//if (v.pos.x == 0.0)
				{
					//vec3 dtv = q.transform (v.pos);
					//dtv = transform_to_screen (m_vp, dtv);
					//
					//draw_rect (dtv, 0.01F, {1.0, .0, .0, 1.});

					vec3 mtv = m * v.pos;
					mtv = transform_to_screen (m_vp, mtv);

					draw_rect (mtv, 0.01F, {.0, .0, 1.0, 1.});
				}
			}
			
		}
	}

};

void generate_rig () {

	real		duration = 2.0; // seconds
	uint32_t 	fps = 6; // why not
	uint32_t	bone_count = 2;



}

int main ( int argc, char ** argv) {

	debug_init();

	game g;

	_frontend = create_frontend (g, {800, 800});
	_frontend->show ();

	_device = create_device ();
	_device->clear_color ({.0F, .6F, 1.F, 1.F});

	// initialize
	g.initialize ();

	// setup game stuffs
	ballistic::graphics::define_resources (g, _device);

	ballistic::component::declare < rigged_demo > (g, text_to_id ("rigged_demo"));

	auto graphics = new ballistic::graphics::graphics_system (g);
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

	_frontend->run ();

	return 0;
}