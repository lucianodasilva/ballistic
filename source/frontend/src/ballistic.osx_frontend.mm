#include "ballistic.base.h"

#ifdef BALLISTIC_OS_DARWIN

#import "ballistic.osx_frontend.h"
#import "ballistic.osx_frontend_native.h"
#import <AppKit/AppKit.h>

namespace ballistic {
	namespace osx_desktop {
		
		frontend::frontend ( ) :
			_window_instance(nullptr),
			_window_controller (nullptr),
			_game_instance (nullptr)
		{}
		
		frontend::~frontend () {}
		
		bool frontend::initialize(ballistic::game *game_instance, const point & window_size ) {
			
			_game_instance = game_instance;
			
			_window_instance = [[NSWindow alloc]
							initWithContentRect: NSMakeRect ( 10, 10, window_size.x, window_size.y )
							styleMask : (NSTitledWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask )
							backing:NSBackingStoreBuffered
							defer:NO
						 ];
			
			[_window_instance cascadeTopLeftFromPoint:NSMakePoint (20, 20)];
			[_window_instance setTitle:@""];
			[_window_instance makeKeyAndOrderFront:nil];
			
			if (_window_instance == nil)
				return false;
			
			_window_controller = [[ballistic_window_controller alloc] initWithGame : _window_instance : _game_instance];
			
			if (_window_controller == nil)
				return false;
			
			[_window_controller show_window];
			
			return true;
		}
		
		void frontend::terminate () {
			[_window_instance dealloc];
			_window_instance = nil;
			[_window_controller close_window];
		}
		
		void frontend::do_event_loop() {
			[NSApplication sharedApplication];
			[NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
			[NSApp activateIgnoringOtherApps:YES];
			[NSApp run];
		}
		
	}
}


#endif