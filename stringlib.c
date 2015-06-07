/*
 * stringlib.c, part of "stringlib" project.
 *
 *  Created on: 19 мая 2015 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "stringlib.h"
#include <stdarg.h>

string sclr( string s )
{
    if( s && s->str )
    {
        memset( s->str, 0, s->bsz );
        s->len = 0;
    }
    return s;
}

string snewn( size_t n )
{
    string s = Malloc( sizeof(struct _string) );
    if( !s ) return NULL;
    s->str = Calloc( sizeof(char), n + 1 );
    if( !s->str )
    {
        Free( s );
        return NULL;
    }
    s->bsz = n;
    s->len = 0;
    return s;
}

void sdel( string s )
{
    if( s )
    {
        Free( s->str );
        Free( s );
    }
}

size_t schomp( string s )
{
    size_t sz = 0;
    if( s )
    {
        sz = chomp( s->str );
    }
    s->len = sz;
    return sz;
}

#if defined(DEBUG)

string snew( void )
{
    return snewn( STR_DEFAULT_LEN );
}

size_t slen( const string s )
{
    return s ? s->len : 0;
}

const char * sstr( const string s )
{
    return s ? s->str : NULL;
}

char sat( const string s, size_t at )
{
    return (!s || !s->str) ? 0 : (at > s->len ? 0 : s->str[at]);
}
int scmp( const string a, const string b )
{
    return scmpc( a, b ? b->str : NULL );
}

int scasecmp( const string a, const string b )
{
    return scasempc( a, b ? b->str : NULL );
}

#endif

string scrop( string s, size_t n )
{
    if( !s ) return NULL;
    if( n < s->len )
    {
        s->len = n;
        s->str[s->len] = 0;
    }
    return s;
}

string strim( string s, size_t n )
{
    if( !s ) return NULL;
    if( s->len > n ) s->len -= n;
    else s->len = 0;
    s->str[s->len] = 0;
    return s;
}

string sltrim( string s, size_t n )
{
    if( !s ) return NULL;
    if( s->len > n )
    {
        s->len -= n;
        memmove( s->str, s->str + n, s->len );
    }
    else s->len = 0;
    s->str[s->len] = 0;
    return s;
}

int scmpc( string a, const char * b )
{
    if( (!a || !a->str) && (!b) ) return 0;
    if( (a && a->str) && (!b) ) return 1;
    if( (!a || !a->str) && (b) ) return -1;
    return strcmp( a->str, b );
}

int scasempc( string a, const char * b )
{
    if( (!a || !a->str) && (!b) ) return 0;
    if( (a && a->str) && (!b) ) return 1;
    if( (!a || !a->str) && (b) ) return -1;
    return strcasecmp( a->str, b );
}

static string _sexpand( string s, size_t sz )
{
    if( s )
    {
        char * buf;
        size_t newsz = sz ? sz : s->bsz;
        newsz *= STR_K_EXPAND;
        buf = Calloc( newsz + 1, 1 );
        if( !buf ) return NULL;
        memcpy( buf, s->str, s->len );
        Free( s->str );
        s->str = buf;
        s->bsz = newsz;
    }
    return s;
}

static string _scatc( string dest, const char * src, size_t sz )
{
    if( dest->len + sz >= dest->bsz )
    {
        if( !_sexpand( dest, dest->bsz + sz ) )
        {
            return NULL;
        }
    }
    memcpy( dest->str + dest->len, src, sz );
    dest->len += sz;
    dest->str[dest->len] = 0;
    return dest;
}

string scatch( string dest, char c )
{
    if( dest->len + 1 >= dest->bsz )
    {
        if( !_sexpand( dest, dest->bsz + 1 ) )
        {
            return NULL;
        }
    }
    dest->str[dest->len] = c;
    dest->len++;
    dest->str[dest->len] = 0;
    return dest;
}

static string _scpyc( string dest, const char * src, size_t sz )
{
    if( sz >= dest->bsz )
    {
        if( !_sexpand( dest, sz ) )
        {
            return NULL;
        }
    }
    memcpy( dest->str, src, sz );
    dest->len = sz;
    dest->str[sz] = 0;
    return dest;
}

string scpyc( string dest, const char * src )
{
    if( !src ) return dest;
    return _scpyc( dest, src, strlen( src ) );
}

string sncpyc( string dest, const char * src, size_t n )
{
    if( !src ) return dest;
    return _scpyc( dest, src, n );
}

string scpy( string dest, const string src )
{
    if( !src ) return dest;
    return _scpyc( dest, src->str, src->len );
}

string sncpy( string dest, const string src, size_t n )
{
    if( !src ) return dest;
    return sncpyc( dest, src->str, n );
}

string scatc( string dest, const char * src )
{
    if( !src || !*src ) return dest;
    return _scatc( dest, src, strlen( src ) );
}
string scat( string dest, const string src )
{
    if( !src ) return dest;
    return _scatc( dest, src->str, src->len );
}

string sprint( string src, const char * fmt, ... )
{
    if( src )
    {
        size_t size;
        char * str;
        va_list ap;

        va_start( ap, fmt );
        str = _ssprintf( &size, fmt, ap );
        va_end( ap );

        if( !str ) return NULL;
        Free( src->str );
        src->str = str;
        src->bsz = size;
/*
        va_list ap;
        int len = 0;

        while( 1 )
        {
            va_start( ap, fmt );
            len = vsnprintf( src->str, src->bsz, fmt, ap );
            va_end( ap );
            if( len > -1 && (size_t)len < src->bsz )
            {
                break;
            }
            if( !sexpand( src, 0 ) ) return NULL;
        }
        src->len = len;
*/
    }
    return src;
}

size_t sfgets( string src, FILE * fin )
{
    if( src )
    {
        size_t last = 0;

        sclr( src );

        while( fgets( src->str + last, src->bsz - last, fin ) )
        {
            size_t len = strlen( src->str );
            src->len = len;
            if( src->str[len - 1] != '\n' && !feof( fin ) )
            {
                if( !_sexpand( src, 0 ) ) return src->len;
                last = len;
                continue;
            }
            break;
        }
        return src->len;
    }
    return 0;
}

string sfromnchar( const char * src, size_t sz )
{
    string s = snew();
    return _scpyc( s, src, sz );
}

string sfromchar( const char * src )
{
    return sfromnchar( src, strlen( src ) );
}

string sfromstr( const string src )
{
    return sfromnchar( src->str, src->len );
}

string sfromnstr( const string src, size_t sz )
{
    return sfromnchar( src->str, sz > src->len ? src->len : sz );
}

string xscat( string dest, ... )
{
    va_list ap;
    string src;
    va_start( ap, dest );
    src = va_arg( ap, string );
    while( src )
    {
        if( !_scatc( dest, src->str, src->len ) )
        {
            va_end( ap );
            return NULL;
        }
        src = va_arg( ap, string );
    }
    va_end( ap );
    return dest;
}

string xscatc( string dest, ... )
{
    va_list ap;
    char * src;
    va_start( ap, dest );
    src = va_arg( ap, char * );
    while( src )
    {
        if( !_scatc( dest, src, strlen( src ) ) )
        {
            va_end( ap );
            return NULL;
        }
        src = va_arg( ap, char * );
    }
    va_end( ap );
    return dest;
}
