#ifndef	_ballistic_mac_frontend_h_
#define _ballistic_mac_frontend_h_

#ifndef _WIN32

#include <GL/glew.h>

class frontend : public ballistic::ifrontend {
private:

	int _window_width, _window_height;
	update_callback _callback;
		
	static void update_frame ();
			
public:

	frontend (int width, int height);
	virtual ~frontend ();

	virtual bool create ();

	virtual void show ();
	virtual void destroy ();
			
	virtual void update ();

	virtual void do_event_loop (update_callback callback);
			
};


#endif
#endif