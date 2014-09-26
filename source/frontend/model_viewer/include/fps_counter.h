#ifndef	_ballistic_model_viewer_fps_counter_h_
#define _ballistic_model_viewer_fps_counter_h_

#include <ballistic.base.h>

using namespace ballistic;

class fps_counter : public component {
private:

	property < string > * _text;

	uint32_t _last_frame;
	real _last_time;

	const real update_time = .025;

public:

	static const id_t
		component_id,
		starting_radius;

	static void require_properties (entity_type * new_type, component_info & info);

	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters);

	virtual void terminate ();

	virtual void notify (ballistic::entity * sender, ballistic::message & message);

};

#endif