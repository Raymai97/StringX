/*  stringx - make string.h better
    by Raymai97 (cheeboonray@gmail.com) in April 2016
*/

#include "stringx.h"

#define FLAG(x) ((f & x) == x)
#define UPPER(c) ((c >= 'a' && c <= 'z') ? c-('a'-'A') : c)
#define LOWER(c) ((c >= 'A' && c <= 'Z') ? c+('a'-'A') : c)
#define SAME(c1, c2) ( (FLAG(STRX_CASE_INSENSITIVE) && (LOWER(c1)==LOWER(c2))) || (c1==c2) )

#ifdef _STRINGX_USE_WCHAR
    #define STRLEN(x) wcslen(x)
    #define STRCAT(x) wcscat(x)
    #define STRCPY(x) wcscpy(x)
    #define STRNCPY(dest, src, count) wcsncpy(dest, src, count)
#else
    #define STRLEN(x) strlen(x)
    #define STRCAT(s1, s2) strcat(s1, s2)
    #define STRCPY(dest, src) strcpy(dest, src)
    #define STRNCPY(dest, src, count) strncpy(dest, src, count)
#endif // _STRINGX_USE_WCHAR

bool strxIs(const STRX_CHAR *str1, const STRX_CHAR *str2, STRX_FLAGS f)
{
    if (STRLEN(str1) != STRLEN(str2)) return false;
    size_t i;
    for (i = 0; str1[i] != '\0'; i++)
    {
        if ( !SAME(str1[i], str2[i]) ) { return false; }
    }
    return true;
}

bool strxHas(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f)
{
    return strxCount(str, key, f | STRX_COUNT_ONE_ONLY);
}

size_t strxCount(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f)
{
    if (STRLEN(key) == 0) return 0;
    size_t i, j = 0, count = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (FLAG(STRX_KEY_AS_SINGLE_CHAR))
        {
            for (j = 0; key[j] != '\0'; j++)
            {
                if (SAME(str[i], key[j]))
                {
                    if (FLAG(STRX_COUNT_ONE_ONLY)) { return 1; }
                    else { count++; break; }
                }
            }
        }
        else
        {
            if (key[j] == '\0')
            {
                if (FLAG(STRX_COUNT_ONE_ONLY)) { return 1; }
                else { count++; j = 0; }
            }
            else if (SAME(str[i], key[j])) { j++; }
            else { j = 0; }
        }
    }
    if (FLAG(STRX_COUNT_NOT_KEY)) { count = strlen(str) - count; }
    return count;
}

size_t strxIndexOf(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f)
{
    size_t len1 = STRLEN(str), len2 = STRLEN(key);
    if (len2 == 0) return len1;
    size_t i, j = 0;
    for (i = 0; i < len1; i++)
    {
        if (FLAG(STRX_KEY_AS_SINGLE_CHAR))
        {
            for (j = 0; j < len2; j++)
            {
                if (SAME(str[i], key[j])) { return i; }
            }
        }
        else
        {
            if (key[j] == '\0') { return i-j; }
            else if (SAME(str[i], key[j])) { j++; }
            else { j = 0; }
        }
    }
    return len1;
}

size_t strxLastIndexOf(const STRX_CHAR *str, const STRX_CHAR *key, STRX_FLAGS f)
{
    size_t len1 = STRLEN(str), len2 = STRLEN(key);
    if (len2 == 0) return len1;
    size_t i, j = len2 - 1;
    for (i = len1; i --> 0 ;) // will i-=1 after checking condition
    {
        if (FLAG(STRX_KEY_AS_SINGLE_CHAR))
        {
            for (j = 0; j < len2; j++)
            {
                if (SAME(str[i], key[j])) { return i; }
            }
        }
        else
        {
            if (j == 0) { return i; }
            else if (SAME(str[i], key[j])) { j--; }
            else { j = len2 - 1; }
        }
    }
    return len1;
}

size_t strxSplit(const STRX_CHAR *str, const STRX_CHAR *delim, STRX_CHAR ***strs, STRX_FLAGS f)
{
    size_t len1 = STRLEN(str), len2 = STRLEN(delim);
    if (len1 == 0) return 0;
    if (len2 == 0) return 0;
    // If not happy but met non-delim, will be happy, set Start Index, partCount++
    // If happy but met delim, will be unhappy, if partCount > 0 then set End Index
    bool same = false, happy = false;
    size_t i, j = 0, iStart[len1], iEnd[len1], partCount = 0;
    if (FLAG(STRX_KEY_AS_SINGLE_CHAR))
    {
        for (i = 0; i < len1; i++)
        {
            for (j = 0; j < len2; j++)
            {
                same = SAME(str[i], delim[j]);
                if (same) { break; }
            }
            if (same && happy)
            {
                happy = false;
                if (partCount > 0) { iEnd[partCount-1] = i - 1; }
            }
            else if (!same && !happy)
            {
                happy = true;
                iStart[partCount++] = i;
            }
        }
    }
    else
    {
        for (i = 0; i < len1; i++)
        {
            if (j < len2)
            {
                if (SAME(str[i], delim[j])) { j++; }
                else { j = 0; }
            }
            if (j == len2 && happy)
            {
                happy = false;
                if (partCount > 0) { iEnd[partCount-1] = i - j; }
                j = 0;
            }
            else if (!happy)
            {
                happy = true;
                iStart[partCount++] = i;
            }
        }
    }
    // If not ends with delims, let last part take the rest
    if (happy) { iEnd[partCount-1] = len1 - 1; }
    // Init string array
    *strs = malloc(partCount * sizeof(STRX_CHAR*));
    for (i = 0; i < partCount; i++)
    {
        (*strs)[i] = strxSubstr(str, iStart[i], iEnd[i] - iStart[i] + 1);
    }
    return partCount;
}

STRX_CHAR *strxCat(const STRX_CHAR *str, ...)
{
    // Count got how many args after str
    size_t i, count = 0, len, totalLen = STRLEN(str);
    va_list ap;
    va_start(ap, 0);
    while ((len = STRLEN( va_arg(ap, STRX_CHAR*) )) > 0)
    {
        totalLen += len;
        count++;
    }
    va_end(ap);
    // Malloc, Strcpy the first str
    STRX_CHAR *ret = malloc((totalLen + 1) * sizeof(STRX_CHAR));
    STRCPY(ret, str);
    // Concat the rest
    va_start(ap, 0);
    for (i = 0; i < count; i++)
    {
        STRCAT(ret, va_arg(ap, STRX_CHAR*));
    }
    va_end(ap);
    ret[totalLen] = '\0';
    return ret;
}

STRX_CHAR *strxSubstr(const STRX_CHAR *str, int offset, size_t count)
{
    size_t len = STRLEN(str);
    if (offset < 0) { offset += len; }
    if (offset > len-1) { offset = len; }
    if (offset+count > len) { count = len - offset; }
    STRX_CHAR *ret = malloc((count + 1) * sizeof(STRX_CHAR));
    STRNCPY(ret, str + offset, count);
    ret[count] = '\0';
    return ret;
}

STRX_CHAR *strxUpper(const STRX_CHAR *str)
{
    size_t i, len = STRLEN(str);
    STRX_CHAR c, *ret = malloc((len + 1) * sizeof(STRX_CHAR));
    for (i = 0; (c = str[i]) != '\0'; i++)
    {
        ret[i] = UPPER(c);
    }
    ret[len] = '\0';
    return ret;
}

STRX_CHAR *strxLower(const STRX_CHAR *str)
{
    size_t i, len = STRLEN(str);
    STRX_CHAR c, *ret = malloc((len + 1) * sizeof(STRX_CHAR));
    for (i = 0; (c = str[i]) != '\0'; i++)
    {
        ret[i] = LOWER(c);
    }
    ret[len] = '\0';
    return ret;
}

