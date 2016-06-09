/*
 * sjoin.c, part of "stringlib" project.
 *
 *  Created on: 24.05.2015, 20:16
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

string sjoin(string *splitted, const char *separator) {
    size_t idx = 0;
    string dest = snew();
    if(!dest) {
        return NULL;
    }
    while(splitted[idx]) {
        if(!scat(dest, splitted[idx])) {
            sdel(dest);
            return NULL;
        }
        idx++;
        if(splitted[idx] && !scatc(dest, separator)) {
            sdel(dest);
            return NULL;
        }
    }
    return dest;
}

string sjoinc(char **splitted, const char *separator) {
    size_t idx = 0;
    string dest = snew();
    if(!dest) {
        return NULL;
    }
    while(splitted[idx]) {
        if(!scatc(dest, splitted[idx])) {
            sdel(dest);
            return NULL;
        }
        idx++;
        if(splitted[idx] && !scatc(dest, separator)) {
            sdel(dest);
            return NULL;
        }
    }
    return dest;
}



