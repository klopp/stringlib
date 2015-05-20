/*
 * qp.c, part of "stringlib" project.
 *
 *  Created on: 19.05.2015, 19:58
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "qp.h"

#define QP_MAX_LINE     76

static int _qp_encodable( int c )
{
    if( ((c >= 9) && (c <= 60)) || ((c >= 62) && (c <= 126)) )
    {
        return 0;
    }
    return 1;
}

static size_t _qp_stdout( int c, size_t line_len, string out, int wrap )
{
    char s[2];
    if( (line_len == (QP_MAX_LINE - 1)) && wrap )
    {
        scatc( out, "=\r\n" );
        line_len = 0;
    }

    s[0] = c;
    s[1] = 0;
    scatc( out, s );
    line_len++;
    return line_len;
}

static size_t _qp_encout( int c, size_t line_len, string out, int wrap )
{
    char s[8];
    if( ((line_len + 3) >= QP_MAX_LINE) && wrap )
    {
        scatc( out, "=\r\n" );
        line_len = 0;
    }

    sprintf( s, "=%02X", c & 0xFF );
    scatc( out, s );
    line_len += 3;
    return line_len;
}

string qp_encode( const char * str, int wrap )
{

    size_t line_len = 0;
    string out = snew();
    if( !out ) return NULL;

    for( ; *str; str++ )
    {
        if( line_len == (QP_MAX_LINE - 1) && wrap )
        {
            scatc( out, "=\r\n" );
            line_len = 0;
        }

        switch( *str )
        {
            case ' ':
            case '\t':
                if( (str[1] == '\r') || (str[1] == '\n') )
                {
                    line_len = _qp_encout( *str, line_len, out, wrap );
                }
                else
                {
                    line_len = _qp_stdout( *str, line_len, out, wrap );
                }
                break;

            case '\r':
                break;

            case '\n':
                scatc( out, "\r\n" );
                line_len = 0;
                break;

            default:
                if( _qp_encodable( *str ) )
                {
                    line_len = _qp_encout( *str, line_len, out, wrap );
                }
                else
                {
                    line_len = _qp_stdout( *str, line_len, out, wrap );
                }
                break;
        }
    }
    return out;
}

