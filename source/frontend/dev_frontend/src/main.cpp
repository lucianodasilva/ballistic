
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

// -----------
class rigged : public ballistic::component {
private:

	struct bone {
		vec3 location;
		quat rotation;

		inline bone to_world ( const bone & parent ) {
			return bone {
				parent.location + (parent.rotation * location),
				parent.rotation * rotation
			};
		}
	};

	inline void draw_bones (const bone & parent, const bone & child ) {
		ballistic::graphics::opengl_debug::draw_line (parent.location, child.location, color{1., .0, .0, 1.});
		
		ballistic::graphics::opengl_debug::draw_line (parent.location + vec3{-0.01F, .0, .0}, parent.location + vec3 {.01F, .0, .0}, color {.0, 1., .0, 1.});
		ballistic::graphics::opengl_debug::draw_line (parent.location + vec3{0, -.01F, .0}, parent.location + vec3 {.0, .01F, .0}, color {.0, 1., .0, 1.});
	}

public:
	
	bone b1 = bone {
		{-1., .0, .0},
		quat ()
	};
		
	bone b2 = bone {
		{.5, .0, .0},
		quat ()
	};
		
	bone b3 = bone {
		{.5, .0, .0},
		quat ()
	};

	real
		mult = 1.,
		angle = 0.;

	rigged () {
	
	}

	static void require_properties (entity_type * new_type, component_info & info) {
	}

	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
		component::setup (parent, parameters);

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
			angle += (0.01F * mult);

			if (angle > 1.0)
				mult = -1.;
			else if (angle < -1.0)
				mult = 1.;

			return;
		} else if (message.id () == id::message::render) {

			bone t_b1 = b1;
			bone t_b2 = bone{vec3{.5, .0, .0}, quat::from_axis (vec3{1.0, .0, .0}, angle)};
			bone t_b3 = b3.to_world (b2);

			draw_bones (b1, b2);
			draw_bones (b2, b3);
		}
	}

};

int main ( int argc, char ** argv) {

	debug_init();

	_frontend = create_frontend (point{800, 800});
	_frontend->create ();
	_frontend->show ();

	_device = create_device ();
	_device->clear_color (color{.0F, .6F, 1.F, 1.F});
	
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
	g.entities.create (res_camera);
	g.entities.create (res_rig);
	g.entities.create(res_overlay_text);

	glDisable (GL_CULL_FACE);

	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	_frontend->do_event_loop ();

	return 0;
}