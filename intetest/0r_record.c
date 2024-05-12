#include<stdio.h>
#include<stdbool.h>
struct books{
int title;
};
books b;
int test(books a)
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
