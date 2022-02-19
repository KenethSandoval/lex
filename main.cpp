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

auto main() -> int {
	XEvent ev;

	if(!(d.get())) exit (1);

	signal(SIGCHLD, SIG_IGN);
}
