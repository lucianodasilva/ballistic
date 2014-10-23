#include "ballistic.frontend.ui_control.h"

namespace ballistic {
	namespace frontend {

		control::control () :
			_parent (nullptr),
			bounds({0}),
			location ({0})
		{}

		rect control::to_absolute (const rect & client_rect) {
			if (!_parent)
				return client_rect;

			rect temp = {{
				client_rect.position + location,
				client_rect.size
			}};

			return _parent->to_absolute (temp);
		}

		vec2 control::to_absolute (const vec2 & client_location) {
			if (!_parent)
				return client_location;

			vec2 temp = client_location + location;

			return _parent->to_absolute (temp);
		}

		rect control::to_parent (const rect & client_rect) {
			return {
				client_rect.position + location,
				client_rect.size
			};
		}

		vec2 control::to_parent (const vec2 & client_location) {
			return client_location + location;
		}

		rect control::to_client (const rect & absolute_rect) {
			if (!_parent)
				return absolute_rect;

			rect temp = to_absolute (bounds);

			return{
				location - temp.position,
				temp.size
			};
		}

		vec2 control::to_client (const vec2 & absolute_location) {
			if (!_parent)
				return absolute_location;

			return absolute_location - to_absolute (location);
		}

	}
}