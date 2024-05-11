#include<stdio.h>
#include<stdbool.h>
int a, b, c, d, e;
bool flag;
int main() {
scanf("%d",&a);
scanf("%d",&b);
scanf("%d",&c);
scanf("%d",&d);
scanf("%d",&e);
flag = false;
if (((a - b * c != d - a / c) or (a * b / c == e + d) or (a + b + c == d + e)))
{
flag = true;
}
if (flag)
{
printf("%d",1);
}
return 0;
}
