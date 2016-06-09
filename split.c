/*
 * split.c, part of "stringlib" project.
 *
 *  Created on: 24.05.2015, 19:44
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

size_t size_splitted(char **splitted) {
    size_t idx = 0;
    while(splitted[idx]) {
        idx++;
    }
    return idx;
}

char **split(const char *s, const char *separators) {
    char *token;
    size_t size = 0;
    char **dest = NULL;
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
    dest = Malloc(sizeof(char *) * (size + 1));
    if(!dest) {
        Free(src);
        return NULL;
    }
    memcpy(src, s, ssize);
    token = strtok(src, separators);
    size = 0;
    while(token) {
        dest[size] = Strdup(token);
        if(!dest[size]) {
            Free(src);
            while(--size) {
                Free(dest[size]);
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

void free_splitted(char **splitted) {
    if(splitted) {
        size_t idx = 0;
        while(splitted[idx]) {
            Free(splitted[idx]);
            idx++;
        }
        Free(splitted);
    }
}

