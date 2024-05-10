#include<stdio.h>
#include<stdbool.h>
int ret;
int ifwhile()
{
int a, b;
a = 0;
b = 1;
if ((a == 5))
{
for (b = 1; b <= 3; b++) {
}
b = b + 25;
return b;
}
else {
for (a = 0; a <= 4; a++) {
b = b * 2;
}
}
return b;
}
int main() {
printf("%d",ifwhile( ));
return 0;
}
