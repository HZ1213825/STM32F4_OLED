#include "Fort.h"
const OLED_Alphanumeric_Array OLED_Num_HEX_Small[16] = {OLED_0, OLED_1, OLED_2, OLED_3, OLED_4, OLED_5, OLED_6, OLED_7, OLED_8, OLED_9};
const OLED_Alphanumeric_Array OLED_Num_HEX_Big[16] = {OLED_0, OLED_1, OLED_2, OLED_3, OLED_4, OLED_5, OLED_6, OLED_7, OLED_8, OLED_9, OLED_A, OLED_B, OLED_C, OLED_D, OLED_E, OLED_F};
const OLED_Alphanumeric_Array OLED_Letter_Small[26] = {OLED_a, OLED_b, OLED_c, OLED_d, OLED_e, OLED_f, OLED_g, OLED_h, OLED_i, OLED_j, OLED_k, OLED_l, OLED_m, OLED_n, OLED_o, OLED_p, OLED_q, OLED_r, OLED_s, OLED_t, OLED_u, OLED_v, OLED_w, OLED_x, OLED_y, OLED_z};
const OLED_Alphanumeric_Array OLED_Letter_Big[26] = {OLED_A, OLED_B, OLED_C, OLED_D, OLED_E, OLED_F, OLED_G, OLED_H, OLED_I, OLED_J, OLED_K, OLED_L, OLED_M, OLED_N, OLED_O, OLED_P, OLED_Q, OLED_R, OLED_S, OLED_T, OLED_U, OLED_V, OLED_W, OLED_X, OLED_Y, OLED_Z};
/*数字 字体System*/
uc8 OLED_0[2][8] = {0x00, 0x00, 0xF0, 0xF8, 0x08, 0x68, 0xF8, 0xF0, 0x00, 0x00, 0x07, 0x0F, 0x0B, 0x08, 0x0F, 0x07}; /*"0",0*/
uc8 OLED_1[2][8] = {0x00, 0x20, 0x20, 0x30, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00}; /*"1",1*/
uc8 OLED_2[2][8] = {0x00, 0x30, 0x38, 0x08, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x0C, 0x0E, 0x0B, 0x09, 0x08, 0x08, 0x00}; /*"2",2*/
uc8 OLED_3[2][8] = {0x00, 0x30, 0x38, 0x88, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x06, 0x0E, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"3",3*/
uc8 OLED_4[2][8] = {0x00, 0x00, 0xF8, 0xF8, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x03, 0x03, 0x02, 0x02, 0x0F, 0x0F, 0x02}; /*"4",4*/
uc8 OLED_5[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0x88, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x0C, 0x07, 0x03, 0x00}; /*"5",5*/
uc8 OLED_6[2][8] = {0x00, 0xC0, 0xE0, 0x78, 0x58, 0xC8, 0x80, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"6",6*/
uc8 OLED_7[2][8] = {0x00, 0x08, 0x08, 0x88, 0xE8, 0x78, 0x18, 0x00, 0x00, 0x00, 0x0E, 0x0F, 0x01, 0x00, 0x00, 0x00}; /*"7",7*/
uc8 OLED_8[2][8] = {0x00, 0x70, 0xF8, 0xC8, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x09, 0x0F, 0x07, 0x00}; /*"8",8*/
uc8 OLED_9[2][8] = {0x00, 0xF0, 0xF8, 0x08, 0x08, 0xF8, 0xF0, 0x00, 0x00, 0x00, 0x09, 0x0D, 0x0F, 0x03, 0x01, 0x00}; /*"9",9*/

/*小写字母 字体System*/
uc8 OLED_a[2][8] = {0x00, 0x00, 0x20, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x06, 0x0F, 0x09, 0x09, 0x0F, 0x0F, 0x00}; /*"a",0*/
uc8 OLED_b[2][8] = {0x00, 0xF8, 0xF8, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"b",1*/
uc8 OLED_c[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0x60, 0x40, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0C, 0x04, 0x00}; /*"c",2*/
uc8 OLED_d[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0xF8, 0xF8, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x0F, 0x00}; /*"d",3*/
uc8 OLED_e[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x07, 0x0F, 0x09, 0x09, 0x09, 0x01, 0x00}; /*"e",4*/
uc8 OLED_f[2][8] = {0x00, 0x80, 0xF0, 0xF8, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00}; /*"f",5*/
uc8 OLED_g[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0xE0, 0xE0, 0x00, 0x00, 0x47, 0x4F, 0x48, 0x48, 0x7F, 0x3F, 0x00}; /*"g",6*/
uc8 OLED_h[2][8] = {0x00, 0xF8, 0xF8, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x0F, 0x0F, 0x00}; /*"h",7*/
uc8 OLED_i[2][8] = {0x00, 0x20, 0x20, 0xEC, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00}; /*"i",8*/
uc8 OLED_j[2][8] = {0x00, 0x00, 0x20, 0x20, 0xEC, 0xEC, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x7F, 0x3F, 0x00, 0x00}; /*"j",9*/
uc8 OLED_k[2][8] = {0x00, 0xF8, 0xF8, 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x0F, 0x0F, 0x01, 0x03, 0x0E, 0x0C, 0x00}; /*"k",10*/
uc8 OLED_l[2][8] = {0x00, 0x08, 0x08, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0F, 0x0F, 0x08, 0x08, 0x00}; /*"l",11*/
uc8 OLED_m[2][8] = {0x00, 0xE0, 0xE0, 0x20, 0xE0, 0x20, 0xE0, 0xC0, 0x00, 0x0F, 0x0F, 0x00, 0x07, 0x00, 0x0F, 0x0F}; /*"m",12*/
uc8 OLED_n[2][8] = {0x00, 0xE0, 0xE0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x0F, 0x0F, 0x00}; /*"n",13*/
uc8 OLED_o[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"o",14*/
uc8 OLED_p[2][8] = {0x00, 0xE0, 0xE0, 0x20, 0x20, 0xE0, 0xC0, 0x00, 0x00, 0x7F, 0x7F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"p",15*/
uc8 OLED_q[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0xE0, 0xE0, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x7F, 0x7F, 0x00}; /*"q",16*/
uc8 OLED_r[2][8] = {0x00, 0xE0, 0xE0, 0x80, 0x40, 0x60, 0x60, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00}; /*"r",17*/
uc8 OLED_s[2][8] = {0x00, 0xC0, 0xE0, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x08, 0x09, 0x09, 0x09, 0x0F, 0x06, 0x00}; /*"s",18*/
uc8 OLED_t[2][8] = {0x00, 0x20, 0xF8, 0xF8, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x08, 0x00}; /*"t",19*/
uc8 OLED_u[2][8] = {0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x0F, 0x00}; /*"u",20*/
uc8 OLED_v[2][8] = {0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x00, 0x03, 0x07, 0x0C, 0x0C, 0x07, 0x03, 0x00}; /*"v",21*/
uc8 OLED_w[2][8] = {0x00, 0xE0, 0xE0, 0x00, 0xC0, 0x00, 0xE0, 0xE0, 0x00, 0x03, 0x0F, 0x0C, 0x03, 0x0C, 0x0F, 0x03}; /*"w",22*/
uc8 OLED_x[2][8] = {0x00, 0x60, 0xE0, 0x80, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x0C, 0x0E, 0x03, 0x03, 0x0E, 0x0C, 0x00}; /*"x",23*/
uc8 OLED_y[2][8] = {0x00, 0xE0, 0xE0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x40, 0x47, 0x4F, 0x68, 0x38, 0x1F, 0x07, 0x00}; /*"y",24*/
uc8 OLED_z[2][8] = {0x00, 0x20, 0x20, 0x20, 0xA0, 0xE0, 0x60, 0x00, 0x00, 0x0C, 0x0E, 0x0B, 0x09, 0x08, 0x08, 0x00}; /*"z",25*/

/*大写字母 字体System*/
uc8 OLED_A[2][8] = {0x00, 0xE0, 0xF0, 0x18, 0x18, 0xF0, 0xE0, 0x00, 0x00, 0x0F, 0x0F, 0x01, 0x01, 0x0F, 0x0F, 0x00}; /*"A",0*/
uc8 OLED_B[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"B",1*/
uc8 OLED_C[2][8] = {0x00, 0xF0, 0xF8, 0x08, 0x08, 0x38, 0x30, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0E, 0x06, 0x00}; /*"C",2*/
uc8 OLED_D[2][8] = {0x00, 0xF8, 0xF8, 0x08, 0x18, 0xF0, 0xE0, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x0C, 0x07, 0x03, 0x00}; /*"D",3*/
uc8 OLED_E[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0x88, 0x08, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x00}; /*"E",4*/
uc8 OLED_F[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0x88, 0x08, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00}; /*"F",5*/
uc8 OLED_G[2][8] = {0x00, 0xF0, 0xF8, 0x08, 0x08, 0x38, 0x30, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x09, 0x0F, 0x0F, 0x00}; /*"G",6*/
uc8 OLED_H[2][8] = {0x00, 0xF8, 0xF8, 0x80, 0x80, 0xF8, 0xF8, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x0F, 0x0F, 0x00}; /*"H",7*/
uc8 OLED_I[2][8] = {0x00, 0x00, 0x08, 0xF8, 0xF8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0F, 0x0F, 0x08, 0x00, 0x00}; /*"I",8*/
uc8 OLED_J[2][8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x06, 0x0E, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"J",9*/
uc8 OLED_K[2][8] = {0x00, 0xF8, 0xF8, 0x80, 0xE0, 0x78, 0x18, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x03, 0x0F, 0x0C, 0x00}; /*"K",10*/
uc8 OLED_L[2][8] = {0x00, 0xF8, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x08, 0x08, 0x08, 0x08, 0x00}; /*"L",11*/
uc8 OLED_M[2][8] = {0x00, 0xF8, 0xF8, 0x20, 0xC0, 0x20, 0xF8, 0xF8, 0x00, 0x0F, 0x0F, 0x00, 0x01, 0x00, 0x0F, 0x0F}; /*"M",12*/
uc8 OLED_N[2][8] = {0x00, 0xF8, 0xF8, 0x60, 0xC0, 0x80, 0xF8, 0xF8, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x01, 0x0F, 0x0F}; /*"N",13*/
uc8 OLED_O[2][8] = {0x00, 0xF0, 0xF8, 0x08, 0x08, 0xF8, 0xF0, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"O",14*/
uc8 OLED_P[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00}; /*"P",15*/
uc8 OLED_Q[2][8] = {0x00, 0xF0, 0xF8, 0x08, 0x08, 0xF8, 0xF0, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x18, 0x3F, 0x27, 0x00}; /*"Q",16*/
uc8 OLED_R[2][8] = {0x00, 0xF8, 0xF8, 0x88, 0x88, 0xF8, 0x70, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x01, 0x0F, 0x0E, 0x00}; /*"R",17*/
uc8 OLED_S[2][8] = {0x00, 0x30, 0x78, 0xC8, 0x88, 0x18, 0x10, 0x00, 0x00, 0x04, 0x0C, 0x08, 0x09, 0x0F, 0x06, 0x00}; /*"S",18*/
uc8 OLED_T[2][8] = {0x00, 0x08, 0x08, 0xF8, 0xF8, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00}; /*"T",19*/
uc8 OLED_U[2][8] = {0x00, 0xF8, 0xF8, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x07, 0x0F, 0x08, 0x08, 0x0F, 0x07, 0x00}; /*"U",20*/
uc8 OLED_V[2][8] = {0x00, 0xF8, 0xF8, 0x00, 0x00, 0xF8, 0xF8, 0x00, 0x00, 0x03, 0x07, 0x0C, 0x0C, 0x07, 0x03, 0x00}; /*"V",21*/
uc8 OLED_W[2][8] = {0x00, 0xF8, 0xF8, 0x00, 0xC0, 0x00, 0xF8, 0xF8, 0x00, 0x01, 0x0F, 0x0E, 0x01, 0x0E, 0x0F, 0x01}; /*"W",22*/
uc8 OLED_X[2][8] = {0x00, 0x18, 0x38, 0xE0, 0xC0, 0x38, 0x18, 0x00, 0x00, 0x0E, 0x0F, 0x00, 0x01, 0x0F, 0x0E, 0x00}; /*"X",23*/
uc8 OLED_Y[2][8] = {0x00, 0x78, 0xF8, 0x80, 0x80, 0xF8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x00, 0x00, 0x00}; /*"Y",24*/
uc8 OLED_Z[2][8] = {0x00, 0x08, 0x08, 0x88, 0xC8, 0x78, 0x38, 0x00, 0x00, 0x0E, 0x0F, 0x09, 0x08, 0x08, 0x08, 0x00}; /*"Z",25*/

uc8 OLED_Black[2][8] = {0};
uc8 OLED_Reduce[2][8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00};  /*"-"*/
uc8 OLED_Add[2][8] = {0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x0F, 0x01, 0x01, 0x01};     /*"+",0*/
uc8 OLED_Ride[2][8] = {0x40, 0x40, 0x80, 0xF0, 0x80, 0x40, 0x40, 0x00, 0x02, 0x02, 0x01, 0x0F, 0x01, 0x02, 0x02, 0x00};    /*"*",0*/
uc8 OLED_Except[2][8] = {0x00, 0x00, 0x00, 0x00, 0xC0, 0x38, 0x04, 0x00, 0x00, 0x60, 0x18, 0x07, 0x00, 0x00, 0x00, 0x00};  /*"/",0*/
uc8 OLED_Equal[2][8] = {0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00};   /*"=",0*/
uc8 OLED_Greater[2][8] = {0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00}; /*">",0*/
uc8 OLED_Less[2][8] = {0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00};    /*">",0*/
