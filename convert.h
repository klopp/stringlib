/*
 * convert.h
 *
 *  Created on: 6 июня 2016 г.
 *      Author: klopp
 */

#ifndef CONVERT_H_
#define CONVERT_H_

unsigned long asc2num( const char * s, unsigned base, int ignore_errors );
unsigned long _asc2num(const char * s, unsigned base, size_t size);

#endif /* CONVERT_H_ */
