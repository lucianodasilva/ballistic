#include "ui_controller.h"

#include <ballistic.frontend.h>
#include <ballistic.graphics.h>

const ballistic::id_t ui_controller::component_id = text_to_id ("ui_controller");

//void ui_controller::require_properties (entity_type * new_type, component_info & info) {
//	new_type->properties
//		.require < vec3 > (id::position)
//		.require < real > (starting_radius, .0);
//}
//

void ui_controller::setup (ballistic::entity * parent, ballistic::containers::property_container & parameters, ballistic::game & game_inst) {
	component::setup (parent, parameters, game_inst);

	// create ui controls and other stuffs
}

//
//void ui_controller::terminate () {
//	parent ()->game ().global_notifier.detach (
//		{
//			id::message::update,
//			id::frontend::on_mouse_event
//		},
//			this
//	);
//}

void ui_controller::notify (ballistic::entity * sender, ballistic::message & message) {
	ui::component::notify (sender, message);
}