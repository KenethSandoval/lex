#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <cstdio>
#include <iostream>
#include <cstring>
#include <memory>
#include <functional>
#include <sys/utsname.h>

auto main() -> int {
  //initialize Display connection with a smart pointer
  auto dpy = std::unique_ptr<Display, std::function<void(Display*)>>(
      XOpenDisplay(0), XFlush);

  if (dpy.get() == NULL) {
	std::cout << "Cannot open display" << std::endl;
	exit(1);
  }

  //Create some colors
  int blackColor = BlackPixel(dpy.get(), DefaultScreen(dpy.get()));
  int whiteColor = WhitePixel(dpy.get(), DefaultScreen(dpy.get()));

  int s = DefaultScreen(dpy.get());
  //initialize window
  Window w = XCreateSimpleWindow(dpy.get(), RootWindow(dpy.get(), s), 10, 10, 660, 200, 1, blackColor, whiteColor);


  //Call for map notify events
  XSelectInput(dpy.get(), w, ExposureMask | KeyPressMask);

  //show window on screen
  XMapWindow(dpy.get(), w);

  XStoreName(dpy.get(), w, "Lex");

  Atom WM_DELETE_WINDOW = XInternAtom(dpy.get(), "WM_DELETE_WINDOW", False);
  XSetWMProtocols(dpy.get(), w, &WM_DELETE_WINDOW, 1);

  bool uname_ok = false;
  struct utsname sname;
  int ret = uname(&sname);

  if (ret != -1) {
	uname_ok = true;
  }

  XEvent e;

  while(1) {
	XNextEvent(dpy.get(), &e);
	if (e.type == Expose) {
		int y_offset = 20;
		const char* s1 = "X11 test app under Linux";

		const char* s2 = "Lex";
		XDrawString(dpy.get(), w, DefaultGC(dpy.get(), s), 10, y_offset, s1, strlen(s1));
		XDrawString(dpy.get(), w, DefaultGC(dpy.get(), s), 10, y_offset, s2, strlen(s2));
		y_offset += 20;

		if (uname_ok) {
			char buf[256] = {0};

			sprintf(buf, "System information: ");
			XDrawString(dpy.get(), w, DefaultGC(dpy.get(), s), 10, y_offset, buf, strlen(buf));
			y_offset += 15;
		}

		XWindowAttributes wa;
		XGetWindowAttributes(dpy.get(), w, &wa);
		int width = wa.width;
		int height = wa.height;
		char buf[128] = {0};
		XDrawString(dpy.get(), w, DefaultGC(dpy.get(), s), 10, y_offset, buf, strlen(buf));
		y_offset += 20;
	}

	if (e.type == KeyPress) {
		char buf[128] = {0};
		KeySym keysym;
		int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
		if(keysym == XK_Escape) {
			break;
		}
	}
	if ((e.type == ClientMessage) &&
			(static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW)) {
		break;
	}
  }

  XDestroyWindow(dpy.get(), w);
  XCloseDisplay(dpy.get());

  return 0;
}
