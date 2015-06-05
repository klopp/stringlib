/*
 * strprbrk.c, part of "stringlib" project.
 *
 *  Created on: 05.06.2015, 17:27
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char * strprbrk( const char * s, const char * accept )
{
    const char * end = s + strlen( s );
    while( end >= s )
    {
        const char *a = accept;
        while( *a )
            if( *a++ == *end ) return (char *)end;
        end--;
    }
    return NULL;
}

