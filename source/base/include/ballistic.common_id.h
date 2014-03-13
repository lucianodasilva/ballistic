#ifndef	_ballistic_common_id_h_
#define _ballistic_common_id_h_

#include "ballistic.id.h"

using namespace std;

namespace ballistic {

	namespace id {

		const id_t null							= text_to_id ("null");

		const id_t message_update				= text_to_id ("message_update");

		const id_t game_time					= text_to_id ("game_time");
		const id_t frame_time					= text_to_id ("frame_time");
		const id_t frame_count					= text_to_id ("frame_count");

		// -------------------------------------- 
		const id_t message_terminate			= text_to_id ("message_terminate");

		// -------------------------------------- 
		const id_t message_initialize			= text_to_id ("initialize");

		// -------------------------------------- 
		const id_t message_property_changed	= text_to_id ("message_property_changes");

		const id_t name							= text_to_id ("name");
		const id_t id							= text_to_id ("id");
		const id_t value						= text_to_id ("value");

		// --------------------------------------
		const id_t transform					= text_to_id ("transform");
		const id_t position						= text_to_id ("position");
	}
}

#endif