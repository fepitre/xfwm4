/*
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; You may only use version 2 of the License,
	you have no option to use any other version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

        oroborus - (c) 2001 Ken Lynch
        xfwm4    - (c) 2002 Olivier Fourdan

 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xmd.h>
#include <X11/cursorfont.h>
#include <X11/extensions/shape.h>
#include <glib.h>
#include <gtk/gtk.h>
#include <libxfcegui4/libxfcegui4.h>
#include "misc.h"
#include "hints.h"
#include "keyboard.h"
#include "settings.h"
#include "pixmap.h"

#define ANY				0
#define WINDOW				1
#define FRAME				2

#define APPLY				1
#define REMOVE				-1

#define PLACEMENT_MOUSE			0
#define PLACEMENT_ROOT			1

#define INCLUDE_HIDDEN			(1<<0)
#define INCLUDE_SKIP_FOCUS		(1<<1)
#define INCLUDE_ALL_WORKSPACES		(1<<2)
#define INCLUDE_SKIP_PAGER		(1<<3)
#define INCLUDE_SKIP_TASKBAR		(1<<4)

#define UPDATE_NONE			0
#define UPDATE_KEYGRABS			(1<<0)
#define UPDATE_FRAME			(1<<1)
#define UPDATE_GRAVITY			(1<<2)
#define UPDATE_ALL			(UPDATE_KEYGRABS | UPDATE_FRAME | UPDATE_GRAVITY)

#define ACTIVE				0
#define INACTIVE			1
#define PRESSED				2

#define MARGIN_LEFT			0
#define MARGIN_RIGHT			1
#define MARGIN_TOP			2
#define MARGIN_BOTTOM			3

#define CLIENT_MIN_VISIBLE              5

#define CLIENT_FLAG_FOCUS	       (1L<<0)
#define CLIENT_FLAG_ABOVE	       (1L<<1)
#define CLIENT_FLAG_BELOW	       (1L<<2)
#define CLIENT_FLAG_FULLSCREEN         (1L<<3)
#define CLIENT_FLAG_HAS_BORDER         (1L<<4)
#define CLIENT_FLAG_HAS_MENU 	       (1L<<5)
#define CLIENT_FLAG_HAS_MAXIMIZE       (1L<<6)
#define CLIENT_FLAG_HAS_CLOSE	       (1L<<7)
#define CLIENT_FLAG_HAS_HIDE           (1L<<8)
#define CLIENT_FLAG_HAS_MOVE           (1L<<9)
#define CLIENT_FLAG_HAS_RESIZE         (1L<<10)
#define CLIENT_FLAG_IS_RESIZABLE       (1L<<11)
#define CLIENT_FLAG_HAS_STRUTS         (1L<<12)
#define CLIENT_FLAG_HIDDEN	       (1L<<13)
#define CLIENT_FLAG_MANAGED	       (1L<<14)
#define CLIENT_FLAG_MAXIMIZED_VERT     (1L<<15)
#define CLIENT_FLAG_MAXIMIZED_HORIZ    (1L<<16)
#define CLIENT_FLAG_MAXIMIZED          (CLIENT_FLAG_MAXIMIZED_VERT | CLIENT_FLAG_MAXIMIZED_HORIZ)
#define CLIENT_FLAG_SHADED	       (1L<<17)
#define CLIENT_FLAG_SKIP_PAGER         (1L<<18)
#define CLIENT_FLAG_SKIP_TASKBAR       (1L<<19)
#define CLIENT_FLAG_STATE_MODAL        (1L<<20)
#define CLIENT_FLAG_STICKY	       (1L<<21)
#define CLIENT_FLAG_VISIBLE	       (1L<<22)
#define CLIENT_FLAG_WM_DELETE	       (1L<<23)
#define CLIENT_FLAG_WM_INPUT           (1L<<24)
#define CLIENT_FLAG_WM_TAKEFOCUS       (1L<<25)

/* Convenient macros */
#define CLIENT_FLAG_TEST(c,f)			(c->client_flag & (f))
#define CLIENT_FLAG_TEST_ALL(c,f)		((c->client_flag & (f)) == (f))
#define CLIENT_FLAG_TEST_AND_NOT(c,f1,f2)	((c->client_flag & (f1 | f2)) == (f1))
#define CLIENT_FLAG_SET(c,f)			(c->client_flag |= (f))
#define CLIENT_FLAG_UNSET(c,f)			(c->client_flag &= ~(f))
#define CLIENT_FLAG_TOGGLE(c,f)			(c->client_flag ^= (f))

#define CLIENT_CAN_HIDE_WINDOW(c)	(!(c->transient_for) && CLIENT_FLAG_TEST_AND_NOT(c, CLIENT_FLAG_HAS_HIDE, CLIENT_FLAG_SKIP_TASKBAR))
#define CLIENT_CAN_MAXIMIZE_WINDOW(c)	CLIENT_FLAG_TEST_ALL(c, CLIENT_FLAG_HAS_MAXIMIZE | CLIENT_FLAG_HAS_RESIZE | CLIENT_FLAG_IS_RESIZABLE)

typedef enum
{
    UNSET = 0,
    WINDOW_NORMAL = (1 << 0),
    WINDOW_DESKTOP = (1 << 1),
    WINDOW_DOCK = (1 << 2),
    WINDOW_DIALOG = (1 << 3),
    WINDOW_MODAL_DIALOG = (1 << 4),
    WINDOW_TOOLBAR = (1 << 5),
    WINDOW_MENU = (1 << 6),
    WINDOW_UTILITY = (1 << 7),
    WINDOW_SPLASHSCREEN = (1 << 8)
}
WindowType;

typedef struct _Client Client;

struct _Client
{
    Window window;
    Window frame;
    Window transient_for;
    Window *cmap_windows;
    Window title;
    Window sides[3];
    Window corners[4];
    Window buttons[BUTTON_COUNT];
    Colormap cmap;
    unsigned long win_hints;
    unsigned long win_state;
    unsigned long win_layer;
    int win_workspace;
    Atom type_atom;
    XSizeHints *size;
    XWMHints *wmhints;
    Client *next;
    Client *prev;
    WindowType type;
    int x;
    int y;
    int width;
    int height;
    int border_width;
    unsigned int ignore_unmap;
    int old_x;
    int old_y;
    int old_width;
    int old_height;
    int fullscreen_old_x;
    int fullscreen_old_y;
    int fullscreen_old_width;
    int fullscreen_old_height;
    int fullscreen_old_layer;
    int initial_layer;
    int ncmap;
    int button_pressed[BUTTON_COUNT];
    int struts[4];
    char *name;
    unsigned long client_flag;
};

extern Client *clients;
extern Window *client_list;
extern unsigned int client_count;

void clientSetNetState(Client *);
void clientUpdateNetState(Client *, XClientMessageEvent *);
void clientGetNetWmType(Client * c);
void clientCoordGravitate(Client *, int, int *, int *);
void clientGravitate(Client *, int);
void clientConfigure(Client *, XWindowChanges *, int);
void clientUpdateMWMHints(Client *);
void clientFrame(Window);
void clientUnframe(Client *, int);
void clientFrameAll();
void clientUnframeAll();
void clientGetNetStruts(Client *);
void clientInstallColormaps(Client *);
void clientUpdateColormaps(Client *);
void clientUpdateAllFrames(int);
void clientGrabKeys(Client *);
void clientUngrabKeys(Client *);
Client *clientGetFromWindow(Window, int);
Client *clientGetNext(Client *, int);
void clientShow(Client *, int);
void clientHide(Client *, int);
void clientHideAll(Client *);
void clientClose(Client *);
void clientKill(Client *);
void clientRaise(Client *);
void clientLower(Client *);
void clientSetLayer(Client *, int);
void clientSetWorkspace(Client *, int, gboolean);
void clientToggleShaded(Client *);
void clientStick(Client *);
void clientUnstick(Client *);
void clientToggleSticky(Client *);
inline void clientRemoveMaximizeFlag(Client *);
void clientToggleMaximized(Client *, int);
void clientUpdateFocus(Client *);
inline gboolean clientAcceptFocus(Client * c);
void clientSetFocus(Client *, int);
Client *clientGetFocus();
void clientMove(Client *, XEvent *);
void clientResize(Client *, int, XEvent *);
void clientCycle(Client *);
void clientButtonPress(Client *, Window, XButtonEvent *);

#endif /* __CLIENT_H__ */
