#ifndef _ballistic_graphics_imesh_h_
#define	_ballistic_graphics_imesh_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		enum mesh_attribute {
			mesh_attribute_position = 1,
			mesh_attribute_uv		= 2,
			mesh_attribute_normal	= 4
		};

		class idevice;

		class imesh : public ballistic::resources::iresource {
		public:

			virtual uint8_t get_run_id () = 0;
			
			virtual void set_data (
				uint8_t *		data_buffer,
				int32_t			data_buffer_size,
				uint16_t *		index_buffer,
				uint32_t		index_buffer_size,
				mesh_attribute	attributes,
				bool			dynamic = false
			) = 0;

			virtual void update_data (
				uint8_t *		data_buffer,
				int32_t			data_buffer_size,
				mesh_attribute	attributes
			) = 0;

			virtual void update_index (
				uint16_t *		index_buffer,
				uint32_t		index_buffer_size
			) = 0;

			virtual void apply (idevice * device) = 0;
			virtual void render () = 0;
		};

	}
}

#endif