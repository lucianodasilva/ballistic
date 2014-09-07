
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

const char * root_package = "resources/perf_test.xml";

ballistic::res_id_t res_cube ("cube.entity", root_package);
ballistic::res_id_t res_cube_manager ("cube_manager.entity", root_package);
ballistic::res_id_t res_cube_count ("cube_count.entity", root_package);
ballistic::res_id_t res_camera ("camera.entity", root_package);

ballistic::res_id_t res_default_material ("default_material.effect", "resources/default_material.fx");
ballistic::res_id_t res_overlay_material ("overlay_material.effect", "resources/overlay_material.fx");

// -----------
class box_brain : public ballistic::component {
private:

	real _start_time;

	property < vec3 > * _bounce;
	property < vec3 > * _start_pos;

public:

	box_brain () : _start_time (-1) {}

	static void require_properties (entity_type * new_type, component_info & info) {
		new_type->properties.require < vec3 > (text_to_id ("bounce"), vec3 ());
		new_type->properties.require < vec3 > (text_to_id ("start_pos"), vec3 ());
	}

	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
		component::setup (parent, parameters);

		_bounce = parent->properties.aquire < vec3 > (text_to_id ("bounce"));
		_start_pos = parent->properties.aquire < vec3 > (text_to_id ("start_pos"));

		game::instance.global_notifier.attach (id::message::update, this);
	}

	virtual void terminate () {
		game::instance.global_notifier.detach (id::message::update, this);
	}

	virtual void notify (ballistic::entity * sender, ballistic::message & message) {
		// update position with animation
		parent ()->properties [id::transform_position] = vec3(*_start_pos) + vec3(*_bounce);															 
	}

};

// -----------
class box_manager : public ballistic::component {
private:

	vector < entity * > _entity_list;
	entity *			_cube_count;

	vector < int > _random_numbers;

public:

	void generate_rand () {
		int nums = _random_numbers.capacity ();
		for (int i = 0; i < nums; ++i)
			_random_numbers.push_back (std::rand ());
	}

	int pop_rand () {

		if (_random_numbers.size () == 0)
			generate_rand ();

		int num = _random_numbers.back ();
		_random_numbers.pop_back ();

		return num;
	}

	box_manager () :
		_cube_count (nullptr)
	{
		_entity_list.reserve (100000);
		_random_numbers.reserve (200000);
	}

	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
		component::setup (parent, parameters);
		game::instance.global_notifier.attach (id::message::update, this);
	}

	virtual void terminate () {
		game::instance.global_notifier.detach (id::message::update, this);
	}

	virtual void notify (ballistic::entity * sender, ballistic::message & message) {

		if (!_cube_count)
			_cube_count = game::instance.entities [text_to_id ("cube_count")];

		real frame_time = message [id::frame_time];

		if (frame_time < 0.017) {

			for (int i = 0; i < 10; ++i) {
				entity * new_entity = game::instance.entities.create (res_cube);
				new_entity->properties [text_to_id ("start_pos")] = vec3 ({
					real ((pop_rand () % 100) - 50),
					real (0),
					real ((pop_rand () % 100) - 50)
				});
				
				_entity_list.push_back (new_entity);
			}

			_cube_count->properties [id::graphics::text::text] = convert_to < std::string > (_entity_list.size ());
		} else if (frame_time > 0.020 ) {
			auto entity_count = _entity_list.size ();

			if (entity_count == 0)
				return;

			_entity_list.back ()->kill ();
			_entity_list.pop_back ();

			_cube_count->properties [id::graphics::text::text] = convert_to < std::string > (entity_count - 1);
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

	g.initialize ();

	g.frontend (_frontend);

	// setup game stuffs
	ballistic::graphics::define_resources (_device);

	component::declare < box_brain > (text_to_id ("box_brain"));
	component::declare < box_manager > (text_to_id ("box_manager"));

	auto graphics = new ballistic::graphics::graphics_system ();
	graphics->device (_device);
	graphics->material_effect (g.resources [res_default_material]);
	graphics->overlay_effect (g.resources [res_overlay_material]);

	g.systems.attach (graphics);

	// create entities
	game::instance.entities.create (res_camera);
	game::instance.entities.create (text_to_id ("cube_count"), res_cube_count);
	game::instance.entities.create (res_cube_manager);

	// initialize
	g.initialize ();

	_frontend->do_event_loop ();

	return 0;
}