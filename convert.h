/*
 * convert.h
 *
 *  Created on: 6 июня 2016 г.
 *      Author: klopp
 */

#ifndef CONVERT_H_
#define CONVERT_H_

#include <stdlib.h>

unsigned long asc2ulong(const char *s, unsigned base, int ignore_errors);
long asc2long(const char *s, unsigned base, int ignore_errors);
unsigned long long asc2ullong(const char *s, unsigned base, int ignore_errors);
long long asc2llong(const char *s, unsigned base, int ignore_errors);

#define _asc2ulong(s, base)     strtoul( (s), NULL, (base) )
#define _asc2long(s, base)      strtol( (s), NULL, (base) )
#define _asc2ullong(s, base)    strtoull( (s), NULL, (base) )
#define _asc2llong(s, base)     strtoll( (s), NULL, (base) )

#endif /* CONVERT_H_ */
