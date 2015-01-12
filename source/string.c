
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
    
    while (str[i]) {
        i++;
    } return i;
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
    int i = 0;
    char c;
    
    do {
        c = strSrc[i];
        strDest[i] = c;
        i++;
    } while (c);
}

/**
    Reverse the specified string
    
    @param
        strSrc - string to reverse, null-terminated
        strDest - string to save reversed strSrc, null-terminated
*/
void stringReverse(char* strSrc, char* strDest) {
    short reverseOfs = stringLength(strSrc) - 1;
    short forwardOfs = 0;
    
    for (; reverseOfs >= 0; reverseOfs--) {
        strDest[forwardOfs] = strSrc[reverseOfs];
        forwardOfs++;
    }
}

/**
    Return the string representation of a signed short.
    Does not print leading zeroes.
    
    @param
        n - number to convert
        str - seven character string buffer to write to, including null-terminator
*/
void intToString(short n, char* str) {
    int i;
    int digits = 5;
    int tempN = n;
    
    if (n == 0) {
        str[0] = '0';
        str[1] = 0;
    }
    
    else {
        // Determine the number of digits
        for (i = 10000; i > 0; i /= 10) {
            if (n / i) break;
            else digits--;
        }
        
        // Add or substract to get the ASCII representation?
        if (n < 0) tempN *= -1;
        
        // Write digits to string, least significant digits first
        for (i = digits; i > 0; i--) {
            str[i] = (tempN % 10) + 48;
            tempN /= 10;
        }
        
        str[0] = '-';
        str[digits + 1] = 0;
    }
    
    return;
}

/**
    Return the string representation of an unsigned short.
    Does not print leading zeroes.
    
    @param
        n - number to convert
        str - seven character string buffer to write to, including null-terminator
*/
void uintToString(unsigned short n, char* str) {
    int i;
    int digits = 5;
    unsigned int tempN = n;
    
    if (n == 0) {
        str[0] = '0';
        str[1] = 0;
    }
    
    else {
        // Determine the number of digits
        for (i = 10000; i > 0; i /= 10) {
            if (n / i) break;
            else digits--;
        }
        
        // Write digits to string, least significant digits first
        for (i = digits - 1; i >= 0; i--) {
            str[i] = (tempN % 10) + 48;
            tempN /= 10;
        }
        
        str[digits] = 0;
    }
    
    return;
}
