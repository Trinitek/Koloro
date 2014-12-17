
#ifndef _TYPEDEF_FIXED
#define _TYPEDEF_FIXED
typedef short fixed;
#endif

fixed getFixed(short whole, char decimal);
short getWhole(fixed x);
char getDecimal(fixed x);
fixed setWhole(fixed x, short whole);
fixed setDecimal(fixed x, char decimal);