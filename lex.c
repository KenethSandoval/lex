#include <X11/Xlib.h>
#include <X11/XF86keysym.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "lex.h"
#include "config.h"

static client 		*list = {0}, *ws_list[10] = {0}, *cur;
static int 		ws = 1, sw, sh, wx, wy, numlock = 0;
static unsigned int 	ww, wh;

static Display *d;
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
	XSetInputFocus(d, cur->w, RevertToParent, CurrentTime);
}

void notify_destroy(XEvent *e) {
	win_del(e->xdestroywindow.window);
}

void notify_enter(XEvent *e) {
	while(XCheckTypedEvent(d, EnterNotify, e));

	for win if (c->w == e->xcrossing.window) win_focus(c);
}

void notify_motion(XEvent *e) {
	if (!mouse.subwindow || cur->f) return;

	while (XCheckTypedEvent(d, MotionNotify, e));

	int xd = e->xbutton.x_root - mouse.x_root;
	int yd = e->xbutton.y_root - mouse.y_root;

	XMoveResizeWindow(d, mouse.subwindow,
			wx + (mouse.button == 1 ? xd : 0),
			wy + (mouse.button == 1 ? yd : -0),
			MAX(1, ww + (mouse.button == 3 ? xd : 0)),
			MAX(1, wh + (mouse.button == 3 ? yd : 0)));
}

void key_press(XEvent *e) {
	KeySym keysym = XkbKeycodeToKeysym(d, e->xkey.keycode, 0, 0);

	for(unsigned int i = 0; i < sizeof(keys)/sizeof(*keys); ++i) {
		if(keys[i].keysym == keysym && mod_clean(keys[i].mod) == mod_clean(e->xkey.state))
			keys[i].function(keys[i].arg);
	}
}

int main(void) {
	XEvent ev;
	printf("Hello world");
}
