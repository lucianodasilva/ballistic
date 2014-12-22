//
//  osx_frontend_native.h
//  ballistic
//
//  Created by Luciano da Silva on 17/12/14.
//
//

#ifndef ballistic_osx_frontend_native_h
#define ballistic_osx_frontend_native_h

#include <ballistic.base.h>
#import <Foundation/Foundation.h>
#import <Foundation/NSObject.h>
#import <Cocoa/Cocoa.h>

@class NSNotification;

@protocol ballistic_window_interface_protocol

-(void)show_window;
-(void)close_window;

@end

@interface ballistic_opengl_view : NSOpenGLView
{
	CVDisplayLinkRef	_displayLink;
	ballistic::game *	_game_instance;
}

-(id)initWithGame:(NSRect)frameRect : (ballistic::game *) game_instance;

@end

@interface ballistic_window_controller : NSResponder < ballistic_window_interface_protocol, NSWindowDelegate >
{
	NSWindow *		_window;
	NSOpenGLView *	_gl_view;
}

-(id)initWithGame : (NSWindow*)window : (ballistic::game *) game_instance;

@end

@interface ballistic_app_controller : NSObject
{
	NSWindow * _window;
}

- (void)applicationWillFinishLaunching:(NSNotification *) notification;
- (void)applicationDidFinishLaunching:(NSNotification *) notification;


@end

#endif
