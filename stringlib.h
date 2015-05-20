/*
 * stringlib.h, part of "stringlib" project.
 *
 *  Created on: 19 мая 2015 г.
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#ifndef STRINGLIB_H_
#define STRINGLIB_H_

#include "../klib/config.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

size_t chomp( char * s );
char * rnd_string( char * string, size_t size );

#define STR_DEFAULT_LEN 128

typedef struct _string
{
    size_t bsz;
    size_t len;
    char * str;
}*string;

string snewn( size_t sz );
string sfromstr( const string src );
string sfromnstr( const string src, size_t sz );
string sfromchar( const char * src );
string sfromnchar( const char * src, size_t sz );
string sclr( string s );
void sdel( string src );

#if defined(DEBUG)
string snew( void );
size_t slen( const string s );
const char * sstr( const string s );
char sat( const string src, size_t at );
string sset( string src, size_t at, char c );
int scmp( const string a, const string b );
int scasemp( const string a, const string b );
#else
# define snew() snewn((STR_DEFAULT_LEN))
# define slen( s ) (s)->len
# define sstr( s ) (s)->str
# define sat( s, at ) ((at) > (s)->len ? 0 : (s)->str[(at)])
# define sset( s, at, c ) ( (at) > (s)->len ? (void)0 : (s)->str[(at)] = c )
# define scmp( a, b ) scmpc( (a), (b)->str )
# define scasemp( a, b ) scasempc( (a), (b)->str )
#endif

size_t schomp( string s );
int scmpc( string a, const char * b );
int scasempc( string a, const char * b );
string scpy( string dest, const string src );
string sncpy( string dest, const string src, size_t n );
string scpyc( string dest, const char * src );
string scat( string dest, const string src );
string scatc( string dest, const char * src );
string scatch( string dest, char c );
string scrop(string s, size_t n);
string strim(string s, size_t n);
string sltrim(string s, size_t n);
/*
 string slower( string src );
 string supper( string src );
 */
string sprint( string src, const char * fmt, ... );
size_t sfgets( string src, FILE * fin );

string sresize( string s, size_t sz );

#ifdef __cplusplus
}
#endif

#endif /* STRINGLIB_H_ */
