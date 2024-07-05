#ifndef PRINTF_H
#define PRINTF_H

#define STB_SPRINTF_DECORATE(name) name
#define STB_SPRINTF_IMPLEMENTATION 1
#define STB_SPRINTF_STATIC
#define STB_SPRINTF_NOFLOAT 1

#define PRINT_BUF 8192

#include "stb_sprintf.h"
#include "util.h"

// Function declaration
int kprintf(const char *format, ...);

#endif // PRINTF_H
