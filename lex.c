#include <X11/Xlib.h>
#include <X11/XF86keysym.h>
#include <X11/XKBlib.h>

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <memory>
#include <functional>

#include "lex.hpp"

static client 		*list = {0}, *ws_list[10] = {0}, *cur;
static int 		ws = 1, sw, sh, wx, wy, numlock = 0;
static unsigned int 	ww, wh;

auto d = std::unique_ptr<Display, std::function<void(Display*)>> (XOpenDisplay(0), XFlush);
static XButtonEvent 	mouse;
static Window 		root;

static void(*events[LASTEvent])(XEvent *e) = {
	[ButtonPress] 		= button_press,
	[ButtonRelease]		= button_release,
	[ConfigureRequest]	= configure_request,
	[KeyPress]		= key_press,
	[MapRequest]		= map_request,
	[MappingNotify]		= mapping_notify,
	[DestroyNotify]		= notify_destroy,
	[EnterNotify]		= notify_enter,
	[MotionNotify]		= notify_motion
};

void win_focus(client *c) {
	cur = c;
	XSetInputFocus(d.get(), cur->w, RevertToParent, CurrentTime);
}

void notify_destroy(XEvent *e) {
	win_del(e->xdestroywindow.window);

	if(list) win_focus(list->prev);
}

auto main() -> int {
	XEvent ev;

	if(!(d.get())) exit (1);

	signal(SIGCHLD, SIG_IGN);
}
