#include "camera_controller.h"

#include <ballistic.frontend.h>
#include <ballistic.graphics.h>

const ballistic::id_t camera_controller::component_id = text_to_id ("camera_controller");
const ballistic::id_t camera_controller::starting_radius = text_to_id ("camera_controller.starting_radius");

void camera_controller::require_properties (entity_type * new_type, component_info & info) {
	new_type->properties
		.require < vec3 > (id::position)
		.require < real > (starting_radius, .0);
}

void camera_controller::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters) {
	component::setup (parent, parameters);

	_mouse_is_down = false;

	_cam_position = parent->properties.aquire < vec3 > (id::position);

	_yaw = real (.0);
	_pitch = real (.0);
	_radius = parent->properties [starting_radius];

		parent ->game ().global_notifier.attach (
		{
			id::message::update,
			id::frontend::on_mouse_event
		},
			this
	);
}

void camera_controller::terminate () {
	parent ()->game ().global_notifier.detach (
		{
			id::message::update,
			id::frontend::on_mouse_event
		},
			this
	);
}

void camera_controller::notify (ballistic::entity * sender, ballistic::message & message) {

	ballistic::id_t message_id = message.id ();

	real move_mult = real(0.01);
	real delta_mult = real (0.02);

	if (message_id == id::frontend::on_mouse_event) {
		switch (message [id::frontend::mouse_event_type].as < uint32_t > ()) {
		case mouse_event_down:
			if (message [id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left ) {
				_mouse_is_down = true;
				_mouse_start = message [id::frontend::mouse_position];
				_start_yaw = _yaw;
				_start_pitch = _pitch;
			}
			break;
		case mouse_event_move:
			if (_mouse_is_down && message [id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left) {
				point dif = _mouse_start - message [id::frontend::mouse_position].as < point > ();
				_yaw = _start_yaw + real (dif.x) * move_mult;
				_pitch = _start_pitch - real (dif.y) * move_mult;
			}
			break;
		case mouse_event_up:
			if (message [id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left) {
				_mouse_is_down = false;
				point dif = _mouse_start - message [id::frontend::mouse_position].as < point > ();
				_yaw = _start_yaw + real (dif.x) * move_mult;
				_pitch = _start_pitch - real (dif.y) * move_mult;
			}
			break;
		case mouse_event_wheel:
			{
				int delta = message [id::frontend::mouse_wheel_delta];
				_radius -= (real (delta) * delta_mult);
			}
			break;
		}
		
	} else if (message_id == id::message::update) {

		vec3 pos = {
			(std::cos (_yaw) * std::cos (_pitch)) * _radius,
			std::sin (_pitch) * _radius,
			(-std::sin (_yaw) * std::cos (_pitch)) * _radius
		};

		*_cam_position = pos;

	}

}