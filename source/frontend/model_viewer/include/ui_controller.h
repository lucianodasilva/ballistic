#ifndef	_ballistic_model_viewer_ui_controller_h_
#define _ballistic_model_viewer_ui_controller_h_

#include <ballistic.base.h>
#include <ballistic.frontend.h>

using namespace ballistic;

class ui_controller : public ballistic::ui::component {
private:


public:

	static const ballistic::id_t
		component_id;
	
	//static void require_properties (entity_type * new_type, component_info & info);
	
	virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters);
	
	//virtual void terminate ();
	
	virtual void notify (ballistic::entity * sender, ballistic::message & message);

};

#endif