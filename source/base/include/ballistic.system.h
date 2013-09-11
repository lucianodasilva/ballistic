#ifndef	_ballistic_system_h_
#define _ballistic_system_h_

#include <chrono>

namespace ballistic {
	namespace system {

		typedef std::chrono::time_point < std::chrono::high_resolution_clock > ballistic_time_t;

		ballistic_time_t get_time_now ();

		double get_elapsed_seconds ( ballistic_time_t & t );

	}
}

#endif