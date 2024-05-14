#include<stdio.h>
#include<stdbool.h>
const char split = ',';
int a, b, k, i;
int inc_a()
{
int _inc_a_;
int temp_b;
temp_b = a;
temp_b = temp_b + 1;
a = temp_b;
_inc_a_ = a;
return _inc_a_;
}
int main() {
a = -1;
b = 1;
k = 5;
for (i = 0; i <= k; i++) {
if ((inc_a() != 0) && (inc_a() != 0) && (inc_a() != 0))
{
printf("%d%d%c",a, b, split);
}
if ((inc_a() < 14) || ((inc_a() != 0) && ((inc_a() - inc_a() + 1) != 0)))
{
printf("%d%c",a, split);
b = b * 2;
}
else {
inc_a();
}
}
printf("%d%d%c",a, b, split);
printf("%d",a);
return 0;
}
