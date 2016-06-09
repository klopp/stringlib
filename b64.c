/*
 * b64.c, part of "stringlib" project.
 *
 *  Created on: 19.05.2015, 18:43
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#include "b64.h"

#define MAX_B64_LINE 72

static const char _b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz"
                           "0123456789+/";

static void _b64_encode_block(const unsigned char in[3], unsigned char out[5],
                              size_t len) {
    out[0] = _b64[in[0] >> 2];
    out[1] = _b64[((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)];
    out[2] =
        (unsigned char)(
            len > 1 ?
            _b64[((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6)] :
            '=');
    out[3] = (unsigned char)(len > 2 ? _b64[in[2] & 0x3f] : '=');
}

static string _b64_encode(size_t insize, int (*b64_getc)(void *data),
                          void *data/*, const char * prefix */) {
    unsigned char in[3], out[5] = { 0 };
    size_t i, blocksout = 0;
    int c;
    string ret;
    i = insize * 4 / 3 + 4;
    i += (i / MAX_B64_LINE) * 2;
    /*if( prefix ) i += strlen( prefix ) + 1;*/
    ret = snewn(i + 1);
    if(!ret) {
        return NULL;
    }
    /*if( prefix ) scpyc( ret, prefix );*/
    while((c = b64_getc(data)) != -1) {
        int len = 1;
        in[1] = in[2] = 0;
        in[0] = (unsigned char)c;
        for(i = 1; i < 3; i++) {
            c = b64_getc(data);
            if(c != -1) {
                in[i] = (unsigned char)c;
                len++;
            } else {
                in[i] = 0;
            }
        }
        if(len) {
            _b64_encode_block(in, out, len);
            scatc(ret, (char *)out);
            blocksout++;
        }
        if(blocksout >= (MAX_B64_LINE / 4)) {
            if(blocksout) {
                scatc(ret, "\r\n");
            }
            blocksout = 0;
        }
    }
    return ret;
}

static int _b64_from_string(void *data) {
    struct {
        const char *buf;
        size_t sz;
        size_t pos;
    }* ptr = data;
    if(ptr->pos >= ptr->sz) {
        return -1;
    }
    return ptr->buf[ptr->pos++];
}

string base64_sencode(const char *buf) {
    return base64_encode(buf, strlen(buf));
}

string base64_encode(const char *buf, size_t insize) {
    struct {
        const char *buf;
        size_t sz;
        size_t pos;
    } data;
    data.sz = insize;
    data.pos = 0;
    data.buf = buf;
    return _b64_encode(insize, _b64_from_string, &data);
}

static int _b64_from_file(void *data) {
    int c = fgetc((FILE *)data);
    return c == EOF ? -1 : c;
}

string base64_fencode(FILE *file) {
    size_t insize;
    fseek(file, 0, SEEK_END);
    insize = ftell(file);
    fseek(file, 0, SEEK_SET);
    return _b64_encode(insize, _b64_from_file, file);
}
