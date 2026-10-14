/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int swterminheritfs    = 1;        /* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Misc Tamzen:size=10" };
static const char dmenufont[]       = "Misc Tamzen:size=10";
static const char col_gray1[]       = "#424242";
static const char col_gray2[]       = "#575757";
static const char col_gray3[]       = "#e4e4e4";
static const char col_gray4[]       = "#eeeeee";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_gray2, col_gray3 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,            0,         1,          0,           0,        -1 },
	{ "Firefox",  NULL,       NULL,            1 << 8,    0,          0,          -1,        -1 },
	{ "St",       NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_y,      setlayout,      {.v = &layouts[1]} }, /* toggle */
	{ MODKEY,           		XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,			XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY,            		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,			XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,			XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,			XK_space,  zoom,           {0} },
	{ MODKEY,			XK_0,	   view,           {.ui = ~0 } },
	{ MODKEY,			XK_Tab,    view,           {0} },
	{ MODKEY,			XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,		XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,		XK_0,	   tag,            {.ui = ~0 } },
	{ MODKEY,			XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,			XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Right,  tagmon,         {.i = +1 } },
	{ Mod1Mask, 			XK_Tab,    altTab, 	   {0} },
	{ MODKEY|ControlMask,           XK_1,	   tagandview,	   {.ui = 1 << 0} },
	{ MODKEY|ControlMask,           XK_2,	   tagandview,	   {.ui = 1 << 1} },
	{ MODKEY|ControlMask,           XK_3,	   tagandview,	   {.ui = 1 << 2} },
	{ MODKEY|ControlMask,           XK_4,	   tagandview,	   {.ui = 1 << 3} },
	{ MODKEY|ControlMask,           XK_5,	   tagandview,	   {.ui = 1 << 4} },
	{ MODKEY|ControlMask,           XK_6,	   tagandview,	   {.ui = 1 << 5} },
	{ MODKEY|ControlMask,           XK_7,	   tagandview,	   {.ui = 1 << 6} },
	{ MODKEY|ControlMask,           XK_8,	   tagandview,	   {.ui = 1 << 7} },
	{ MODKEY|ControlMask,           XK_9,	   tagandview,	   {.ui = 1 << 8} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

