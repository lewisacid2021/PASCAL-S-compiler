#include<stdio.h>
#include<stdbool.h>
int if_if_else()
{
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
return a;
}
int main() {
printf("%d",if_if_else());
return 0;
}
