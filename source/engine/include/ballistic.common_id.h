#ifndef	_ballistic_engine_common_id_h_
#define _ballistic_engine_common_id_h_

#include <functional>

using namespace std;

namespace ballistic {

#	define to_id(x) \
	hash < string > ()(x)

	namespace id {
		const auto message_update				= to_id ("message_update");

		const auto game_time					= to_id ("game_time");
		const auto frame_time					= to_id ("frame_time");
		const auto frame_count					= to_id ("frame_count");

		// -------------------------------------- 
		const auto message_terminate			= to_id ("message_terminate");

		// -------------------------------------- 
		const auto message_initialize			= to_id ("initialize");

		// -------------------------------------- 
		const auto message_attribute_changed	= to_id ("message_attribute_changes");

		const auto name							= to_id ("name");
		const auto id							= to_id ("id");
		const auto value						= to_id ("value");

		// --------------------------------------
		const auto transform					= to_id ("transform");
	}
}

#	undef to_id

#endif