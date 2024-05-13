#include<stdio.h>
#include<stdbool.h>
struct books{
int title[2];
};
struct stu{
struct books bo;
};
struct books b;
struct stu c;
int d;
int test(struct books a)
{
int _test_;
_test_ = a.title[0];
return _test_;
}
int main() {
b.title[0] = d;
d = c.bo.title;
return 0;
}
