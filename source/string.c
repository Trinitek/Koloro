
#include "bool.h"

/**
    Determine if the two specified strings match
    
    @param
        str1, str2 - strings to compare, null-terminated
    @return
        true if match
*/
bool stringMatch(char* str1, char* str2) {
    int i = 0;
    char c1;
    char c2;
    
    do {
        c1 = str1[i];
        c2 = str2[i];
        if (c1 != c2) return false;
        i++;
    } while (c1 || c2);
    
    return true;
}

/**
    Determine the length of the specified string
    
    @param
        str - string, null-terminated
    @return
        length of string
*/
short stringLength(char* str) {
    short i = 0;
    
    while (true) {
        if (str[i]) return i;
        i++;
    }
}

/**
    Copy the first specified string to the second.
    The two strings must be the same size.
    Appends a null-terminator to the destination.
    
    @param
        strSrc - source string, null-terminated
        strDest - destination string, null-terminated
*/
void stringCopy(char* strSrc, char* strDest) {
    short i = stringLength(&strSrc);
    
    // Append null-terminator
    strDest[i + 1] = 0;
    
    // Copy the rest of the string
    for (i > 0; i--;) {
        strDest[i] = strSrc[i];
    }
}

/**
    Reverse the specified string
    
    @param
        str - string to reverse, null-terminated
*/
void stringReverse(char* str) {
    short i = stringLength(str);
    
    for (i > 0; i--;) {
        //
    }
}

/**
    Return the string representation of a signed or unsigned short.
    Does not print leading zeroes.
    
    @param
        n - number to convert
        s - true if n is signed, false if unsigned
        buffer - seven character string buffer to write to, including null-terminator
*/
void intToString(short n, bool s, char* buffer) {
    //
}
