#ifndef	_ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <functional>

using namespace std;

#	define to_id(x) \
	hash < string > ()(x)

namespace ballistic {
	namespace graphics {
		namespace id {

			const auto message_render				= to_id ("message_render");

			const auto render_system				= to_id ("render_system");
			const auto mesh							= to_id ("mesh");
			const auto material						= to_id ("material");
		}
	}
}

#undef to_id

#endif