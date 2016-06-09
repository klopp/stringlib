/*
 * chomp.c, part of "stringlib" project.
 *
 *  Created on: 19 мая 2015 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

size_t chomp(char *s) {
    size_t sz = strlen(s);
    char *ptr = s;
    while(*ptr && (unsigned char)*ptr <= ' ') {
        ptr++;
        sz--;
    }
    if(ptr != s) {
        memmove(s, ptr, sz + 1);
    }
    if(sz) {
        ptr = s + sz - 1;
        while(sz && (unsigned char)*ptr <= ' ') {
            *ptr = 0;
            ptr--;
            sz--;
        }
    }
    return sz;
}
