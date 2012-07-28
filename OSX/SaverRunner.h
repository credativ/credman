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

#ifdef USE_IPHONE
# import <Foundation/Foundation.h>
# import <UIKit/UIKit.h>
# import <OpenGLES/EAGL.h>
# import <OpenGLES/ES1/gl.h>
# import <OpenGLES/ES1/glext.h>
# import <QuartzCore/QuartzCore.h>
# define NSView  UIView
# define NSRect  CGRect
# define NSSize  CGSize
# define NSColor UIColor
# define NSImage UIImage
# define NSEvent UIEvent
# define NSWindow UIWindow
# define NSButton UIButton
# define NSApplication UIApplication
# define NSScreen UIScreen
#else
# import <Cocoa/Cocoa.h>
# import <ScreenSaver/ScreenSaver.h>
#endif

@class ScreenSaverView;

#ifdef USE_IPHONE
# import "SaverListController.h"
#endif

@interface SaverRunner : NSObject
{
  NSString *saverName;		// the one currently loaded
  NSArray  *saverNames;		// Names of available savers
  NSString *saverDir;		// Where we find saver bundles

# ifndef USE_IPHONE

  NSBundle *saverBundle;
  NSArray  *windows;
  IBOutlet NSMenu *menubar;

# else  // USE_IPHONE

  ScreenSaverView *saverView;
  UINavigationController *rootViewController;
  IBOutlet UIWindow *window;
  EAGLContext *eagl_ctx;
  GLuint gl_framebuffer, gl_renderbuffer;
  IBOutlet UIView *view;
  SaverListController *listController;
  UIImage *saved_screenshot;

# endif // USE_IPHONE
}

- (void) aboutPanel: (id)sender;
- (void) openPreferences: (id)sender;
- (void)loadSaver:(NSString *)name launch:(BOOL)launch;
- (void) loadSaver: (NSString *)name;
- (void)selectedSaverDidChange:(NSDictionary *)change;

#ifdef USE_IPHONE
- (void) loadSaverMenu: (id)sender;
- (UIImage *) screenshot;
#endif

@end
