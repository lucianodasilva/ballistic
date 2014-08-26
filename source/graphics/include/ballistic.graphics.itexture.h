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
			texture_filter_linear,
			texture_filter_linear_mipmap_nearest,
			texture_filter_linear_mipmap_linear
		};

		enum texture_format {
			texture_format_rgb,
			texture_format_rgba
		};

		class itexture : public ballistic::iresource {
		public:

			itexture (const id_t & id);
			
			// properties
			virtual uint8_t run_id () = 0;

			// load data
			virtual void set_data (
				char * data,
				uint32_t width,
				uint32_t height,
				const texture_format & format,
				const texture_wrap & wrap_s_v = texture_wrap_clamp_to_border,
				const texture_wrap & wrap_t_v = texture_wrap_clamp_to_border,
				const texture_filter & mag_filter_v = texture_filter_nearest,
				const texture_filter & min_filter_v = texture_filter_nearest
			) = 0;

			//virtual void update_data (
			//	char * data,
			//	int width,
			//	int height,
			//	const texture_wrap & wrap_s_v = texture_wrap_clamp_to_border,
			//	const texture_wrap & wrap_t_v = texture_wrap_clamp_to_border,
			//	const texture_filter & mag_filter_v = texture_filter_nearest,
			//	const texture_filter & min_filter_v = texture_filter_nearest
			//) = 0;

			virtual void apply (idevice * device) = 0;

		};

	}
}

#endif