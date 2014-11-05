#include "ballistic.ui.draw.h"

namespace ballistic {
	namespace ui {

		void draw::evaluate_config () {
			_valid_config =
				_device && 
				_overlay_effect;
		}

		void draw::report_config_fail (const char * element) const {
			if (!_device)
				debug_error ("graphics device not set! will not render ui " << element);

			if (!_overlay_effect)
				debug_error ("no active overlay effect! will not render ui " << element);
		}

		graphics::idevice * draw::device () { return _device; }

		graphics::idevice * draw::device (graphics::idevice * v) {
			_device = v;

			// do initializing stuffs
			_line_mesh = _device->create_mesh (text_to_id ("__ui_line_mesh__"));
			_line_mesh->set_data (
				nullptr,
				sizeof (vec3) * 2, // information volume for 2 vertices
				nullptr,
				2, // 2 index count
				graphics::mesh_attribute_position,
				true
			);

			uint16_t square_index [6] = {0, 1, 2, 0, 2, 3};

			_square_mesh = _device->create_mesh (text_to_id ("__ui_square_mesh__"));
			_square_mesh->set_data (
				nullptr,
				sizeof (vec3) * 4, // information volume for 4 vertices
				+square_index,
				6, // 6 index count
				graphics::mesh_attribute_position,
				true
			);

			evaluate_config ();

			return v;
		}

		graphics::ieffect * draw::overlay_effect () { return _overlay_effect; }

		graphics::ieffect * draw::overlay_effect (graphics::ieffect * v) {
			_overlay_effect = v;

			if (v) {
				_effect_diffuse = v->constant (id::effect::diffuse);
				_effect_texture = v->constant (id::effect::texture);
				_effect_t_model = v->constant (id::effect::t_model);
			} else {
				_effect_diffuse = &graphics::null_constant::instance;
				_effect_texture = &graphics::null_constant::instance;
				_effect_t_model = &graphics::null_constant::instance;
			}

			evaluate_config ();
			return v;
		}

		draw::draw () : 
			_device (nullptr),
			_overlay_effect (nullptr),
			_effect_diffuse (&graphics::null_constant::instance),
			_effect_texture (&graphics::null_constant::instance),
			_effect_t_model (&graphics::null_constant::instance),
			_valid_config (false)
		{}

		draw::~draw () {
			if (_device) {
				delete _line_mesh;
				delete _square_mesh;
			}
		}

		void draw::begin_frame () const {
			_effect_t_model->set_value (mat4::identity);
		}

		void draw::draw_line (const color & col, const vec2 & p1, const vec2 & p2) const {
			if (!_valid_config) {
				report_config_fail ("[line]");
				return;
			}

			static uint16_t index [2] = {0, 1};	// 2 vector indexes
			real data [6] = { // 6 units ( 2 vectors * 3 dimentions )
				p1.x, p1.y, real (.0),
				p2.x, p2.y, real (.0)
			};

			_line_mesh->set_data (
				(uint8_t *)(+data),
				sizeof (real) * 3 * 2,
				+index,
				2,
				graphics::mesh_attribute_position,
				true
			);

			_effect_diffuse->set_value (col);
			// update uniforms for color and stuffs
			_line_mesh->render ();
		}

		void draw::draw_rect (const color & col, const vec2 & p1, const vec2 & p2) const {
			if (!_valid_config) {
				report_config_fail ("[rect]");
				return;
			}

			real data [12] = {									// 12 units ( 4 vectors * 3 dimentions )
				p1.x, p1.y, real (.0),
				p2.x, p1.y, real (.0),
				p2.x, p2.y, real (.0),
				p1.x, p2.y, real (.0),
			};

			_square_mesh->update_data (
				(uint8_t *)(+data),
				sizeof (vec3) * 4
			);

			// update uniforms for color and stuffs
			_effect_diffuse->set_value (col);
			_effect_texture->set_value ((int)0);
			
			_square_mesh->apply (_device);
			_square_mesh->render ();
		}

		void draw::fill_rect (const color & col, const vec2 & p1, const vec2 & p2) const {
		}
	
		void draw::draw_text (const color & col, const vec2 & pos, real size, const std::string & text) const {

		}

	}
}
