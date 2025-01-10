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

#include "tool_bname.h"

#include "memdebug.h" /* keep this as LAST include */

#ifndef HAVE_BASENAME

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
~  

char *tool_basename(char *path)
{
  char *s1;
  char *s2;

  s1 = strrchr(path, '/');
  s2 = strrchr(path, '\\');

  if(s1 && s2) {
    path = (s1 > s2) ? s1 + 1 : s2 + 1;
  }
  else if(s1)
    path = s1 + 1;
  else if(s2)
    path = s2 + 1;

  return path;
}

#endif /* HAVE_BASENAME */
