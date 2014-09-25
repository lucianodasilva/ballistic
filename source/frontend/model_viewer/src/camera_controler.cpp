#include "camera_controler.h"

#include <ballistic.frontend.h>
#include <ballistic.graphics.h>

const id_t camera_controler::component_id = text_to_id ("camera_controler");
const id_t camera_controler::starting_radius = text_to_id ("camera_controller.starting_radius");

void camera_controler::require_properties (entity_type * new_type, component_info & info) {
	new_type->properties.require < vec3 > (id::position);
	new_type->properties.require < real > (starting_radius, .0);
}

void camera_controler::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
	component::setup (parent, parameters);

	_mouse_is_down = false;

	_cam_position = parent->properties.aquire < vec3 > (id::position);

	_yaw = real (.0);
	_pitch = real (.0);
	_radius = parent->properties [starting_radius];

	game::instance.global_notifier.attach (id::message::update, this);
	game::instance.global_notifier.attach (id::frontend::on_mouse_up, this);
	game::instance.global_notifier.attach (id::frontend::on_mouse_move, this);
	game::instance.global_notifier.attach (id::frontend::on_mouse_down, this);
	game::instance.global_notifier.attach (id::frontend::on_mouse_wheel, this);
}

void camera_controler::terminate () {
	game::instance.global_notifier.detach (id::message::update, this);
	game::instance.global_notifier.detach (id::frontend::on_mouse_up, this);
	game::instance.global_notifier.detach (id::frontend::on_mouse_move, this);
	game::instance.global_notifier.detach (id::frontend::on_mouse_down, this);
	game::instance.global_notifier.detach (id::frontend::on_mouse_wheel, this);
}

void camera_controler::notify (ballistic::entity * sender, ballistic::message & message) {

	id_t message_id = message.id ();

	real move_mult = 0.01;
	real delta_mult = 0.02;

	if (message_id == id::frontend::on_mouse_down) {

		_mouse_is_down = true;
		_mouse_start = message [id::frontend::mouse_position];
		_start_yaw = _yaw;
		_start_pitch = _pitch;

	} else if (message_id == id::frontend::on_mouse_up) {

		_mouse_is_down = false;
		point dif = _mouse_start - message [id::frontend::mouse_position].as < point > ();
		_yaw = _start_yaw + real (dif.x) * move_mult;
		_pitch = _start_pitch - real (dif.y) * move_mult;

	} else if (message_id == id::frontend::on_mouse_move && _mouse_is_down) {

		point dif = _mouse_start - message [id::frontend::mouse_position].as < point > ();
		_yaw = _start_yaw + real (dif.x) * move_mult;
		_pitch = _start_pitch - real (dif.y) * move_mult;

	} else if (message_id == id::frontend::on_mouse_wheel) {

		int delta = message [id::frontend::mouse_wheel_delta];
		_radius -= (real (delta) * delta_mult);
		
	} else if (message_id == id::message::update) {

		vec3 pos = {
			(std::cos (_yaw) * std::cos (_pitch)) * _radius,
			std::sin (_pitch) * _radius,
			(-std::sin (_yaw) * std::cos (_pitch)) * _radius
		};

		*_cam_position = pos;

	}

}