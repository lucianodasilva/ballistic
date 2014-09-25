#ifndef	_ballistic_model_viewer_camera_controler_h_
#define _ballistic_model_viewer_camera_controler_h_

#include <ballistic.base.h>

using namespace ballistic;

class camera_controler : public component {
private:

	property < vec3 > * _cam_position;

	real
		_radius,
		_yaw,
		_pitch;

	bool _mouse_is_down;

	point _mouse_start;

	real
		_start_yaw,
		_start_pitch;


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