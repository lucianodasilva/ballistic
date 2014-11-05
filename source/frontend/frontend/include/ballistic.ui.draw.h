#ifndef _ballistic_ui_draw_h_
#define _ballistic_ui_draw_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

namespace ballistic {
	namespace ui {

		class draw {
		private:

			graphics::idevice
				* _device;

			graphics::ieffect 
				* _overlay_effect;

			graphics::imesh 
				* _line_mesh,
				* _square_mesh;

			graphics::iconstant
				* _effect_diffuse,
				*_effect_texture,
				*_effect_t_model;

			bool _valid_config;

			void evaluate_config ();
			void report_config_fail (const char * element) const;

		public:

			graphics::idevice * device ();
			graphics::idevice * device (graphics::idevice * v);

			graphics::ieffect * overlay_effect ();
			graphics::ieffect * overlay_effect (graphics::ieffect * v);

			draw ();
			virtual ~draw ();

			void begin_frame () const;

			void draw_line (const color & col, const vec2 & p1, const vec2 & p2) const;
			void draw_rect (const color & col, const vec2 & p1, const vec2 & p2) const;
			void fill_rect (const color & col, const vec2 & p1, const vec2 & p2) const;
			
			void draw_text (const color & col, const vec2 & pos, real size, const std::string & text) const;

		};

	}
}

#endif