#include <stdio.h>

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define FLAGS_ZEROPAD (1U << 0U)
#define FLAGS_LEFT (1U << 1U)
#define FLAGS_PLUS (1U << 2U)
#define FLAGS_SPACE (1U << 3U)
#define FLAGS_HASH (1U << 4U)
#define FLAGS_UPPERCASE (1U << 5U)
#define FLAGS_CHAR (1U << 6U)
#define FLAGS_SHORT (1U << 7U)
#define FLAGS_LONG (1U << 8U)
#define FLAGS_LONG_LONG (1U << 9U)
#define FLAGS_PRECISION (1U << 10U)
#define FLAGS_ADAPT_EXP (1U << 11U)

#define PRINTF_NTOA_BUFFER_SIZE 32

size_t ntoa(FILE* stream, unsigned long long value, int negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned flags, size_t idx) {
    char buf[PRINTF_NTOA_BUFFER_SIZE];
    size_t len = 0;

    if (!value)
        flags &= ~FLAGS_HASH;

    if (!(flags & FLAGS_PRECISION) || value) {
        do {
            const char digit = (char)(value % base);
            buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
            value /= base;
        } while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
    }

    if (!(flags & FLAGS_LEFT)) {
        if (width && (flags & FLAGS_ZEROPAD) && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE))))
            width--;

        while ((len < prec) && (len < PRINTF_NTOA_BUFFER_SIZE))
            buf[len++] = '0';

        while ((flags & FLAGS_ZEROPAD) && (len < width) && (len < PRINTF_NTOA_BUFFER_SIZE))
            buf[len++] = '0';
    }

    if (flags & FLAGS_HASH) {
        if (!(flags & FLAGS_PRECISION) && len && ((len == prec) || (len == width))) {
            len--;
            if (len && (base == 16))
                len--;
        }

        if ((base == 16) && (len < PRINTF_NTOA_BUFFER_SIZE))
            buf[len++] = 'x';
        else if ((base == 2) && (len < PRINTF_NTOA_BUFFER_SIZE))
            buf[len++] = 'b';

        if (len < PRINTF_NTOA_BUFFER_SIZE)
            buf[len++] = '0';
    }

    if (len < PRINTF_NTOA_BUFFER_SIZE) {
        if (negative)
            buf[len++] = '-';
        else if (flags & FLAGS_PLUS)
            buf[len++] = '+';
        else if (flags & FLAGS_SPACE)
            buf[len++] = ' ';
    }

    const size_t start_idx = idx;

    if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD)) {
        for (size_t i = len; i < width; i++) {
            fputc(' ', stream);
            idx++;
        }
    }

    while (len) {
        fputc(buf[--len], stream);
        idx++;
    }

    if (flags & FLAGS_LEFT) {
        while (idx - start_idx < width) {
            fputc(' ', stream);
            idx++;
        }
    }

    return idx;
}

int vfprintf(FILE* stream, const char* format, va_list arg) {
    unsigned int flags, width, precision, n;
    size_t idx = 0;

    while (*format) {
        // Check for specifier
        if (*format != '%') {
            fputc(*format, stream);
            format++;
            continue;
        }

        format++;

        // Parse flags
        flags = 0;
        do {
            switch (*format) {
            case '0':
                flags |= FLAGS_ZEROPAD;
                format++;
                n = 1;
                break;

            case '-':
                flags |= FLAGS_LEFT;
                format++;
                n = 1;
                break;

            case '+':
                flags |= FLAGS_PLUS;
                format++;
                n = 1;
                break;

            case ' ':
                flags |= FLAGS_SPACE;
                format++;
                n = 1;
                break;

            case '#':
                flags |= FLAGS_HASH;
                format++;
                n = 1;
                break;

            default:
                n = 0;
                break;
            }
        } while (n);

        // Parse width
        width = 0;
        if (isdigit(*format)) {
            while (isdigit(*format)) {
                width *= 10;
                width += *format - '0';
                format++;
            }
        } else if (*format == '*') {
            const int w = va_arg(arg, int);
            if (w < 0) {
                flags |= FLAGS_LEFT;
                width = (unsigned int)-w;
            } else
                width = (unsigned int)w;

            format++;
        }

        // Parse precision
        precision = 0;
        if (*format == '.') {
            flags |= FLAGS_PRECISION;
            format++;
            if (isdigit(*format)) {
                while (isdigit(*format)) {
                    precision *= 10;
                    precision += *format - '0';
                    format++;
                }
            } else if (*format == '*') {
                const int prec = va_arg(arg, int);
                precision = prec > 0 ? (unsigned int)prec : 0;
                format++;
            }
        }

        // Parse length
        switch (*format) {
        case 'l':
            flags |= FLAGS_LONG;
            format++;
            if (*format == 'l') {
                flags |= FLAGS_LONG_LONG;
                format++;
            }
            break;

        case 'h':
            flags |= FLAGS_SHORT;
            format++;
            if (*format == 'h') {
                flags |= FLAGS_CHAR;
                format++;
            }
            break;
        case 't':
            flags |= FLAGS_LONG;
            format++;
            break;

        case 'j':
            flags |= FLAGS_LONG;
            format++;
            break;

        case 'z':
            flags |= FLAGS_LONG;
            format++;
            break;

        default:
            break;
        }

        // Parse specifier
        switch (*format) {
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'X':
        case 'o':
        case 'b': {
            unsigned int base;
            if (*format == 'x' || *format == 'X')
                base = 16;
            else if (*format == 'o')
                base = 8;
            else if (*format == 'b')
                base = 2;
            else {
                base = 10;
                flags &= ~FLAGS_HASH;
            }

            if (*format == 'X')
                flags |= FLAGS_UPPERCASE;

            if (*format != 'i' && *format != 'd')
                flags |= ~(FLAGS_PLUS | FLAGS_SPACE);

            if (flags & FLAGS_PRECISION)
                flags &= ~FLAGS_ZEROPAD;

            if (*format == 'i' || *format == 'd') {
                if (flags & FLAGS_LONG_LONG) {
                    const long long value = va_arg(arg, long long);
                    idx = ntoa(stream, (unsigned long long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                } else if (flags & FLAGS_LONG) {
                    const long value = va_arg(arg, long);
                    idx = ntoa(stream, (unsigned long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                } else {
                    const int value = (flags & FLAGS_CHAR) ? (char)va_arg(arg, int) : (flags & FLAGS_SHORT) ? (short int)va_arg(arg, int) : va_arg(arg, int);
                    idx = ntoa(stream, (unsigned int)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                }
            } else {
                if (flags & FLAGS_LONG_LONG)
                    idx = ntoa(stream, va_arg(arg, unsigned long long), 0, base, precision, width, flags, idx);
                else if (flags & FLAGS_LONG)
                    idx = ntoa(stream, va_arg(arg, unsigned long), 0, base, precision, width, flags, idx);
                else {
                    const unsigned int value = (flags & FLAGS_CHAR) ? (unsigned char)va_arg(arg, unsigned int) : (flags & FLAGS_SHORT) ? (unsigned short int)va_arg(arg, int) : va_arg(arg, int);
                    idx = ntoa(stream, value, 0, base, precision, width, flags, idx);
                }
            }
        }
        case 'c': {
            unsigned int l = 1;
            if (!(flags & FLAGS_LEFT)) {
                while (l++ < width) {
                    fputc(' ', stream);
                    idx++;
                }
            }

            fputc((char)va_arg(arg, int), stream);
            if (flags & FLAGS_LEFT) {
                while (l++ < width) {
                    fputc(' ', stream);
                    idx++;
                }
            }

            format++;
            break;
        }

        case 's': {
            const char* p = va_arg(arg, char*);
            unsigned int l = strnlen(p, precision ? precision : (size_t)-1);

            if (flags & FLAGS_PRECISION)
                l = (l < precision ? l : precision);

            if (!(flags & FLAGS_LEFT)) {
                while (l++ < width) {
                    fputc(' ', stream);
                    idx++;
                }
            }

            while ((*p != 0) && (!(flags & FLAGS_PRECISION) || precision--)) {
                fputc(*(p++), stream);
                idx++;
            }

            if (flags & FLAGS_LEFT) {
                while (l++ < width) {
                    fputc(' ', stream);
                    idx++;
                }
            }
            format++;
            break;
        }

        case 'p': {
            width = sizeof(void*) * 2;
            flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
            idx = ntoa(stream, (unsigned long long)va_arg(arg, void*), 0, 16, precision, width, flags, idx);
            format++;
            break;
        }

        case '%':
            fputc('%', stream);
            idx++;
            format++;
            break;

        default:
            fputc(*format, stream);
            idx++;
            format++;
            break;
        }
    }

    return idx;
}