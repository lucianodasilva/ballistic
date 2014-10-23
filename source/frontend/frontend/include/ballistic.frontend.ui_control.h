#ifndef _ballistic_frontend_ui_control_h_
#define _ballistic_frontend_ui_control_h_

#include <functional>

#include <ballistic.graphics.h>
#include "ballistic.frontend.draw.h"

namespace ballistic {
	namespace frontend {

		class control;

		template < class ... _param_tv >
		struct event {

			using target_type = void (control *, _param_tv...);

			std::vector < std::function < target_type > > handlers;

			inline void invoke (control * sender, _param_tv ... params) {
				for (auto f : handlers) {
					f (sender, params...);
				}
			}

			inline void operator () (control * sender, _param_tv ... params) {
				invoke (sender, params ...);
			}

			inline void operator += (const std::function < target_type > & v) {
				handlers.push_back (v);
			}

			inline void operator -= (const std::function < target_type > & v) {
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

		class control {
		private:

			control * _parent;

		public:

			control ();

			control * parent ();
			control * parent (control * v);

			rect bounds;
			vec2 location;

			virtual rect to_absolute (const rect & client_rect);
			virtual vec2 to_absolute (const vec2 & client_location);

			virtual rect to_parent (const rect & client_rect);
			virtual vec2 to_parent (const vec2 & client_location);

			virtual rect to_client (const rect & absolute_rect);
			virtual vec2 to_client (const vec2 & absolute_location);

			virtual void on_paint (const draw & d);

		};

	}
}

#endif