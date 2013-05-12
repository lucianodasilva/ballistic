#ifndef	_ballistic_graphics_common_id_h_
#define _ballistic_graphics_common_id_h_

#include <functional>

using namespace std;

namespace ballistic {
	namespace graphics {
		namespace id {

			const id_t message_render				= string_to_id ("message_render");

			const id_t render_device				= string_to_id ("render_device");
			const id_t mesh							= string_to_id ("mesh");
			const id_t material						= string_to_id ("material");
			const id_t projection					= string_to_id ("projection");
			
		}
	}
}

#endif