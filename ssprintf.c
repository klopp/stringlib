/*
 * ssprintf.c, part of "stringlib" project.
 *
 *  Created on: 06.06.2015, 22:33
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

char * _ssprintf( size_t * size, const char * fmt, va_list ap )
{
    char * str;
    va_list cp;
    va_copy( cp, ap );
    size_t bsz = vsnprintf( NULL, 0, fmt, ap );
    if( bsz == (size_t)-1 ) return NULL;
    str = Malloc( bsz + 1 );
    if( !str ) return NULL;
    vsprintf( str, fmt, cp );
    if( size ) *size = bsz + 1;
    return str;
}

char * ssprintf( size_t * size, const char * fmt, ... )
{
    va_list ap;
    char * str;
    va_start( ap, fmt );
    str = _ssprintf( size, fmt, ap );
    va_end( ap );
    return str;
}
