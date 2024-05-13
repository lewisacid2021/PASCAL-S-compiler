#include<stdio.h>
#include<stdbool.h>
const char split = ',';
int n, t, i;
void move(int x,int y)
{
printf("%c",x, y, split);
}
void hanoi(int n,int one,int two,int three)
{
if (n == 1)
{
move(one, three);
}
else {
hanoi(n - 1, one, three, two);
move(one, three);
hanoi(n - 1, two, one, three);
}
}
int main() {
scanf("%d",&n);
for (i = 1; i <= n; i++) {
scanf("%d",&t);
hanoi(t, 1, 2, 3);
}
return 0;
}
