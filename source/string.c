
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
