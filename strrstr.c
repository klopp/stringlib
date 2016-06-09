/*
 * strrstr.c, part of "stringlib" project.
 *
 *  Created on: 05.06.2015, 18:45
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char *strrstr(const char *haystack, const char *needle) {
    size_t hlen = strlen(haystack);
    size_t nlen = strlen(needle);
    const char *ptr;
    if(hlen < nlen) {
        return NULL;
    }
    ptr = haystack + hlen - nlen;
    while(ptr >= haystack) {
        if(*ptr == *needle && !memcmp(ptr, needle, nlen)) {
            return (char *)ptr;
        }
        ptr--;
    }
    return NULL;
}

