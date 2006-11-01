/*      $Id$

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2, or (at your option)
        any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

        oroborus - (c) 2001 Ken Lynch
        xfwm4    - (c) 2002-2006 Olivier Fourdan

 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <sys/types.h>
#include <X11/Xlib.h>
#include <glib.h>
#include "screen.h"

#ifndef INC_MISC_H
#define INC_MISC_H

/*
   Just for completion, being a bit pedantic, X seems to be missing
   those so far, so create them for now.
 */
#ifndef Button6
#define Button6 6
#endif

#ifndef Button7
#define Button7 7
#endif

unsigned int getMouseXY (ScreenInfo *, Window, int *, int *);
Window getMouseWindow (ScreenInfo *, Window);
GC createGC (ScreenInfo *, char *, int, XFontStruct *, int, gboolean);
void sendClientMessage (ScreenInfo *, Window, int, Time);
void sendRootMessage (ScreenInfo *, int, long, Time);
gboolean checkWindowOnRoot (ScreenInfo *, Window);
void placeSidewalks(ScreenInfo *, gboolean);
gint find_monitor_at_point (GdkScreen *screen, gint x, gint y);

#endif /* INC_MISC_H */
