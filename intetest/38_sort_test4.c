#include<stdio.h>
#include<stdbool.h>
int n, i;
int arr[10];
void selectsort()
{
int i, j, min, tmp;
for (i = 0; i <= n - 2; i++) {
min = i;
for (j = i + 1; j <= n - 1; j++) {
if (arr[min] > arr[j])
{
min = j;
}
}
if (min != i)
{
tmp = arr[min];
arr[min] = arr[i];
arr[i] = tmp;
}
}
}
int main() {
n = 10;
arr[0] = 4;
arr[1] = 3;
arr[2] = 9;
arr[3] = 2;
arr[4] = 0;
arr[5] = 1;
arr[6] = 6;
arr[7] = 5;
arr[8] = 7;
arr[9] = 8;
selectsort();
for (i = 0; i <= n - 1; i++) {
printf("%d",arr[i]);
}
return 0;
}
