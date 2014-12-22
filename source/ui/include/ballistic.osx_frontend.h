#ifndef	_ballistic_osx_frontend_h_
#define _ballistic_osx_frontend_h_

#ifdef BALLISTIC_OS_DARWIN

#import <Cocoa/Cocoa.h>

@interface osx_view : NSOpenGLView
{
	NSTimer* renderTimer;
}

@end

#endif
#endif