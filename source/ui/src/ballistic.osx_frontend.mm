#include "ballistic.base.h"

#ifdef BALLISTIC_OS_DARWIN

#include <OpenGL/gl.h>
#import "ballistic.osx_frontend.h"

@implementation osx_view

- (id)initWithFrame:(NSRect)frame
{
	self = [super initWithFrame:frame];
 //below code helps optimize Open GL context
 // initialization for the best available resolution
 // important for Retina screens for example
	if (self) {
		[self wantsBestResolutionOpenGLSurface];
	}
	return self;
}
- (void)prepareOpenGL
{
	// Synchronize buffer swaps with vertical refresh rate
	GLint swapInt = 1;
	[[self openGLContext]
	 setValues:&swapInt
	 forParameter:NSOpenGLCPSwapInterval];
	//renderer.init();
}
-(void)awakeFromNib
{
	//when UI is created and properly initialized,
	// we set the timer to continual, real-time rendering
	//a 1ms time interval
	renderTimer = [NSTimer timerWithTimeInterval:0.001
										  target:self
										selector:@selector(timerFired:)
										userInfo:nil
										 repeats:YES];
	
	[[NSRunLoop currentRunLoop] addTimer:renderTimer
								 forMode:NSDefaultRunLoopMode];
	//Ensure timer fires during resize
	[[NSRunLoop currentRunLoop]
	 addTimer:renderTimer
	 forMode:NSEventTrackingRunLoopMode];
}
// Timer callback method
- (void)timerFired:(id)sender
{
	// it's the update routine for our C/C++ renderer
	//renderer.update();
	//it sets the flag that windows has to be redrawn
	[self setNeedsDisplay:YES];
}
// Each time window has to be redrawn, this method is called
- (void)drawRect:(NSRect)bounds
{
	//below code sets the viewport of Open GL context into
	//correct size (assuming resize, fullscreen operations may trigger change)
	NSRect backingBounds = [self convertRectToBacking:[self bounds]];
	glViewport(0,0, backingBounds.size.width, backingBounds.size.height);
 //our renderer's drawing routine
	//renderer.render();
}

@end


#endif