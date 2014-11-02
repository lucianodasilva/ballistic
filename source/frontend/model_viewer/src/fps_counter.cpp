#include "fps_counter.h"

#include <ballistic.frontend.h>
#include <ballistic.graphics.h>

const ballistic::id_t fps_counter::component_id = text_to_id ("fps_counter");

void fps_counter::require_properties (entity_type * new_type, component_info & info) {
	new_type->properties.require_notify < string > (id::overlay_text::text, "");
}

void fps_counter::setup (ballistic::containers::property_container & parameters) {
	component::setup (parameters);

	_last_frame = 0;
	_last_time = 0;

	_text = parent ().properties.aquire < string > (id::overlay_text::text);

	game ().global_notifier.attach (
		id::message::update,
		this
	);
}

void fps_counter::terminate () {
	game ().global_notifier.detach (
		id::message::update,
		this
	);
}

void fps_counter::notify (ballistic::entity * sender, ballistic::message & message) {

	real current_time = game ().game_time ();
	real elapsed_time = current_time - _last_time;

	if (elapsed_time > update_time) {

		uint32_t frame = game ().frame_count ();
		real instant_fps = real (frame - _last_frame) / (elapsed_time);

		*_text = convert_to < string > (instant_fps);

		_last_time = current_time;
		_last_frame = frame;
	}
}