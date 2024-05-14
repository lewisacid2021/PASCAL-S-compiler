#include<stdio.h>
#include<stdbool.h>
int m, l, n;
int a0[3],a1[3],a2[3],b0[3],b1[3],b2[3],c0[3],c1[3],c2[3];
int i, x;
int add()
{
int _add_;
int i;
for (i = 0; i <= m - 1; i++) {
c0[i] = a0[i] + b0[i];
c1[i] = a1[i] + b1[i];
c2[i] = a2[i] + b2[i];
}
_add_ = 0;
return _add_;
}
int main() {
n = 3;
m = 3;
l = 3;
for (i = 0; i <= m - 1; i++) {
a0[i] = i;
a1[i] = i;
a2[i] = i;
b0[i] = i;
b1[i] = i;
b2[i] = i;
}
add();
for (i = 0; i <= n - 1; i++) {
x = c0[i];
printf("%d",x);
}
for (i = 0; i <= n - 1; i++) {
x = c1[i];
printf("%d",x);
}
for (i = 0; i <= n - 1; i++) {
x = c2[i];
printf("%d",x);
}
return 0;
}
