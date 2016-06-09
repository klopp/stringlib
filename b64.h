/*
 * b64.h, part of "stringlib" project.
 *
 *  Created on: 19.05.2015, 18:37
 *      Author: Vsevolod Lutovinov <klopp@yandex.ru>
 */

#ifndef B64_H_
#define B64_H_

#include "stringlib.h"

string base64_encode(const char *buf, size_t sz);
string base64_sencode(const char *s);
string base64_fencode(FILE *file);

#endif /* B64_H_ */
