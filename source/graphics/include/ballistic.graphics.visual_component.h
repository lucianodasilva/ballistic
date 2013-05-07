#ifndef _ballistic_graphics_visual_component_h_
#define _ballistic_graphics_visual_component_h_

#include <Ballistic.h>

namespace ballistic {
	namespace graphics {
		
		class visual_component : public engine::icomponent {
		public:

			static engine::attribute::id_t mesh_attribute_id; 
			static engine::attribute::id_t material_attribute_id; 
			static engine::attribute::id_t transform_attribute_id;

			virtual void setup ();
			
			virtual void notify ( ballistic::engine::message & message );
			
		};
		
	}
}

#endif
