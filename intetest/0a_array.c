#include<stdio.h>
#include<stdbool.h>
int test(int a[][11])
{
int _test_;
a[0][0] = a[0][1];
printf("%d",a[0][2]);
_test_ = 1;
return _test_;
}
int main() {
return 0;
}
