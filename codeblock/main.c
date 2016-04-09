// Demo of StringX
// Define _STRINGX_USE_WCHAR in Compiler settings if you want to use wchar_t

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "stringx.h"

#define PAUSE(); printf("Press any key to go on...");_getch();printf("\n\n\n\n");

int main()
{
    const char *testStr1 = "Always try your best in life, as if tomorrow is deadline.";
    const char *testStr2 = "The number of PI is 3.1415926535...";
    const char *testStr3 = strxCAT(
        "Can you feel my heart?\n",
        "Itsu ma demo\n",
        "Anata no kanaderu RIZUMU wo\n",
        "Kanjitai\n",
        "Can you feel my beat?\n",
        "Hohoemi ga\n",
        "Sekai wo yurukzu MERODI\n",
        "Tsukuri dasu\n");
    const char *NUMBER_CHARS = "1234567890";
    const char *ALPHABET_CHARS = "QWERTYUIOPASDFGHJKLZXCVBNM";

    size_t count, i, j;
    char **strArray;

    printf("testStr1 ... \n\n");
    count = strxSplit(testStr1, " ,.", &strArray, STRX_KEY_AS_SINGLE_CHAR);
    printf(" Split by \" ,.\" ... strArray now has %i strings. \n", count);
    for (i = 0; i < count; i++)
    {
        printf(" [%3i] %s \n", i+1, strArray[i]);
    }
    printf("\n");
    PAUSE();

    // Find FIRST and LAST '123...' char, and extract them.
    printf("testStr2 ... \n\n");
    i = strxIndexOf(testStr2, NUMBER_CHARS, STRX_KEY_AS_SINGLE_CHAR);
    j = strxLastIndexOf(testStr2, NUMBER_CHARS, STRX_KEY_AS_SINGLE_CHAR);
    printf(" The first number is at index %i \n The last number is at index %i. \n", i , j);
    printf(" Substring result: %s \n\n", strxSubstr(testStr2, i, j-i));

    // How many chars are NOT number?
    count = strxCount(testStr2, NUMBER_CHARS, STRX_KEY_AS_SINGLE_CHAR | STRX_COUNT_NOT_KEY);
    printf(" Excluding decimal point, there are %i chars are NOT number. \n\n", count);
    PAUSE();

    // As long as every line is ended with '\n', we can get how many lines is in a string.
    printf("testStr3 ... \n\n");
    count = strxCount(testStr3, "\n", STRX_KEY_AS_SINGLE_CHAR);
    printf("      Line count: %i \n", count);
    // Count of UPPERCASE and lowercase (alphabets only)
    count = strxCount(testStr3, ALPHABET_CHARS, STRX_KEY_AS_SINGLE_CHAR);
    printf(" UPPERCASE count: %i \n", count);
    // Yes, StringX let you easily change the case of string.
    count = strxCount(testStr3, strxLower(ALPHABET_CHARS), STRX_KEY_AS_SINGLE_CHAR);
    printf(" lowercase count: %i \n\n", count);

    printf("End of demo...\n\n");
    PAUSE();

    return 0;
}
