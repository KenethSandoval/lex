#include <X11/Xlib.h> 
#define win	   (client *t=0, *c=list; c && t!=list->prev; t=c, c=c->next)
#define ws_save(W) ws_list[W] = list
#define ws_sel(W)  list = ws_list[ws = W]
#define MAX(a,b)   ((a) > (b) ? (a) : (b))

#define win_size(W, gx, gy, gw, gh) \
	XGetGeometry(d, W, &(Window){0}, gx, gy, gw, gh \
			&(unsigned int){0}, &(unsigned int){0})

// Credits DWM.
#define mod_clean(mask) (mask & ~(numlock|LockMask) & \
		(ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
