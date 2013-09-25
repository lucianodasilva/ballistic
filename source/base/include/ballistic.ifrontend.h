#ifndef	_ballistic_ifrontend_h_
#define _ballistic_ifrontend_h_

#include "ballistic.math.rect.h"

namespace ballistic {

	class igame;

	class ifrontend {
	public:

		virtual point get_client_size () = 0;

		virtual ~ifrontend ();

		/* 
		create whatever window or whatnot
		that where to present the visual field
		of the engine.
		*/
		virtual bool create () = 0;

		virtual void show () = 0;
		virtual void destroy () = 0;

		virtual void update (ballistic::igame * game) = 0;

		virtual void do_event_loop (ballistic::igame * game) = 0;

		virtual const vec2 & size () const;

	};

}


#endif