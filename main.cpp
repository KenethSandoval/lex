#include <X11/Xlib.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <functional>

auto main() -> int {
  //initialize Display connection with a smart pointer
  auto dpy = std::unique_ptr<Display, std::function<void(Display*)>>(
      XOpenDisplay(0), XFlush);
  const char *msg = "Hello, World!";


  //Create some colors
  int blackColor = BlackPixel(dpy.get(), DefaultScreen(dpy.get()));
  int whiteColor = WhitePixel(dpy.get(), DefaultScreen(dpy.get()));

  int s = DefaultScreen(dpy.get());
  //initialize window
  Window w = XCreateSimpleWindow(dpy.get(), DefaultRootWindow(dpy.get()), 0, 0, 
      200, 100, 0, blackColor, blackColor);


  //Call for map notify events
  XSelectInput(dpy.get(), w, StructureNotifyMask);

  //show window on screen
  XMapWindow(dpy.get(), w);

  GC gc = XCreateGC(dpy.get(), w, 0, nullptr);

  //Set foreground color(for for draw lines later"
  XSetForeground(dpy.get(), gc, whiteColor);

  //wait for MapNotify event so we can proced with draw calls on new window
  while(true) {
    XEvent e;
    XNextEvent(dpy.get(), &e);
    if(e.type == Expose) {
	    XFillRectangle(dpy.get(), w, DefaultGC(dpy.get(), s), 20, 20, 10, 10);
            XDrawString(dpy.get(), w, DefaultGC(dpy.get(), s), 10, 50, msg, strlen(msg));
    }

    if (e.type == KeyPress) {
	    break;
    }
  }

  XCloseDisplay(dpy.get());

  return 0;
}
