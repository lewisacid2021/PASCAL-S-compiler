#include<stdio.h>
#include<stdbool.h>
int i, n;
int arr[10];
int bubblesort()
{
int i, j, tmp;
for (i = 0; i <= n - 2; i++) {
for (j = 0; j <= (n - 2 - i); j++) {
if (arr[j] > arr[j + 1])
{
tmp = arr[j + 1];
arr[j + 1] = arr[j];
arr[j] = tmp;
}
}
}
return 0;
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
for (i = bubblesort(); i <= n - 1; i++) {
printf("%d",arr[i]);
}
return 0;
}
