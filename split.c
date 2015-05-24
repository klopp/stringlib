/*
 * split.c, part of "stringlib" project.
 *
 *  Created on: 24.05.2015, 19:44
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"

size_t size_splitted( char ** splitted )
{
    size_t idx = 0;
    while( splitted[idx] )
        idx++;
    return idx;
}

char ** split( const char * s, const char * separators )
{
    char * token;
    size_t size = 0;
    char ** dest = NULL;
    char * src = strdup( s );
    if( !src ) return NULL;

    token = strtok( src, separators );
    while( token )
    {
        size++;
        token = strtok( NULL, separators );
    }

    dest = malloc( sizeof(char *) * (size + 1) );
    if( !dest )
    {
        free( src );
        return NULL;
    }

    strcpy( src, s );
    token = strtok( src, separators );
    size = 0;
    while( token )
    {
        dest[size] = strdup( token );
        if( !dest[size] )
        {
            free( src );
            while( --size )
            {
                free( dest[size] );
            }
            free( dest );
            return NULL;
        }
        size++;
        token = strtok( NULL, separators );
    }

    dest[size] = NULL;
    free( src );
    return dest;
}

void free_splitted( char ** splitted )
{
    if( splitted )
    {
        size_t idx = 0;
        while( splitted[idx] )
        {
            free( splitted[idx] );
            idx++;
        }
        free( splitted );
    }
}

