/*
 * join.c, part of "stringlib" project.
 *
 *  Created on: 24.05.2015, 19:55
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char *join(char **splitted, const char *separator) {
    char *dest = 0;
    size_t idx = 0;
    size_t size = 0;
    size_t ssize = strlen(separator);
    while(splitted[idx]) {
        size += strlen(splitted[idx]) + ssize;
        idx++;
    }
    dest = Malloc(size + 1);
    if(!dest) {
        return NULL;
    }
    *dest = 0;
    idx = 0;
    while(splitted[idx]) {
        strcat(dest, splitted[idx]);
        idx++;
        if(splitted[idx]) {
            strcat(dest, separator);
        }
    }
    return dest;
}

