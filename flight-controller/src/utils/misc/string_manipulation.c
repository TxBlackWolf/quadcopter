//---------------------------------------------------------------------------------------------------------------
//
// Filename   : string_manipulation.c
// Author     : Kuba Sejdak
// Created on : 05.09.2015
//
// This file is a part of SkyViper project.
// Based on ee_printf: https://github.com/jpbonn/coremark_lm32
//
// %LICENSE%
//
//---------------------------------------------------------------------------------------------------------------

#include "string_manipulation.h"

static char *lower_digits = "0123456789abcdefghijklmnopqrstuvwxyz";
static char *upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int vsprintf(char *buffer, const char *format, va_list args)
{
    char *ptr;
    for(ptr = buffer; *format; ++format)
    {
        if(*format != '%')
        {
            *ptr++ = *format;
            continue;
        }

        int flags = 0;

process_flags:
        // Skip first '%' character and already processed specifier flags.
        ++format;

        switch(*format)
        {
        case '-':   flags |= LEFT;      goto process_flags;
        case '+':   flags |= PLUS;      goto process_flags;
        case ' ':   flags |= SPACE;     goto process_flags;
        case '#':   flags |= HEX_PREP;  goto process_flags;
        case '0':   flags |= ZEROPAD;   goto process_flags;
        }

        // Get field width.
        int field_width = -1;

        if(is_digit(*format))
            field_width = skip_atoi(&format);
        else if(*format == '*')
        {
            ++format;

            field_width = va_arg(args, int);
            if(field_width < 0)
            {
                field_width = -field_width;
                flags |= LEFT;
            }
        }

        // Get precision.
        int precision = -1;

        if (*format == '.')
        {
            ++format;

            if(is_digit(*format))
                precision = skip_atoi(&format);
            else if (*format == '*')
            {
                ++format;
                precision = va_arg(args, int);
            }

            if(precision < 0)
                precision = 0;
        }

        // Get conversion qualifier.
        int qualifier = -1;

        if (*format == 'l' || *format == 'L')
        {
            qualifier = *format;
            ++format;
        }

        // Default base.
        int base = 10;

        switch (*format)
        {
        case 'c':
            if(!(flags & LEFT))
            {
                while(--field_width > 0)
                    *ptr++ = ' ';
            }

            *ptr++ = (unsigned char) va_arg(args, int);

            while(--field_width > 0)
                *ptr++ = ' ';

            continue;
        //----------------------------------------------------------
        case 's':
        {
            char *string = va_arg(args, char *);
            if(!string)
                string = "<NULL>";

            int length = strnlen(string, precision);
            if(!(flags & LEFT))
            {
                while(length < field_width--)
                    *ptr++ = ' ';
            }

            int i;
            for(i = 0; i < length; ++i)
                *ptr++ = *string++;

            while (length < field_width--)
                *ptr++ = ' ';

            continue;
        }
        //----------------------------------------------------------
        case 'p':
            if(field_width == -1)
            {
                field_width = 2 * sizeof(void *);
                flags |= ZEROPAD;
            }

            ptr = number_to_string(ptr, (unsigned long) va_arg(args, void *), 16, field_width, precision, flags);

            continue;
        //----------------------------------------------------------
        case 'A':
            flags |= UPPERCASE;

        case 'a':
            if (qualifier == 'l')
                ptr = eaddr(ptr, va_arg(args, unsigned char *), field_width, flags);
            else
                ptr = iaddr(ptr, va_arg(args, unsigned char *), field_width, flags);

            continue;
        //----------------------------------------------------------
        case 'o':
            base = 8;
            break;
        //----------------------------------------------------------
        case 'X':
            flags |= UPPERCASE;

        case 'x':
            base = 16;
            break;
        //----------------------------------------------------------
        case 'd':
        case 'i':
            flags |= SIGN;

        case 'u':
            break;
        //----------------------------------------------------------
#if HAS_FLOAT
        case 'f':
            ptr = float_to_string(ptr, va_arg(args, double), field_width, precision, *format, flags | SIGN);
            continue;
#endif
        //----------------------------------------------------------
        default:
            if(*format != '%')
                *ptr++ = '%';

            if(*format)
                *ptr++ = *format;
            else
                --format;

            continue;
        }

        unsigned long num;
        if(qualifier == 'l')
            num = va_arg(args, unsigned long);
        else if (flags & SIGN)
            num = va_arg(args, int);
        else
            num = va_arg(args, unsigned int);

        ptr = number_to_string(ptr, num, base, field_width, precision, flags);
    }

    *ptr = '\0';
    return (ptr - buffer);
}

int skip_atoi(const char **string)
{
    int i = 0;
    while(is_digit(**string))
        i = i * 10 + *((*string)++) - '0';

    return i;
}

size_t strnlen(const char *string, size_t count)
{
    const char *ptr;
    for(ptr = string; *ptr != '\0' && count--; ++ptr);

    return (ptr - string);
}

char *number_to_string(char *string, long number, int base, int size, int precision, int type)
{
    char *digits = lower_digits;
    if(type & UPPERCASE)
        digits = upper_digits;

    if(type & LEFT)
        type &= ~ZEROPAD;

    if(base < 2 || base > 36)
        return 0;

    // Prepare sign character.
    char sign = 0;
    if(type & SIGN)
    {
        if(number < 0)
        {
            sign = '-';
            number = -number;
            --size;
        }
        else if(type & PLUS)
        {
            sign = '+';
            --size;
        }
        else if(type & SPACE)
        {
            sign = ' ';
            --size;
        }
    }

    if(type & HEX_PREP)
    {
        if(base == 16)
            size -= 2;
        else if(base == 8)
            --size;
    }

    int i = 0;
    char tmp[66];
    if(number == 0)
        tmp[i++] = '0';
    else
    {
        while(number != 0)
        {
            tmp[i++] = digits[((unsigned long) number) % (unsigned) base];
            number = ((unsigned long) number) / (unsigned) base;
        }
    }

    if(i > precision)
        precision = i;

    size -= precision;
    if(!(type & (ZEROPAD | LEFT)))
    {
        while(size-- > 0)
            *string++ = ' ';
    }

    if(sign)
        *string++ = sign;

    if(type & HEX_PREP)
    {
        if(base == 8)
            *string++ = '0';
        else if (base == 16)
        {
            *string++ = '0';
            *string++ = lower_digits[33];
        }
    }

    char c = (type & ZEROPAD) ? '0' : ' ';

    if(!(type & LEFT))
    {
        while(size-- > 0)
            *string++ = c;
    }

    while(i < precision--)
        *string++ = '0';

    while(i-- > 0)
        *string++ = tmp[i];

    while(size-- > 0)
        *string++ = ' ';

    return string;
}

char *eaddr(char *string, unsigned char *address, int size, int type)
{
    char *digits = lower_digits;
    if(type & UPPERCASE)
        digits = upper_digits;

    int length = 0;
    char tmp[24];
    for(int i = 0; i < 6; i++)
    {
        if(i != 0)
            tmp[length++] = ':';

        tmp[length++] = digits[address[i] >> 4];
        tmp[length++] = digits[address[i] & 0x0F];
    }

    if(!(type & LEFT))
    {
        while(length < size--)
            *string++ = ' ';
    }

    for(int i = 0; i < length; ++i)
        *string++ = tmp[i];

    while(length < size--)
        *string++ = ' ';

    return string;
}

char *iaddr(char *string, unsigned char *address, int size, int type)
{
    int length = 0;
    char tmp[24];
    for(int i = 0; i < 4; i++)
    {
        if (i != 0)
            tmp[length++] = '.';

        int n = address[i];

        if (n == 0)
            tmp[length++] = lower_digits[0];
        else
        {
            if(n >= 100)
            {
                tmp[length++] = lower_digits[n / 100];
                n = n % 100;
                tmp[length++] = lower_digits[n / 10];
                n = n % 10;
            }
            else if(n >= 10)
            {
                tmp[length++] = lower_digits[n / 10];
                n = n % 10;
            }

            tmp[length++] = lower_digits[n];
        }
    }

    if(!(type & LEFT))
    {
        while(length < size--)
            *string++ = ' ';
    }

    for(int i = 0; i < length; ++i)
        *string++ = tmp[i];

    while(length < size--)
        *string++ = ' ';

    return string;
}

#if HAS_FLOAT
void buffcpy(char *destination, char *source, int count)
{
    char *end = source + count;

    while(source != end)
        *destination++ = *source++;
}

void parse_float(double value, char *buffer, char format, int precision)
{
    int decpt;
    int sign;
    char *float_digits = NULL;
    char cvtbuf[80];

    int capexp = 0;
    if(format == 'G' || format == 'E')
    {
        capexp = 1;
        format += 'a' - 'A';
    }

    if(format == 'g')
    {
        float_digits = ecvtbuf(value, precision, &decpt, &sign, cvtbuf);
        int magnitude = decpt - 1;
        if(magnitude < -4  ||  magnitude > precision - 1)
        {
            format = 'e';
            precision -= 1;
        }
        else
        {
            format = 'f';
            precision -= decpt;
        }
    }

    if(format == 'e')
    {
        float_digits = ecvtbuf(value, precision + 1, &decpt, &sign, cvtbuf);

        if(sign)
            *buffer++ = '-';

        *buffer++ = *float_digits;
        if(precision > 0)
            *buffer++ = '.';

        buffcpy(buffer, float_digits + 1, precision);
        buffer += precision;
        *buffer++ = capexp ? 'E' : 'e';

        int exponential;
        if(decpt == 0)
            exponential = (value == 0.0) ? 0 : -1;
        else
            exponential = decpt - 1;

        if(exponential < 0)
        {
            *buffer++ = '-';
            exponential = -exponential;
        }
        else
            *buffer++ = '+';

        buffer[2] = (exponential % 10) + '0';
        exponential = exponential / 10;
        buffer[1] = (exponential % 10) + '0';
        exponential = exponential / 10;
        buffer[0] = (exponential % 10) + '0';
        buffer += 3;
    }
    else if(format == 'f')
    {
        float_digits = fcvtbuf(value, precision, &decpt, &sign, cvtbuf);
        if(sign)
            *buffer++ = '-';

        if(*float_digits)
        {
            if (decpt <= 0)
            {
                *buffer++ = '0';
                *buffer++ = '.';
                for(int pos = 0; pos < -decpt; pos++)
                    *buffer++ = '0';

                while(*float_digits)
                    *buffer++ = *float_digits++;
            }
            else
            {
                int pos = 0;
                while(*float_digits)
                {
                    if(pos++ == decpt)
                        *buffer++ = '.';

                    *buffer++ = *float_digits++;
                }
            }
        }
        else
        {
            *buffer++ = '0';
            if(precision > 0)
            {
                *buffer++ = '.';
                for(int pos = 0; pos < precision; pos++)
                    *buffer++ = '0';
            }
        }
    }

    *buffer = '\0';
}

void decimal_point(char *buffer)
{
    while(*buffer)
    {
        if(*buffer == '.')
            return;

        if(*buffer == 'e' || *buffer == 'E')
            break;

        buffer++;
    }

    if(*buffer)
    {
        int n = strnlen(buffer, 256);
        while(n > 0)
        {
            buffer[n + 1] = buffer[n];
            --n;
        }

        *buffer = '.';
    }
    else
    {
        *buffer++ = '.';
        *buffer = '\0';
    }
}

void cropzeros(char *buffer)
{
    char *stop;

    while (*buffer && *buffer != '.')
        ++buffer;

    if(*buffer++)
    {
        while(*buffer && *buffer != 'e' && *buffer != 'E')
            ++buffer;

        stop = buffer--;

        while(*buffer == '0')
            --buffer;

        if(*buffer == '.')
            --buffer;

        while (buffer!=stop)
            *++buffer = 0;
    }
}

char *float_to_string(char *string, double number, int size, int precision, char format, int flags)
{
    // Left align means no zero padding.
    if(flags & LEFT)
        flags &= ~ZEROPAD;

    // Determine padding and sign char.
    char c = (flags & ZEROPAD) ? '0' : ' ';

    char sign = 0;
    if(flags & SIGN)
    {
        if(number < 0.0)
        {
            sign = '-';
            number = -number;
            --size;
        }
        else if(flags & PLUS)
        {
            sign = '+';
            --size;
        }
        else if(flags & SPACE)
        {
            sign = ' ';
            size--;
        }
    }

    // Compute the precision value (default is 6).
    if (precision < 0)
        precision = 6;

    // Convert floating point number to text.
    char tmp[80];
    parse_float(number, tmp, format, precision);

    if((flags & HEX_PREP) && precision == 0)
        decimal_point(tmp);

    if(format == 'g' && !(flags & HEX_PREP))
        cropzeros(tmp);

    int n = strnlen(tmp,256);

    // Output number with alignment and padding.
    size -= n;

    if(!(flags & (ZEROPAD | LEFT)))
    {
        while (size-- > 0)
            *string++ = ' ';
    }

    if(sign)
        *string++ = sign;

    if(!(flags & LEFT))
    {
        while(size-- > 0)
            *string++ = c;
    }

    for (int i = 0; i < n; ++i)
        *string++ = tmp[i];

    while(size-- > 0)
        *string++ = ' ';

    return string;
}
#endif
