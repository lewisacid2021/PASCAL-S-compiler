#include<stdio.h>
#include<stdbool.h>
int a;
int defn()
{
return 4;
}
int main() {
{
a = defn;
printf("%d",a);
}
return 0;
}
