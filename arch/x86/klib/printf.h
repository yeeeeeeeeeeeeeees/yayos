#ifndef PRINTF_H
#define PRINTF_H

#define STB_SPRINTF_DECORATE(name) name
#define STB_SPRINTF_IMPLEMENTATION 1
#define STB_SPRINTF_NOFLOAT 1

#define PRINT_BUF 8192

#include "stb_sprintf.h"
#include "util.h"

int printf(const char *format, ...)
{
    va_list args;
    char buffer[PRINT_BUF];
    size_t length;

    va_start(args, format);

    length = vsnprintf(buffer, PRINT_BUF, format, args);
    for (size_t i=0;i<length;i++)
    {
         putchar(buffer[i]);
    }

    va_end(args);

    return length;
}


#endif
