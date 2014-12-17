
#include "math.h"
#include "fixed.h"

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
        "fidiv word [bp + 6] \n"    // ST0 = ST0 / 100
        "fsin \n"                   // ST0 = sin(ST0)
        "fimul word [bp + 6] \n"    // ST0 = ST0 * 100
        "fist word [bp + 8]"        // result = (int)ST0
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
        "fidiv word [bp + 6] \n"    // ST0 = ST0 / 100
        "fcos \n"                   // ST0 = cos(ST0)
        "fimul word [bp + 6] \n"    // ST0 = ST0 * 100
        "fist word [bp + 8]"        // result = (int)ST0
        );
}