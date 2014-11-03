#ifndef _ballistic_ifrontend_h_
#define _ballistic_ifrontend_h_

#include <ballistic.base.h>

namespace ballistic {

	class ifrontend {
	public:
		virtual ~ifrontend ();

		virtual void show () = 0;
		virtual void close () = 0;

		virtual void run () = 0;

	};

	namespace frontend {
		void define_resources (game & game_inst);
	}

}

#endif