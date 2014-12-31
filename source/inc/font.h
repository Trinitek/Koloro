
#ifndef _FONT_H
#define _FONT_H

typedef enum {
    // Numbers
    N0, N1, N2, N3, N4, N5, N6, N7, N8, N9,
    
    // Symbols
    AMPER, APOST, BRACEL, BRACER, BRACKETL, BRACKETR,
    CARAT, CHEVL, CHEVR, COLON, COMMA, DASH, DOLLAR,
    EXC, NUL, OCTO, PARENTHL, PARENTHR, PERCENT, PERIOD,
    PIPE, PLUS, QUESTION, QUOTE, SEMI, SLASHB, SLASHF, UNDER,
    
    // Uppercase letters
    UA, UB, UC, UD, UE, UF, UG, UH, UI, UJ, UK, UL, UM,
    UN, UO, UP, UQ, UR, US, UT, UU, UV, UW, UX, UY, UZ,
    
    // Lowercase letters
    LA, LB, LC, LD, LE, LF, LG, LH, LI, LJ, LK, LL, LM,
    LN, LO, LP, LQ, LR, LS, LT, LU, LV, LW, LX, LY, LZ
} chartype_t;

#endif