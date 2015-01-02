
#include "math.h"
#include "fixed.h"

/*
    Calculate the absolute value of the given number
    
    @param
        x - signed number
    @return
        absolute value of x
*/
short abs(short x) {
    short result;
    asm("fninit \n"                 // initialize FPU
        "fnclex \n"                 // clear previous exceptions
        
        "fild word [bp + 4] \n"     // ST0 = x
        "fabs \n"                   // ST0 = abs(ST0)
        "fist word [bp - 2] \n"     // result = ST0
        );
}

/*
    Calculate the sine of the given angle provided in radians
    
    @param
        x - angle in radians
    
    @return
        sine of the provided angle
*/
fixed sin(fixed x) {
    short divisor = 100;
    fixed result;
    asm("fninit \n"                 // initialize FPU
        "fnclex \n"                 // clear previous exceptions
        
        "fild word [bp + 4] \n"     // ST0 = x
        "fidiv word [bp - 2] \n"    // ST0 = ST0 / 100
        "fsin \n"                   // ST0 = sin(ST0)
        "fimul word [bp - 2] \n"    // ST0 = ST0 * 100
        "fist word [bp - 4]"        // result = (int)ST0
        );
}

/*
    Calculate the cosine of the given angle provided in radians
    
    @param
        x - angle in radians
    
    @return
        cosine of the provided angle
*/
fixed cos(fixed x) {
    short divisor = 100;
    fixed result;
    asm("fninit \n"                 // initialize FPU
        "fnclex \n"                 // clear previous exceptions
        
        "fild word [bp + 4] \n"     // ST0 = x
        "fidiv word [bp - 2] \n"    // ST0 = ST0 / 100
        "fcos \n"                   // ST0 = cos(ST0)
        "fimul word [bp - 2] \n"    // ST0 = ST0 * 100
        "fist word [bp - 4]"        // result = (int)ST0
        );
}