#include<stdio.h>
#include<stdbool.h>
int x[1],y[1];
int a, b;
int exgcd(int a,int b,int (*x),int (*y))
{
int _exgcd_;
int t, r;
if (b == 0)
{
(*x) = 1;
(*y) = 0;
_exgcd_ = a;
}
else {
r = exgcd(b, a % b, &(*x), &(*y));
t = (*x);
(*x) = (*y);
(*y) = (t - (a / b) * (*y));
_exgcd_ = r;
}
return _exgcd_;
}
int main() {
a = 7;
b = 15;
x[0] = 1;
y[0] = 1;
exgcd(a, b, &x[0], &y[0]);
x[0] = ((x[0] % b) + b) % b;
printf("%d",x[0]);
return 0;
}
