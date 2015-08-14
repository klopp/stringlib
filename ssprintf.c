/*
 * ssprintf.c, part of "stringlib" project.
 *
 *  Created on: 06.06.2015, 22:33
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char * _ssprintf( size_t * size, const char * fmt, va_list ap )
{
    //va_list ap;
    //int len = 0;
    size_t bsz = STR_DEFAULT_LEN;
    //size_t newsz;
    char * str = Malloc( STR_DEFAULT_LEN );
    char * newstr;
    if( !str ) return NULL;

    while( 1 )
    {
        size_t newsz;
        int len = vsnprintf( str, bsz, fmt, ap );
        if( len > -1 && (size_t)len < bsz )
        {
            break;
        }
        newsz = bsz * 2;
        newstr = Malloc( newsz );
        if( !newstr )
        {
            Free( str );
            return NULL;
        }
        Free( str );
        str = newstr;
        bsz = newsz;
    }
    if( size ) *size = bsz;
    return str;
}

char * ssprintf( size_t * size, const char * fmt, ... )
{
    va_list ap;
    char * rc;
    va_start( ap, fmt );
    rc = _ssprintf( size, fmt, ap );
    va_end( ap );
    return rc;
}
