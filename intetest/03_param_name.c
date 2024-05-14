#include<stdio.h>
#include<stdbool.h>
int ret;
int fn(int f)
{
int _fn_;
_fn_ = f * 2;
return _fn_;
}
int main() {
ret = 0;
ret = fn(10);
printf("%d",ret);
return 0;
}
