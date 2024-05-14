#include<stdio.h>
#include<stdbool.h>
int n, m, l, i, x;
int a0[3];
int a1[3];
int a2[3];
int b0[3];
int b1[3];
int b2[3];
int c0[6];
int c1[3];
int c2[3];
int sub()
{
int _sub_;
for (i = 0; i <= 2; i++) {
c0[i] = a0[i] - b0[i];
c1[i] = a1[i] - b1[i];
c2[i] = a2[i] - b2[i];
}
_sub_ = 0;
return _sub_;
}
int main() {
n = 3;
m = 3;
l = 3;
for (i = 0; i <= 2; i++) {
a0[i] = i;
a1[i] = i;
a2[i] = i;
b0[i] = i;
b1[i] = i;
b2[i] = i;
}
sub();
for (i = 0; i <= 2; i++) {
x = c0[i];
printf("%d",x);
}
for (i = 0; i <= 2; i++) {
x = c1[i];
printf("%d",x);
}
for (i = 0; i <= 2; i++) {
x = c2[i];
printf("%d",x);
}
return 0;
}
