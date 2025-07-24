/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include "tool_setup.h"

#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif

#include "terminal.h"

#include "memdebug.h" /* keep this as LAST include */

#ifdef HAVE_TERMIOS_H
#  include <termios.h>
#elif defined(HAVE_TERMIO_H)
#  include <termio.h>
#endif



/*
 * get_terminal_columns() returns the number of columns in the current
 * terminal. It will return 79 on failure. Also, the number can be very big.
 */

unsigned int get_terminal_columns(void)
{
  unsigned int width = 0;
  char *colp = curl_getenv("COLUMNS");
  if(colp) {
    char *endptr;
    long num = strtol(colp, &endptr, 10);
    if((endptr != colp) && (endptr == colp + strlen(colp)) && (num > 20) &&
       (num < 10000))
      width = (unsigned int)num;
//    curl_free(colp);
  }

  if(!width) {
    int cols = 0;

#ifdef TIOCGSIZE
    struct ttysize ts;
    if(!ioctl(STDIN_FILENO, TIOCGSIZE, &ts))
      cols = ts.ts_cols;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    if(!ioctl(STDIN_FILENO, TIOCGWINSZ, &ts))
      cols = (int)ts.ws_col;
#elif defined(_WIN32) && !defined(CURL_WINDOWS_APP)
    {
      HANDLE  stderr_hnd = GetStdHandle(STD_ERROR_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO console_info;

      if((stderr_hnd != INVALID_HANDLE_VALUE) &&
         GetConsoleScreenBufferInfo(stderr_hnd, &console_info)) {
        /*
         * Do not use +1 to get the true screen-width since writing a
         * character at the right edge will cause a line wrap.
         */
        cols = (int)
          (console_info.srWindow.Right - console_info.srWindow.Left);
      }
    }
#endif /* TIOCGSIZE */
    if(cols >= 0 && cols < 10000)
      width = (unsigned int)cols;
  }
  if(!width)
    width = 79;
  return width; /* 79 for unknown, might also be very small or very big */
}

// The following is copied from GNU Chess 5.0.8
char *return_append_str(char *dest, const char *s) {
/* Append text s to dest, and return new result. */
        char *new_loc;
        size_t new_len;
        /* This doesn't have buffer overflow vulnerabilities, because
           we always allocate for enough space before appending. */
        if (!dest) {
                new_loc = (char *) malloc(strlen(s))+1;
                strcpy(new_loc, s);
                return new_loc;
        }
        new_len = strlen(dest) + strlen(s) + 1;
        new_loc = (char *) malloc(new_len);
        strcpy(new_loc, dest);
        if (!new_loc) return dest; /* Can't do it, throw away the data */
        strcat(new_loc, s);
        return new_loc;
}
