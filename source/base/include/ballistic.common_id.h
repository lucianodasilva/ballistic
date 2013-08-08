#ifndef	_ballistic_engine_common_id_h_
#define _ballistic_engine_common_id_h_

#include "ballistic.id.h"

using namespace std;

namespace ballistic {

	namespace id {
		const id_t message_update				= string_to_id ("message_update");

		const id_t game_time					= string_to_id ("game_time");
		const id_t frame_time					= string_to_id ("frame_time");
		const id_t frame_count					= string_to_id ("frame_count");

		// -------------------------------------- 
		const id_t message_terminate			= string_to_id ("message_terminate");

		// -------------------------------------- 
		const id_t message_initialize			= string_to_id ("initialize");

		// -------------------------------------- 
		const id_t message_property_changed	= string_to_id ("message_property_changes");

		const id_t name							= string_to_id ("name");
		const id_t id							= string_to_id ("id");
		const id_t value						= string_to_id ("value");

		// --------------------------------------
		const id_t transform					= string_to_id ("transform");
	}
}

#endif