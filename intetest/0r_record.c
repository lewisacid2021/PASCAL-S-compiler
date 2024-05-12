#include<stdio.h>
#include<stdbool.h>
struct books{
int title;
};
struct books b;
int test(struct books a)
{
int _test_;
_test_ = a.title;
return _test_;
}
int main() {
b.title = 1;
printf("%d",test(b));
return 0;
}
