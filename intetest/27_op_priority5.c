#include<stdio.h>
#include<stdbool.h>
int a, b, c, d, e;
bool flag;
int main() {
a = 1;
b = 0;
c = 1;
d = 2;
e = 4;
flag = false;
if (((a * b / c == e + d) && (a * (a + b) + c <= d + e) || (a - (b * c) == d - a / c)))
{
flag = true;
}
if ((flag))
{
printf("%d",1);
}
return 0;
}
