#include<stdio.h>
#include<stdbool.h>
int k;
int i, j;
float ret0, ret1;
float arr[40][3];
int arr2[24][3];
float params_f40(float x0,float x1,float x2,float x3,float x4,float x5,float x6,float x7,float x8,float x9,float x10,float x11,float x12,float x13,float x14,float x15,float x16,float x17,float x18,float x19,float x20,float x21,float x22,float x23,float x24,float x25,float x26,float x27,float x28,float x29,float x30,float x31,float x32,float x33,float x34,float x35,float x36,float x37,float x38,float x39)
{
float _params_f40_;
int i;
float arr[10];
if (x39 != 0)
{
arr[0] = x0 + x1 + x2 + x3;
arr[1] = x4 + x5 + x6 + x7;
arr[2] = x8 + x9 + x10 + x11;
arr[3] = x12 + x13 + x14 + x15;
arr[4] = x16 + x17 + x18 + x19;
arr[5] = x20 + x21 + x22 + x23;
arr[6] = x24 + x25 + x26 + x27;
arr[7] = x28 + x29 + x30 + x31;
arr[8] = x32 + x33 + x34 + x35;
arr[9] = x36 + x37 + x38 + x39;
for (i = 0; i <= 9; i++) {
printf("%f",arr[i]);
}
_params_f40_ = arr[k];
}
else {
_params_f40_ = params_f40(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x0 + x1 + x2);
}
return _params_f40_;
}
float params_f40_i24(int i23,int i2,int i6,float x4,int i1,int i4,int i5,float x8,float x15,float x7,int i22,float x3,float x28,int i0,float x37,int i19,float x30,float x12,float x1,float x11,float x38,float x6,int i7,float x32,int i10,int i13,float x20,float x33,float x23,float x9,float x25,int i8,float x39,int i17,float x21,float x16,float x5,float x34,int i18,int i9,float x14,float x10,float x0,int i12,float x31,int i11,int i16,float x27,float x24,float x13,float x29,int i3,int i21,int i20,float x18,float x19,float x22,float x26,float x36,float x17,int i15,float x2,int i14,float x35)
{
float _params_f40_i24_;
int i;
float arr[10];
float arr2[8];
if (i23 != 0)
{
arr[0] = x0 + x1 + x2 + x3;
arr[1] = x4 + x5 + x6 + x7;
arr[2] = x8 + x9 + x10 + x11;
arr[3] = x12 + x13 + x14 + x15;
arr[4] = x16 + x17 + x18 + x19;
arr[5] = x20 + x21 + x22 + x23;
arr[6] = x24 + x25 + x26 + x27;
arr[7] = x28 + x29 + x30 + x31;
arr[8] = x32 + x33 + x34 + x35;
arr[9] = x36 + x37 + x38 + x39;
arr2[0] = (i0 + i1 + i2) * 1.0;
arr2[1] = (i3 + i4 + i5) * 1.0;
arr2[2] = (i6 + i7 + i8) * 1.0;
arr2[3] = (i9 + i10 + i11) * 1.0;
arr2[4] = (i12 + i13 + i14) * 1.0;
arr2[5] = (i15 + i16 + i17) * 1.0;
arr2[6] = (i18 + i19 + i20) * 1.0;
arr2[7] = (i21 + i22 + i23) * 1.0;
for (i = 0; i <= 9; i++) {
printf("%f",arr[i]);
}
for (i = 0; i <= 7; i++) {
printf("%f",arr2[i]);
}
for (i = 0; i <= 7; i++) {
arr2[i] = arr2[i] - arr[i];
}
_params_f40_i24_ = arr2[k];
}
else {
_params_f40_i24_ = params_f40_i24(i1, i2, i6, x4, i1, i4, i5, x8, x15, x7, i22, x3, x28, i0, x37, i19, x30, x12, x1, x11, x38, x6, i7, x32, i10, i13, x20, x33, x23, x9, x25, i8, x39, i17, x21, x16, x5, x34, i18, i9, x14, x10, x0, i12, x31, i11, i16, x27, x24, x13, x29, i3, i21, i20, x18, x19, x22, x26, x36, x17, i15, x2, i14, x35);
}
return _params_f40_i24_;
}
int main() {
k = 0;
for (i = 0; i <= 23; i++) {
for (j = 0; j <= 2; j++) {
arr2[i][j] = i * 2 - j * 3;
}
}
for (i = 0; i <= 39; i++) {
for (j = 0; j <= 2; j++) {
arr[i][j] = i * 2.2 - j * 3.3;
}
}
ret0 = params_f40(arr[0][k], arr[1][k], arr[2][k], arr[3][k], arr[4][k], arr[5][k], arr[6][k], arr[7][k], arr[8][k], arr[9][k], arr[10][k], arr[11][k], arr[12][k], arr[13][k], arr[14][k], arr[15][k], arr[16][k], arr[17][k], arr[18][k], arr[19][k], arr[20][k], arr[21][k], arr[22][k], arr[23][k], arr[24][k], arr[25][k], arr[26][k], arr[27][k], arr[28][k], arr[29][k], arr[30][k], arr[31][k], arr[32][k], arr[33][k], arr[34][k], arr[35][k], arr[36][k], arr[37][k], arr[38][k], arr[39][k]);
ret1 = params_f40_i24(arr2[23][k], arr2[2][k], arr2[6][k], arr[4][k], arr2[1][k], arr2[4][k], arr2[5][k], arr[8][k], arr[15][k], arr[7][k], arr2[22][k], arr[3][k], arr[28][k], arr2[0][k], arr[37][k], arr2[19][k], arr[30][k], arr[12][k], arr[1][k], arr[11][k], arr[38][k], arr[6][k], arr2[7][k], arr[32][k], arr2[10][k], arr2[13][k], arr[20][k], arr[33][k], arr[23][k], arr[9][k], arr[25][k], arr2[8][k], arr[39][k], arr2[17][k], arr[21][k], arr[16][k], arr[5][k], arr[34][k], arr2[18][k], arr2[9][k], arr[14][k], arr[10][k], arr[0][k], arr2[12][k], arr[31][k], arr2[11][k], arr2[16][k], arr[27][k], arr[24][k], arr[13][k], arr[29][k], arr2[3][k], arr2[21][k], arr2[20][k], arr[18][k], arr[19][k], arr[22][k], arr[26][k], arr[36][k], arr[17][k], arr2[15][k], arr[2][k], arr2[14][k], arr[35][k]);
printf("%f",ret0);
printf("%f",ret1);
return 0;
}
