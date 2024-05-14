#include<stdio.h>
#include<stdbool.h>
int a, sum, i;
int func()
{
int _func_;
int b, a;
b = 7;
a = 1;
if ((a == b))
{
a = a + 1;
_func_ = 1;
}
else {
_func_ = 0;
}
return _func_;
}
int main() {
a = 7;
sum = 0;
for (i = 0; i <= 99; i++) {
if ((func() == 1))
{
sum = sum + 1;
}
}
printf("%d",a);
printf("%d",sum);
return 0;
}
