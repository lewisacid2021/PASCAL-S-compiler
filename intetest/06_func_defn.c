#include<stdio.h>
#include<stdbool.h>
int a;
int b;
int func(int p)
{
p = p - 1;
return p;
}
int main() {
{
a = 10;
b = func(a);
printf("%d",b);
}
return 0;
}
