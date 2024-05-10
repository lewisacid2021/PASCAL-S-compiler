#include<stdio.h>
#include<stdbool.h>
int a[4096];
int b[4][1024];
int c[1024][4];
int f1()
{
a[5] = 4000;
a[4000] = 3;
a[4095] = 7;
c[0][a[4095]] = a[2216] + 9;
return a[a[5]];
}
int main() {
b[1][0] = 1;
b[2][0] = 2;
b[2][1] = 3;
b[3][0] = 4;
b[3][1] = 5;
b[3][2] = 6;
c[0][0] = 1;
c[0][1] = 2;
c[1][0] = 3;
c[1][1] = 4;
printf("%d",f1());
printf("%d",c[2][0]);
return 0;
}
