/*
 * ssplit.c, part of "stringlib" project.
 *
 *  Created on: 24.05.2015, 20:15
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

#if defined(DEBUG)

string *ssplit(const string s, const char *separators) {
    return s ? ssplitc(sstr(s), separators) : NULL;
}

#endif

size_t ssize_splitted(string *splitted) {
    size_t idx = 0;
    while(splitted[idx]) {
        idx++;
    }
    return idx;
}

string *ssplitc(const char *s, const char *separators) {
    char *token;
    size_t size = 0;
    string *dest = NULL;
    size_t ssize = strlen(s) + 1;
    char *src = Malloc(ssize);
    if(!src) {
        return NULL;
    }
    memcpy(src, s, ssize);
    token = strtok(src, separators);
    while(token) {
        size++;
        token = strtok(NULL, separators);
    }
    dest = Malloc(sizeof(string) * (size + 1));
    if(!dest) {
        Free(src);
        return NULL;
    }
    memcpy(src, s, ssize);
    token = strtok(src, separators);
    size = 0;
    while(token) {
        dest[size] = sfromchar(token);
        if(!dest[size]) {
            Free(src);
            while(--size) {
                sdel(dest[size]);
            }
            Free(dest);
            return NULL;
        }
        size++;
        token = strtok(NULL, separators);
    }
    dest[size] = NULL;
    Free(src);
    return dest;
}

void sfree_splitted(string *splitted) {
    if(splitted) {
        size_t idx = 0;
        while(splitted[idx]) {
            sdel(splitted[idx]);
            idx++;
        }
        Free(splitted);
    }
}

