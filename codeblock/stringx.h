/*  stringx - make string.h better
    by Raymai97 (cheeboonray@gmail.com) in April 2016
*/

#ifndef _STRINGX_H
#define _STRINGX_H

#ifdef _STRINGX_USE_WCHAR
    #include <wchar.h>
    typedef wchar_t STRX_CHAR;
#else
    typedef char STRX_CHAR;
#endif // _STRINGX_USE_WCHAR

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum
{
    STRX_NO_FLAG = 0,
    STRX_CASE_INSENSITIVE = 1,
    STRX_KEY_AS_SINGLE_CHAR = 2,
    STRX_COUNT_ONE_ONLY = 4,
    STRX_COUNT_NOT_KEY = 8
} STRX_FLAGS;

#define strxCAT(str, ...) strxCat(str, ##__VA_ARGS__, "")

bool strxIs(const STRX_CHAR *str1, const STRX_CHAR *str2, STRX_FLAGS f);
bool strxHas(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f);
size_t strxCount(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f);
size_t strxIndexOf(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f);
size_t strxLastIndexOf(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f);
size_t strxSplit(const STRX_CHAR *str, const STRX_CHAR *delim, STRX_CHAR ***strs, STRX_FLAGS f);
STRX_CHAR *strxCat(const STRX_CHAR *str, ...);
STRX_CHAR *strxSubstr(const STRX_CHAR *str, int offset, size_t count);
STRX_CHAR *strxUpper(const STRX_CHAR *str);
STRX_CHAR *strxLower(const STRX_CHAR *str);

#endif // _STRINGX_H
