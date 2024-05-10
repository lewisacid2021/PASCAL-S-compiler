#include<stdio.h>
#include<stdbool.h>
int ret;
int a[61][67];
int b[53][59];
int func(int aa,int c,int e,int f,int h,int i)
{
int index;
index = 0;
while ((index < 10)) {
printf("%d",b[aa][index]);
index = index + 1;
}
printf("%d",a[17][c]);
while ((i < 10)) {
b[6][i] = h * 128875 % 3724;
i = i + 1;
h = h + 7;
}
func = e + f;
}
int main() {
a[17][1] = 6;
a[17][3] = 7;
a[17][4] = 4;
a[17][7] = 9;
a[17][11] = 11;
b[6][1] = 1;
b[6][2] = 2;
b[6][3] = 3;
b[6][9] = 9;
ret = func(a[17][1], a[17][3], b[6][3], b[6][0], b[34][4], b[51][18]) * 3;
printf("%d",ret);
return 0;
}
