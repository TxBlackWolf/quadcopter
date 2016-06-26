////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       05.09.2015
/// @brief      Based on ee_printf: https://github.com/jpbonn/coremark_lm32
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef STRING_MANIPULATION_H
#define STRING_MANIPULATION_H

#include <stdarg.h>
#include <stdlib.h>

#define HAS_FLOAT       0

// Format flags.
#define ZEROPAD         (1 << 0)    // Pad with zero.
#define SIGN            (1 << 1)    // Unsigned/signed long.
#define PLUS            (1 << 2)    // Show plus.
#define SPACE           (1 << 3)    // Spacer.
#define LEFT            (1 << 4 )   // Left justified.
#define HEX_PREP        (1 << 5 )   // 0x prefix.
#define UPPERCASE       (1 << 6 )   // Uppercase for hex letters 'ABCDEF'.

#define is_digit(c)     ((c) >= '0' && (c) <= '9')

int vsprintf(char *buffer, const char *format, va_list args);
int skip_atoi(const char **string);
size_t strnlen(const char *string, size_t count);
char *number_to_string(char *string, long number, int base, int size, int precision, int type);
char *eaddr(char *string, unsigned char *address, int size, int type);
char *iaddr(char *string, unsigned char *address, int size, int type);

#if HAS_FLOAT
void buffcpy(char *destination, char *source, int count);
void parse_float(double value, char *buffer, char format, int precision);
void decimal_point(char *buffer);
void cropzeros(char *buffer);
char *float_to_string(char *string, double number, int size, int precision, char format, int flags);
char *ecvtbuf(double arg, int ndigits, int *decpt, int *sign, char *buf);   // Not copied into project, because depends on math.h.
char *fcvtbuf(double arg, int ndigits, int *decpt, int *sign, char *buf);   // Not copied into project, because depends on math.h.
#endif

#endif
