/*
 * rndstring.c, part of "stringlib" project.
 *
 *  Created on: 19 мая 2015 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char * rnd_string( char * string, size_t size )
{
    static const char _letters[] =
            "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz0123456789";
    size_t i;

    if( !string )
    {
        string = Malloc( size + 1 );
        if( !string ) return NULL;
    }

    for( i = 0; i < size - 1; i++ )
    {
        string[i] = _letters[rand() % (sizeof(_letters)-1)];
    }
    string[i] = 0;
    return string;
}
