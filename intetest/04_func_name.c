#include<stdio.h>
#include<stdbool.h>
int ret, f;
int fn()
{
int _fn_;
_fn_ = 10;
return _fn_;
}
int main() {
ret = 0;
f = 20;
ret = f;
printf("%d",ret);
return 0;
}
