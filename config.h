/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 20;       /* gaps between windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	//"Cascadia Code:style=regular:pixelsize=18:antialias=true:autohint=true",
	"Cascadia Code:style=SemiLight:size=12:antialias=true:autohint=true",
	//"Terminus:size=14:antialias=true:autohint=true",
	/* "Misc Tamsyn:style=Regular:pixelsize=15", */
	"Noto Emoji:size=10",
	"monospace:size=10"
};

static const char col_black[]       = "#32302f";
/* static const char col_black[]       = "#282828"; */
/* static const char col_black[]       = "#000000"; */
static const char col_white[]       = "#ebdbb2";
/* static const char col_white[]       = "#f1f1f1"; */

static const char col_gray[]       = "#928374";
static const char col_red[]        = "#cc241d";
static const char col_green[]      = "#b8bb26";
static const char col_yellow[]     = "#fabd2f";
static const char col_blue[]       = "#83a598";
static const char col_purple[]     = "#d3869b";
static const char col_aqua[]       = "#8ec07c";
static const char col_orange[]     = "#fe8019";

/*
 * Color Reference:
 *   - Spring : March 21     : Aqua
 *   - Summer : June  21     : Yellow
 *   - Fall   : September 21 : Orange
 *   - Winter : December 21  : Red
 */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_black },
	[SchemeSel]  = { col_black, col_white,  col_yellow  },
};


/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5" }; */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",             NULL,       NULL,       0,            1,           -1 },
	{ "Free42",             NULL,       NULL,       0,            1,           -1 },
	{ "alsamixer",          NULL,       NULL,       0,            1,           -1 },
	{ "stdc",               NULL,       NULL,       0,            1,           -1 },
	{ "notes",              NULL,       NULL,       0,            1,           -1 },
	{ "float",              NULL,       NULL,       0,            1,           -1 },
	{ "Brave-browser",      NULL,       NULL,       1 << 0,       0,           -1 },
	{ "jetbrains-phpstorm", NULL,       NULL,       1 << 3,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "()=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "( )",      monocle },
	{ "-O-",    centeredmaster },
	{ ">O>",    centeredfloatingmaster },
};

/*
	{ "><>",      NULL },
	{ "[]=",      tile },
	{ "[M]",      monocle },
*/

/* key definitions */
#include <X11/XF86keysym.h>

#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon };
static const char *sudodmenucmd[] = { "sudo_dmenu_run", "-m", dmenumon };
static const char *dmenuflatpakcmd[] = { "dmenu_flatpak", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *termfloatcmd[]  = { "st_float", NULL };
static const char *slock[]  = { "slock", NULL };
static const char *screenshotlist[]  = { "screen-list", NULL };
static const char *dtime[]  = { "dtime", NULL };
static const char *screenshotsave[]  = { "screen-save", NULL };
static const char *clipmenucmd[] = { "clipmenu" };
static const char *emojimenucmd[]  = { "emojimenu", NULL };
static const char *colorpickercmd[]  = { "colorpicker", NULL };
static const char *alsamenu[]  = { "alsamenu", NULL };
static const char *pavucontrol[]  = { "pavucontrol", NULL };
static const char *notifytoggle[]  = { "notifytoggle", NULL };
static const char *finder[]  = { "finder", NULL };
static const char *stdc[]  = { "stdc", NULL };
static const char *stcalc[]  = { "st_calc", NULL };
static const char *free42[]  = { "free42dec_noheader", NULL };
static const char *keymapmenucmd[]  = { "keymapmenu", NULL };
static const char *notes[]  = { "notes", "menu", NULL };
static const char *images[]  = { "images", NULL };
static const char *dmenurecord[]  = { "dmenurecord", NULL };
static const char *dmenurecordkill[]  = { "dmenurecord", "kill", NULL };
static const char *pomodororun[]  = { "pomodoro-run", NULL };
static const char *pomodorostop[]  = { "pomodoro-stop", NULL };
static const char *backlightplus[]  = { "sudo", "backlight", "+", NULL };
static const char *backlightmin[]  = { "sudo", "backlight", "-", NULL };
static const char *upvol[] = { "amixer", "set", "Master", "5%+", NULL };
static const char *downvol[] = { "amixer", "set", "Master", "5%-", NULL };
static const char *mutevol[] = { "amixerl", "set", "Master", "toggle", NULL };
static const char *fixscreen[] = { "fixscreen", NULL };
static const char *passmenu[] = { "passmenu", NULL };
static const char *maps[] = { "OMaps", NULL };
static const char *stncmpcpp[] = { "st", "-e", "ncmpcpp", NULL };
static const char *stvimwiki[] = { "st", "-e", "vimwiki", NULL };
static const char *wiki[] = { "vimwiki_preview", NULL };
static const char *zettel[] = { "st_zettelkasten", NULL };
static const char *zeal[] = { "zeal", NULL };
static const char *favorite[] = { "favorite", NULL };

static const char *chrome[] = { "chromium", NULL };
static const char *php[] = { "projects_php", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = sudodmenucmd } },
	{ MODKEY,                       XK_x,      spawn,          {.v = colorpickercmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clipmenucmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = emojimenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return, spawn,          {.v = termfloatcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_y,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	//{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ControlMask,           XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ControlMask,           XK_5,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_a,                      0)
	TAGKEYS(                        XK_o,                      1)
	TAGKEYS(                        XK_e,                      2)
	TAGKEYS(                        XK_u,                      3)
	TAGKEYS(                        XK_i,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	// Special Function Keys
	/* modifier                     key        function        argument */
	{ 0,				XF86XK_MonBrightnessUp,		spawn,	{.v = backlightplus} },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,	{.v = backlightmin} },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,	{.v = downvol } },
	{ 0,				XF86XK_AudioMute,			spawn,	{.v = mutevol } },
	{ 0,				XF86XK_AudioRaiseVolume,	spawn,	{.v = upvol   } },
	{ 0,				XF86XK_Favorites,			spawn,	{.v = favorite   } },
	{ 0,				XF86XK_Display,				spawn,	{.v = fixscreen   } },

	// Shortcuts
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_s,      spawn,          {.v = screenshotlist } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshotsave } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = dtime } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slock } },
	{ MODKEY,                       XK_r,      spawn,          {.v = pavucontrol } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = alsamenu } },
	{ MODKEY,                       XK_n,      spawn,          {.v = notes } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = images } },
	{ MODKEY,                       XK_f,      spawn,          {.v = dmenuflatpakcmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = finder } },
	{ MODKEY,                       XK_c,      spawn,          {.v = free42 } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = stcalc } },
	{ MODKEY,                       XK_w,      spawn,          {.v = stvimwiki } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = wiki } },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = keymapmenucmd } },
	{ MODKEY,                       XK_1,      spawn,          {.v = dmenurecord } },
	{ MODKEY|ShiftMask,             XK_1,      spawn,          {.v = dmenurecordkill } },
	{ MODKEY,                       XK_2,      spawn,          {.v = pomodororun } },
	{ MODKEY|ShiftMask,             XK_2,      spawn,          {.v = pomodorostop } },
	{ MODKEY,                       XK_3,      spawn,          {.v = passmenu } },
	{ MODKEY,                       XK_m,      spawn,          {.v = maps } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = stncmpcpp } },
	{ MODKEY,                       XK_z,      spawn,          {.v = zettel } },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          {.v = zeal } },

	// Apps
	/* modifier                     key        function        argument */
	{ MODKEY|ControlMask,           XK_c,      spawn,          {.v = chrome } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = php } },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = slock } },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

