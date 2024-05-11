#include<stdio.h>
#include<stdbool.h>
int a;
int b;
int func(int p)
{
int _func_;
p = p - 1;
_func_ = p;
return _func_;
}
int main() {
a = 10;
b = func(a);
printf("%d",b);
return 0;
}
