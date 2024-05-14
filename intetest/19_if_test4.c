#include<stdio.h>
#include<stdbool.h>
int if_ifelse_()
{
int _if_ifelse__;
int a, b;
a = 5;
b = 10;
if ((a == 5))
{
if ((b == 10))
{
a = 25;
}
else {
a = a + 15;
}
}
_if_ifelse__ = a;
return _if_ifelse__;
}
int main() {
printf("%d",if_ifelse_());
return 0;
}
