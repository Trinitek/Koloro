
#include "font.h"
#include "charset.h"

short getGlyph(char c) {
    switch (c) {
        // Numbers
        case '0': return &n_0_pxl;
        case '1': return &n_1_pxl;
        case '2': return &n_2_pxl;
        case '3': return &n_3_pxl;
        case '4': return &n_4_pxl;
        case '5': return &n_5_pxl;
        case '6': return &n_6_pxl;
        case '7': return &n_7_pxl;
        case '8': return &n_8_pxl;
        case '9': return &n_9_pxl;
        
        // Symbols
        case '&': return &amper_pxl;
        case '\'': return &apost_pxl;
        case '{': return &brace_l_pxl;
        case '}': return &brace_r_pxl;
        case '[': return &bracket_l_pxl;
        case ']': return &bracket_r_pxl;
        case '^': return &carat_pxl;
        case '<': return &chev_l_pxl;
        case '>': return &chev_r_pxl;
        case ':': return &colon_pxl;
        case ',': return &comma_pxl;
        case '-': return &dash_pxl;
        case '$': return &dollar_pxl;
        case '=': return &equal_pxl;
        case '!': return &exc_pxl;
        case 0: return &null_pxl;
        case '#': return &octo_pxl;
        case '(': return &parenth_l_pxl;
        case ')': return &parenth_r_pxl;
        case '%': return &percent_pxl;
        case '.': return &period_pxl;
        case '|': return &pipe_pxl;
        case '+': return &plus_pxl;
        case '?': return &question_pxl;
        case '"': return &quote_pxl;
        case ';': return &semi_pxl;
        case '\\': return &slash_b_pxl;
        case '/': return &slash_f_pxl;
        case '_': return &under_pxl;
        
        // Uppercase letters
        case 'A': return &u_a_pxl;
        case 'B': return &u_b_pxl;
        case 'C': return &u_c_pxl;
        case 'D': return &u_d_pxl;
        case 'E': return &u_e_pxl;
        case 'F': return &u_f_pxl;
        case 'G': return &u_g_pxl;
        case 'H': return &u_h_pxl;
        case 'I': return &u_i_pxl;
        case 'J': return &u_j_pxl;
        case 'K': return &u_k_pxl;
        case 'L': return &u_l_pxl;
        case 'M': return &u_m_pxl;
        case 'N': return &u_n_pxl;
        case 'O': return &u_o_pxl;
        case 'P': return &u_p_pxl;
        case 'Q': return &u_q_pxl;
        case 'R': return &u_r_pxl;
        case 'S': return &u_s_pxl;
        case 'T': return &u_t_pxl;
        case 'U': return &u_u_pxl;
        case 'V': return &u_v_pxl;
        case 'W': return &u_w_pxl;
        case 'X': return &u_x_pxl;
        case 'Y': return &u_y_pxl;
        case 'Z': return &u_z_pxl;
        
        // Lowercase letters
        case 'a': return &l_a_pxl;
        case 'b': return &l_b_pxl;
        case 'c': return &l_c_pxl;
        case 'd': return &l_d_pxl;
        case 'e': return &l_e_pxl;
        case 'f': return &l_f_pxl;
        case 'g': return &l_g_pxl;
        case 'h': return &l_h_pxl;
        case 'i': return &l_i_pxl;
        case 'j': return &l_j_pxl;
        case 'k': return &l_k_pxl;
        case 'l': return &l_l_pxl;
        case 'm': return &l_m_pxl;
        case 'n': return &l_n_pxl;
        case 'o': return &l_o_pxl;
        case 'p': return &l_p_pxl;
        case 'q': return &l_q_pxl;
        case 'r': return &l_r_pxl;
        case 's': return &l_s_pxl;
        case 't': return &l_t_pxl;
        case 'u': return &l_u_pxl;
        case 'v': return &l_v_pxl;
        case 'w': return &l_w_pxl;
        case 'x': return &l_x_pxl;
        case 'y': return &l_y_pxl;
        case 'z': return &l_z_pxl;
    }
}