/* xscreensaver, Copyright (c) 2006-2012 Jamie Zawinski <jwz@jwz.org>
*
* Permission to use, copy, modify, distribute, and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice appear in all copies and that both that
* copyright notice and this permission notice appear in supporting
* documentation.  No representations are made about the suitability of this
* software for any purpose.  It is provided "as is" without express or 
* implied warranty.
*/

/* This is a subclass of Apple's ScreenSaverView that knows how to run
   xscreensaver programs without X11 via the dark magic of the "jwxyz"
   library.  In xscreensaver terminology, this is the replacement for
   the "screenhack.c" module.
 */

#ifdef USE_IPHONE
# import <Foundation/Foundation.h>
# import <UIKit/UIKit.h>
# define NSView  UIView
# define NSRect  CGRect
# define NSSize  CGSize
# define NSColor UIColor
# define NSImage UIImage
# define NSEvent UIEvent
# define NSWindow UIWindow
#else
# import <Cocoa/Cocoa.h>
# import <ScreenSaver/ScreenSaver.h>
#endif


#import "screenhackI.h"
#import "PrefsReader.h"

#ifdef USE_IPHONE
@interface ScreenSaverView : NSView
- (id)initWithFrame:(NSRect)frame isPreview:(BOOL)isPreview;
- (NSTimeInterval)animationTimeInterval;
- (void)setAnimationTimeInterval:(NSTimeInterval)timeInterval;
- (void)startAnimation;
- (void)stopAnimation;
- (BOOL)isAnimating;
- (void)animateOneFrame;
- (BOOL)hasConfigureSheet;
//- (NSWindow*)configureSheet;
- (UIViewController*)configureView;
- (BOOL)isPreview;
@end

#endif // USE_IPHONE


@interface XScreenSaverView : ScreenSaverView
{
  struct xscreensaver_function_table *xsft;
  PrefsReader *prefsReader;

  BOOL setup_p;		   // whether xsft->setup_cb() has been run
  BOOL initted_p;          // whether xsft->init_cb() has been run
  BOOL resized_p;	   // whether to run the xsft->reshape_cb() soon
  double next_frame_time;  // time_t in milliseconds of when to tick the frame

  // Data used by the Xlib-flavored screensaver
  Display *xdpy;
  Window xwindow;
  void *xdata;
  fps_state *fpst;

# ifdef USE_IPHONE
  UIDeviceOrientation orientation, new_orientation;
  NSTimer *orientation_Timer;
  BOOL screenLocked;

  GLfloat rotation_ratio;	// ratio thru rotation anim, or -1
  NSSize rot_from, rot_to;	// start size rect, end size rect
  GLfloat angle_from, angle_to;	// start angle, end angle
  double rot_start_time;

  NSSize rot_current_size;
  GLfloat rot_current_angle;

  CGContextRef backbuffer;
  NSSize backbuffer_size;

  NSTimer *crash_timer;

# endif // USE_IPHONE

}

- (id)initWithFrame:(NSRect)frame saverName:(NSString*)n isPreview:(BOOL)p;

- (void) render_x11;
- (void) prepareContext;
- (void) resizeContext;
- (NSUserDefaultsController *) userDefaultsController;

#ifdef USE_IPHONE
- (void)didRotate:(NSNotification *)notification;
- (void)setScreenLocked:(BOOL)locked;
- (void)createBackbuffer;
#endif // USE_IPHONE

@end
