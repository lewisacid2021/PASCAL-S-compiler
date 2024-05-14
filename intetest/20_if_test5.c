#include<stdio.h>
#include<stdbool.h>
int if_if_else()
{
int _if_if_else_;
int a, b;
a = 5;
b = 10;
if ((a == 5))
{
if ((b == 10))
{
a = 25;
}
}
else {
a = a + 15;
}
_if_if_else_ = a;
return _if_if_else_;
}
int main() {
printf("%d",if_if_else());
return 0;
}
