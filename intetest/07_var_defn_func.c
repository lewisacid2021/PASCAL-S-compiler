#include<stdio.h>
#include<stdbool.h>
int a;
int defn()
{
int _defn_;
_defn_ = 4;
return _defn_;
}
int main() {
a = defn();
printf("%d",a);
return 0;
}
