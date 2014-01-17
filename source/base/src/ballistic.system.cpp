#include "ballistic.system.h"

namespace ballistic {
	namespace system {

		ballistic_time_t get_time_now () {
			return std::chrono::high_resolution_clock::now ();
		}

		real get_elapsed_seconds ( ballistic_time_t & t ) {
			auto t_now = std::chrono::high_resolution_clock::now ();
			return real (std::chrono::duration_cast <std::chrono::milliseconds> (t_now - t).count () / 1000.0);
		}

	}
}