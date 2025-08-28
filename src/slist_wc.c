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

#ifndef CURL_DISABLE_LIBCURL_OPTION

#include "slist_wc.h"

/* The last #include files should be: */
#include "memdebug.h"

/*
 * slist_wc_append() appends a string to the linked list. This function can be
 * used as an initialization function as well as an append function.
 */
struct slist_wc *slist_wc_append(struct slist_wc *list,
                                 const char *data)
{
  struct curl_slist *new_item = curl_slist_append(NULL, data);

  if(!new_item)
    return NULL;

  if(!list) {
    list = malloc(sizeof(struct slist_wc));

    if(!list) {
      curl_slist_free_all(new_item);
      return NULL;
    }

    list->first = new_item;
    list->last = new_item;
    return list;
  }

  list->last->next = new_item;
  list->last = list->last->next;
  return list;
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

/* be nice and clean up resources */
void slist_wc_free_all(struct slist_wc *list)
{
  if(!list)
    return;

  curl_slist_free_all(list->first);
  free(list);
}

#endif /* CURL_DISABLE_LIBCURL_OPTION */
