#include "camera_controller.h"

#include <ballistic.frontend.h>
#include <ballistic.graphics.h>

const ballistic::id_t camera_controller::component_id = text_to_id ("camera_controller");
const ballistic::id_t camera_controller::starting_radius = text_to_id ("camera_controller.starting_radius");

void camera_controller::require_properties (entity_type * new_type, component_info & info) {
	new_type->properties
	.require < vec3 > (ballistic::id::position)
		.require < real > (starting_radius, .0);
}

void camera_controller::setup (ballistic::containers::property_container & parameters) {
	component::setup (parameters);

	_mouse_is_down = false;

<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
	_cam_position = parent ().properties.aquire < vec3 > (id::position);
=======
	_cam_position = parent->properties.aquire < vec3 > (ballistic::id::position);
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp

	_yaw = real (.0);
	_pitch = real (.0);
	_radius = parent ().properties [starting_radius];

		game ().global_notifier.attach (
		{
<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
			id::message::update,
			id::ui::on_mouse_event
=======
			ballistic::id::message::update,
			ballistic::id::frontend::on_mouse_event
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
		},
			this
	);
}

void camera_controller::terminate () {
	game ().global_notifier.detach (
		{
<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
			id::message::update,
			id::ui::on_mouse_event
=======
			ballistic::id::message::update,
			ballistic::id::frontend::on_mouse_event
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
		},
			this
	);
}

void camera_controller::notify (ballistic::entity * sender, ballistic::message & message) {

	ballistic::id_t message_id = message.id ();

	real move_mult = real(0.01);
	real delta_mult = real (0.02);

<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
	if (message_id == id::ui::on_mouse_event) {
		switch (message [id::ui::mouse_event_type].as < ui::mouse_event_type > ()) {
		case ui::mouse_event_down:
			if (message [id::ui::mouse_buttons].as < ui::mouse_button > () & ui::mouse_button_left ) {
				_mouse_is_down = true;
				_mouse_start = message [id::ui::mouse_position].as < vec2 > ();
=======
	if (message_id == ballistic::id::frontend::on_mouse_event) {
		switch (message [ballistic::id::frontend::mouse_event_type].as < uint32_t > ()) {
		case mouse_event_down:
				if (message [ballistic::id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left ) {
				_mouse_is_down = true;
					_mouse_start = message [ballistic::id::frontend::mouse_position];
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
				_start_yaw = _yaw;
				_start_pitch = _pitch;
			}
			break;
<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
		case ui::mouse_event_move:
			if (_mouse_is_down && message [id::ui::mouse_buttons].as < ui::mouse_button > () & ui::mouse_button_left) {
				vec2 dif = _mouse_start - message [id::ui::mouse_position].as < vec2 > ();
=======
		case mouse_event_move:
				if (_mouse_is_down && message [ballistic::id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left) {
					point dif = _mouse_start - message [ballistic::id::frontend::mouse_position].as < point > ();
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
				_yaw = _start_yaw + real (dif.x) * move_mult;
				_pitch = _start_pitch - real (dif.y) * move_mult;
			}
			break;
<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
		case ui::mouse_event_up:
			if (message [id::ui::mouse_buttons].as < ui::mouse_button > () & ui::mouse_button_left) {
				_mouse_is_down = false;
				vec2 dif = _mouse_start - message [id::ui::mouse_position].as < vec2 > ();
=======
		case mouse_event_up:
				if (message [ballistic::id::frontend::mouse_buttons].as < uint32_t > () & mouse_button_left) {
				_mouse_is_down = false;
					point dif = _mouse_start - message [ballistic::id::frontend::mouse_position].as < point > ();
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
				_yaw = _start_yaw + real (dif.x) * move_mult;
				_pitch = _start_pitch - real (dif.y) * move_mult;
			}
			break;
		case ui::mouse_event_wheel:
			{
<<<<<<< Updated upstream:source/frontend/model_viewer/src/camera_controller.cpp
				int delta = message [id::ui::mouse_wheel_delta];
=======
				int delta = message [ballistic::id::frontend::mouse_wheel_delta];
>>>>>>> Stashed changes:source/tools/model_viewer/src/camera_controller.cpp
				_radius -= (real (delta) * delta_mult);
			}
			break;
		}
		
	} else if (message_id == ballistic::id::message::update) {

		vec3 pos = {
			(std::cos (_yaw) * std::cos (_pitch)) * _radius,
			std::sin (_pitch) * _radius,
			(-std::sin (_yaw) * std::cos (_pitch)) * _radius
		};

		*_cam_position = pos;

	}

}