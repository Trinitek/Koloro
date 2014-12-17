
#include "math.h"
#include "fixed.h"

fixed sin(fixed x) {
    short divisor = 100;
    fixed result;
    asm("fninit \n"                 // initialize FPU
        "fnclex \n"                 // clear previous exceptions
        
        "fild word [bp + 4] \n"     // ST0 = x
        "fidiv word [bp + 6] \n"         // ST0 = ST0 / 100
        "fsin \n"                   // ST0 = sin(ST0)
        "fimul word [bp + 6] \n"         // ST0 = ST0 * 100
        "fist word [bp + 8]"             // result = (int)ST0
        );
}

fixed cos(fixed x) {
    //
}