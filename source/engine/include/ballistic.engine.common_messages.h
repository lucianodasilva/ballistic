#ifndef	_ballistic_engine_common_messages_h_
#define _ballistic_engine_common_messages_h_

#include "ballistic.engine.message.h"

#include <functional>

using namespace std;

namespace ballistic {
	namespace engine {

		const auto message_update			= hash < string > ()("message_update");
		const auto message_game_time		= hash < string > ()("message_game_time");
		const auto message_frame_time		= hash < string > ()("message_frame_time");
		const auto message_frame_count		= hash < string > ()("message_frame_count");

		// -----------------------------------------
		const auto message_terminate		= hash < string > () ("message_terminate");

		// -----------------------------------------
		const auto message_initialize		= hash < string > () ("message_initialize");
	}
}

#endif