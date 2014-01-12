/*
 * \file dti.c
 * \author Wei Yongming <ymwei@minigui.org>
 * \date 1998/12/xx
 *
 * This file defines the desktop interface funtions.  You should always 
 * include the file in your projects for MiniGUI-Threads.
 *
 \verbatim

    Copyright (C) 2002-2006 Feynman Software.
    Copyright (C) 1999-2002 Wei Yongming.
  
    All rights reserved by Feynman Software.

    This file is part of MiniGUI, a compact cross-platform Graphics 
    User Interface (GUI) support system for real-time embedded systems.

 \endverbatim
 */

/*
 * $Id: dti.c 6812 2006-06-11 04:20:45Z weiym $
 *
 *             MiniGUI for Linux/uClinux, eCos, uC/OS-II, VxWorks, 
 *                     pSOS, ThreadX, NuCleus, OSE, and Win32.
 *
 *             Copyright (C) 2002-2006 Feynman Software.
 *             Copyright (C) 1998-2002 Wei Yongming.
 */

#include <minigui/common.h>

#ifndef _LITE_VERSION

#ifdef __WINBOND_SWLINUX__

int user_thread (int (*)(char **), char **, unsigned long);
int minigui_entry (int argc, const char* argv[]);

int start_minigui (char **data)
{
    return minigui_entry (0, NULL);
}

void Start (void)
{
    user_thread (start_minigui, (char**)NULL, 0);
}

#endif /* __WINBOND_SWLINUX__ */

#endif /* !_LITE_VERSION */

