/*
 *  Created on: 17 авг. 2016 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char *strdup(const char *src)
{
    size_t size = strlen(src) + 1;
    char *dest = Malloc(size);
    if (dest) {
        memcpy(dest, src, size);
    }
    return dest;
}

/*
 *  That's All, Folks!
 */

