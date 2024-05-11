#include<stdio.h>
#include<stdbool.h>
int i;
void reverse(int n)
{
int next;
if (n <= 1)
{
scanf("%d",&next);
printf("%d",next);
}
else {
scanf("%d",&next);
reverse(n - 1);
printf("%d",next);
}
}
int main() {
i = 200;
reverse(i);
return 0;
}
