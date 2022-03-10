#ifndef CONFIG_H
#define CONFIG_H

#define MOD Mod4Mask

const char* menu[] = {"rofi --show", 0};
const char* term[] = {"alacritty"};

static struct key keys[] = {
	{MOD, XK_q, win_kill, {0}},
	{MOD, XK_f, win_fs,   {0}},

	{MOD, XK_d, run, {.com=menu}},
	{MOD, XK_Return, run, {.com=term}},
};

#endif
