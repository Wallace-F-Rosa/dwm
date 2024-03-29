/*  ____ References _____ :  */
/* distrotube channal : http://www.youtube.com/c/DistroTube http://www.gitlab.com/dwt1/ */

/* See LICENSE file for copyright and license details. */
/* appearance */
static const unsigned int borderpx = 4;   /* border pixel of windows */
static const unsigned int snap     = 32;  /* snap pixel */
static const unsigned int gappx    = 0;   /* pixel gap between clients */
static const int showbar           = 1;   /* 0 means no bar */
static const int topbar            = 1;   /* 0 means bottom bar */
static const int horizpadbar       = 10;   /* horizontal padding for statusbar */
static const int vertpadbar        = 10;   /* vertical padding for statusbar */
static const int usealtbar          = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "$HOME/.local/bin/bar"; /* Alternate bar launch command */
/* Mononoki Nerd Font must be installed from AUR nerd-fonts-complete.
 * Otherwise, your default font will be Hack which is found in the standard
 * Arch repos and is listed as a dependency for this build. JoyPixels is also
 * a hard dependency and makes colored fonts and emojis possible.
 */
static const char *fonts[]     = {
    "Noto Color Emoji:size=13:antialias=true:autohint=true",
    "FontAwesome:size=13:antialias=true:autohint=true"
};
static const char col_1[]  = "#282c34"; /* background color of bar */
static const char col_2[]  = "#282c34"; /* border color unfocused windows */
static const char col_3[]  = "#d7d7d7";
static const char col_4[]  = "#000051"; /* border color focused tags */
static const char col_5[]  = "#514aac"; /* border color focused window */
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xee; 
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_3, col_1, col_2 },
    [SchemeSel]  = { col_3, col_4,  col_5 },
};
static const unsigned int alphas[][3] = {
    /*               fg      bg        border     */
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging with emojis */
   static const char *tags[] = { "\uf121", "", "", "", "", "", "\uf11b", "", "\uf392"};
/* tagging with numbers */
/*static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7"};*/

/* startup command */
static const char startup[] = "$HOME/.local/bin/autostart";

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       1<<4,            0,           -1 },
    { "Firefox",  NULL,       NULL,       1<<1,            0,           -1 },
    { NULL,     NULL,       "Google Chrome",       1<<1,            0,           -1 },
    { "Telegram", NULL,       NULL,       1<<2,            0,           -1 },
    { "nautilus", NULL,       NULL,       1<<4,            0,           -1 },
    { "Spotify",  NULL,       NULL,       1<<3,            0,           -1 },
    { "obs",      NULL,       NULL,       1<<5,            0,           -1 },
    { "Lutris",   "lutris",   NULL,       1<<6,            0,           -1 },
    { "kdenlive", NULL,       NULL,       1<<4,            0,           -1 },
    { "remmina",  NULL,       NULL,       1<<3,            0,           -1 },
    { "Steam",   "Steam",     NULL,       1<<6,            0,           -1 }
};


/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "HHH",      grid },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };
/* If you are using the dmenu-distrotube-git program, use the following for a cooler dmenu! */
/* static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "48", "-p", "Run: ", NULL }; */

/* the st terminal with tabbed */
static const char *termcmd[]     = { "xfce4-terminal", NULL };
/* An alternative way to launch st along with the fish shell */
/* static const char *termcmd[]     = { "st", "-e fish", NULL }; */
static const char *tabtermcmd[]  = { "tabbed", "-r", "2", "xfce4-terminal", "-w", "''", NULL };

static Key keys[] = {
    /* modifier             key        function        argument */
    { MODKEY|ShiftMask,     XK_Return, spawn,          {.v = dmenucmd } },
    { MODKEY,               XK_Return, spawn,          {.v = termcmd } },
    { Mod1Mask,             XK_Return, spawn,          {.v = tabtermcmd } },
    { MODKEY,               XK_b,      togglebar,      {0} },
    { MODKEY|Mod1Mask,     XK_j,      rotatestack,    {.i = +1 } },
    { MODKEY|Mod1Mask,     XK_k,      rotatestack,    {.i = -1 } },
    { MODKEY,               XK_j,      focusstackvis,     {.i = +1 } },
    { MODKEY,               XK_k,      focusstackvis,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
    { MODKEY,               XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,               XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY,               XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,               XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ControlMask,   XK_Return, zoom,           {0} },
    { MODKEY,               XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,     XK_c,      killclient,     {0} },

    /* Layout manipulation */
    { MODKEY,               XK_Tab,    cyclelayout,    {.i = -1 } },
    { MODKEY|ShiftMask,     XK_Tab,    cyclelayout,    {.i = +1 } },
    { MODKEY,               XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,     XK_space,  togglefloating, {0} },

    /* Switch to specific layouts */
    { MODKEY,               XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,               XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,               XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,               XK_g,      setlayout,      {.v = &layouts[3]} },

    { MODKEY,               XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
    { MODKEY,               XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,               XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period, tagmon,         {.i = +1 } },

    /* Minimize/Maximize Windows */
    { MODKEY, XK_n,      hide,          {0} },
    { MODKEY, XK_s,      show,          {0} },

        TAGKEYS(                  XK_1,          0)
        TAGKEYS(                  XK_2,          1)
        TAGKEYS(                  XK_3,          2)
        TAGKEYS(                  XK_4,          3)
        TAGKEYS(                  XK_5,          4)
        TAGKEYS(                  XK_6,          5)
        TAGKEYS(                  XK_7,          6)
        TAGKEYS(                  XK_8,          7)
        TAGKEYS(                  XK_9,          8)
        { MODKEY|ShiftMask,       XK_q,	   quit,		   {0} },
        { MODKEY|ShiftMask,       XK_r,    quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click           event mask   button          function        argument */
    { ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
    { ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,     0,           Button2,        zoom,           {0} },
    { ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
    { ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
    { ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
    { ClkTagBar,       0,           Button1,        view,           {0} },
    { ClkTagBar,       0,           Button3,        toggleview,     {0} },
    { ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
    { ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};


