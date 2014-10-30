#ifndef _ballistic_ui_control_h_
#define _ballistic_ui_control_h_

#include <functional>

#include <ballistic.graphics.h>
#include "ballistic.ui.draw.h"
#include "ballistic.ui.common.h"

namespace ballistic {
	namespace ui {

		class control;

		template < class ... _param_tv >
		struct event {

			std::vector < std::function < void (control *, _param_tv...) > > handlers;

			inline void invoke (control * sender, _param_tv ... params) {
				for (auto f : handlers) {
					f (sender, params...);
				}
			}

			inline void operator () (control * sender, _param_tv ... params) {
				invoke (sender, params ...);
			}

			inline void operator += (const std::function < void (control *, _param_tv...) > & v) {
				handlers.push_back (v);
			}

			inline void operator -= (const std::function < void (control *, _param_tv...) > & v) {
				auto
					it = handlers.begin (),
					end = handlers.end ();

				for (; it != end; ++it) {
					auto & f = *it;

					if (f.target () == v.target ()) {
						handlers.erase (it);
						return;
					}
				}
			}

		};

		struct mouse_event_args {
			vec2 position;
			mouse_button buttons;
		};

		using on_draw_event_type = event < const draw & > ;
		using on_mouse_move_event_type = event < const vec2 & > ;
		using on_mouse_event_type = event < const mouse_event_args & > ;

		class control {
		private:

			control * _parent;

			vec2	_location;
			vec2	_size;

			color	_background_color;

			std::vector < control * > _controls;

			control * find_containing (const vec2 & p);

		protected:

			virtual void on_mouse_move (const vec2 & position);
			virtual void on_mouse_down (const mouse_event_args & args);
			virtual void on_mouse_up   (const mouse_event_args & args);

			virtual void on_draw (const draw & d);

		public:

			on_draw_event_type on_draw_event;
			on_mouse_move_event_type on_mouse_move_event;

			on_mouse_event_type
				on_mouse_down_event,
				on_mouse_up_event;

			control ();
			virtual ~control ();

			control * parent () const;
			control * parent (control * v);

			std::vector < control * > & controls ();
			 
			vec2 location () const;
			vec2 location (const vec2 & v);
			 
			vec2 size () const;
			vec2 size (const vec2 & v);

			color background_color () const;
			color background_color (const color & v);

			rect bounds () const;

			virtual rect to_absolute (const rect & client_rect) const;
			virtual vec2 to_absolute (const vec2 & client_location) const;

			virtual rect to_client (const rect & absolute_rect) const;
			virtual vec2 to_client (const vec2 & absolute_location) const;


		};

	}
}

#endif