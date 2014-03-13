#ifndef _ballistic_graphics_itexture_h_
#define	_ballistic_graphics_itexture_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class idevice;

		enum texture_wrap {
			texture_wrap_clamp_to_edge,
			texture_wrap_clamp_to_border,
			texture_wrap_mirrored_repeat,
			texture_wrap_repeat
		};

		enum texture_filter {
			texture_filter_nearest,
			texture_filter_linear
		};

		class itexture : public ballistic::iresource {
		public:

			itexture (const id_t & id);
			
			// properties
			virtual uint8_t run_id () = 0;

			virtual texture_wrap wrap_s () = 0;
			virtual void wrap_u (const texture_wrap & v) = 0;

			virtual texture_wrap wrap_t () = 0;
			virtual void wrap_t (const texture_wrap & v) = 0;

			virtual texture_filter mag_filter () = 0;
			virtual void mag_filter (const texture_filter & v) = 0;

			virtual texture_filter min_filter () = 0;
			virtual void min_filter (const texture_filter & v) = 0;

			// load data
			virtual void set_data (char * data, int width, int height) = 0;
			virtual void update_data (char * data, int width, int height) = 0;

			virtual void apply (idevice * device) = 0;

		};

	}
}

#endif