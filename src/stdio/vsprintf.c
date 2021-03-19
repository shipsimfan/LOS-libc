#include <stdio.h>

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
#define PRINTF_FTOA_BUFFER_SIZE 32
#define PRINTF_MAX_FLOAT 1e9

static const double POW10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

size_t ntoa(char** s, unsigned long long value, int negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned flags, size_t idx);
size_t ftoa(char** s, double value, unsigned int prec, unsigned int width, unsigned int flags, size_t idx);

size_t etoa(char** s, double value, unsigned int prec, unsigned int width, unsigned int flags, size_t idx) {
    if (value != value || value > __DBL_MAX__ || value < -__DBL_MAX__)
        return ftoa(s, value, prec, width, flags, idx);

    const int negative = value < 0;
    if (negative)
        value = -value;

    if (!(flags & FLAGS_PRECISION))
        prec = 6;

    union {
        unsigned long long u;
        double f;
    } conv;

    conv.f = value;
    int exp2 = (int)((conv.u >> 52) & 0x07FF) - 1023;
    conv.u = (conv.u & ((1ULL << 52) - 1)) | (1023ULL << 52);
    int expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.f - 1.5) * 0.289529654602168);
    exp2 = (int)(expval * 3.321928094887362 + 0.5);
    const double z = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
    const double z2 = z * z;
    conv.u = (unsigned long long)(exp2 + 1023) << 52;
    conv.f *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));

    if (value < conv.f) {
        expval--;
        conv.f /= 10;
    }

    unsigned int minWidth = (expval < 100 && expval > -100) ? 4 : 5;

    if (flags & FLAGS_ADAPT_EXP) {
        if (value >= 1e-4 && value < 1e6) {
            if ((int)prec > expval)
                prec = (unsigned)((int)prec - expval - 1);
            else
                prec = 0;
        }

        flags |= FLAGS_PRECISION;
        minWidth = 0;
        expval = 0;
    } else if (prec > 0 && (flags & FLAGS_PRECISION))
        prec--;

    unsigned int fwidth = width;
    if (width > minWidth)
        fwidth -= minWidth;
    else
        fwidth = 0;

    if ((flags & FLAGS_LEFT) && minWidth)
        fwidth = 0;

    if (expval)
        value /= conv.f;

    const size_t startIdx = idx;
    idx = ftoa(s, negative ? -value : value, prec, fwidth, flags & ~FLAGS_ADAPT_EXP, idx);

    if (minWidth) {
        **s = (flags & FLAGS_UPPERCASE) ? 'E' : 'e';
        *s++;
        idx++;

        idx = ntoa(s, (expval < 0) ? -expval : expval, expval < 0, 10, 0, minWidth - 1, FLAGS_ZEROPAD | FLAGS_PLUS, idx);
        if (flags & FLAGS_LEFT) {
            while (idx - startIdx < width) {
                **s = ' ';
                *s++;
                idx++;
            }
        }
    }

    return idx;
}

size_t ftoa(char** s, double value, unsigned int prec, unsigned int width, unsigned int flags, size_t idx) {
    char buf[PRINTF_FTOA_BUFFER_SIZE];
    if (value != value) {
        s[0][0] = 'n';
        s[0][1] = 'a';
        s[0][2] = 'n';
        *s += 3;
        return idx + 3;
    }
    if (value < -__DBL_MAX__) {
        s[0][0] = '-';
        s[0][1] = 'i';
        s[0][2] = 'n';
        s[0][3] = 'f';
        *s += 4;
        return idx + 4;
    }
    if (value > __DBL_MAX__) {
        s[0][0] = 'i';
        s[0][1] = 'n';
        s[0][2] = 'f';
        *s += 3;
        return idx + 3;
    }

    if (value > PRINTF_MAX_FLOAT || value < -PRINTF_MAX_FLOAT)
        return etoa(s, value, prec, width, flags, idx);

    int negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }

    if (!(flags & FLAGS_PRECISION))
        prec = 6;

    size_t len = 0;
    while (len < PRINTF_FTOA_BUFFER_SIZE && prec > 9) {
        buf[len++] = '0';
        prec--;
    }

    int whole = (int)value;
    double tmp = (value - whole) * POW10[prec];
    unsigned long frac = (unsigned long)tmp;
    double diff = tmp - frac;

    if (diff > 0.5) {
        frac++;
        if (frac >= POW10[prec]) {
            frac = 0;
            whole++;
        }
    } else if (diff < 0.5)
        ;
    else if (frac == 0 || (frac & 1))
        frac++;

    if (prec == 0) {
        diff = value - (double)whole;
        if ((!(diff < 0.5) || diff > 0.5) && (whole & 1))
            whole++;
    } else {
        unsigned int count = prec;
        while (len < PRINTF_FTOA_BUFFER_SIZE) {
            count--;
            buf[len++] = (char)(48 + (frac % 10));
            if (!(frac /= 10))
                break;
        }

        while (len < PRINTF_FTOA_BUFFER_SIZE && count-- > 0)
            buf[len++] = '0';

        if (len < PRINTF_FTOA_BUFFER_SIZE)
            buf[len++] = '.';
    }

    while (len < PRINTF_FTOA_BUFFER_SIZE) {
        buf[len++] = (char)(48 + (whole % 10));
        if (!(whole /= 10))
            break;
    }

    if (!(flags & FLAGS_LEFT) && (flags & FLAGS_ZEROPAD)) {
        if (width && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE))))
            width--;

        while ((len < width) && (len < PRINTF_FTOA_BUFFER_SIZE))
            buf[len++] = '0';
    }

    if (len < PRINTF_FTOA_BUFFER_SIZE) {
        if (negative)
            buf[len++] = '-';
        else if (flags & FLAGS_PLUS)
            buf[len++] = '+';
        else if (flags & FLAGS_SPACE)
            buf[len++] = ' ';
    }

    while (len) {
        **s = buf[--len];
        *s++;
        idx++;
    }

    return idx;
}

size_t ntoa(char** s, unsigned long long value, int negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned flags, size_t idx) {
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
            **s = ' ';
            *s++;
            idx++;
        }
    }

    while (len) {
        **s = buf[--len];
        *s++;
        idx++;
    }

    if (flags & FLAGS_LEFT) {
        while (idx - start_idx < width) {
            **s = ' ';
            *s++;
            idx++;
        }
    }

    return idx;
}

int vsprintf(char* s, const char* format, va_list arg) {
    unsigned int flags, width, precision, n;
    size_t idx = 0;

    while (*format) {
        // Check for specifier
        if (*format != '%') {
            *s = *format;
            s++;
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
                    idx = ntoa(&s, (unsigned long long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                } else if (flags & FLAGS_LONG) {
                    const long value = va_arg(arg, long);
                    idx = ntoa(&s, (unsigned long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                } else {
                    const int value = (flags & FLAGS_CHAR) ? (char)va_arg(arg, int) : (flags & FLAGS_SHORT) ? (short int)va_arg(arg, int) : va_arg(arg, int);
                    idx = ntoa(&s, (unsigned int)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags, idx);
                }
            } else {
                if (flags & FLAGS_LONG_LONG)
                    idx = ntoa(&s, va_arg(arg, unsigned long long), 0, base, precision, width, flags, idx);
                else if (flags & FLAGS_LONG)
                    idx = ntoa(&s, va_arg(arg, unsigned long), 0, base, precision, width, flags, idx);
                else {
                    const unsigned int value = (flags & FLAGS_CHAR) ? (unsigned char)va_arg(arg, unsigned int) : (flags & FLAGS_SHORT) ? (unsigned short int)va_arg(arg, int) : va_arg(arg, int);
                    idx = ntoa(&s, value, 0, base, precision, width, flags, idx);
                }
            }

            format++;
            break;
        }
        case 'f':
        case 'F':
            if (*format == 'F')
                flags |= FLAGS_UPPERCASE;

            idx = ftoa(&s, va_arg(arg, double), precision, width, flags, idx);
            format++;
            break;

        case 'e':
        case 'E':
        case 'g':
        case 'G':
            if (*format == 'g' || *format == 'G')
                flags |= FLAGS_ADAPT_EXP;
            if (*format == 'E' || *format == 'G')
                flags |= FLAGS_UPPERCASE;

            idx = etoa(&s, va_arg(arg, double), precision, width, flags, idx);
            format++;
            break;

        case 'c': {
            unsigned int l = 1;
            if (!(flags & FLAGS_LEFT)) {
                while (l++ < width) {
                    *s = ' ';
                    s++;
                    idx++;
                }
            }

            *s = (char)va_arg(arg, int);
            if (flags & FLAGS_LEFT) {
                while (l++ < width) {
                    *s = ' ';
                    s++;
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
                    *s = ' ';
                    s++;
                    idx++;
                }
            }

            while ((*p != 0) && (!(flags & FLAGS_PRECISION) || precision--)) {
                *s = *(p++);
                s++;
                idx++;
            }

            if (flags & FLAGS_LEFT) {
                while (l++ < width) {
                    *s = ' ';
                    s++;
                    idx++;
                }
            }
            format++;
            break;
        }

        case 'p': {
            width = sizeof(void*) * 2;
            flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
            idx = ntoa(&s, (unsigned long long)va_arg(arg, void*), 0, 16, precision, width, flags, idx);
            format++;
            break;
        }

        case '%':
            *s = '%';
            s++;
            idx++;
            format++;
            break;

        default:
            *s = *format;
            s++;
            idx++;
            format++;
            break;
        }
    }

    *s = 0;

    return idx;
}