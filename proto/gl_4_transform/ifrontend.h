#ifndef	_ifrontend_h_
#define _ifrontend_h_

typedef void (*update_callback) ();

class ifrontend {
	public:

	virtual ~ifrontend () {}

	/* 
	create whatever window or whatnot
	that where to present the visual field
	of the engine.
	*/
	virtual bool create () = 0;

	virtual void show () = 0;
	virtual void destroy () = 0;

	virtual void update () = 0;

	virtual void do_event_loop (update_callback callback) = 0;

};



#endif