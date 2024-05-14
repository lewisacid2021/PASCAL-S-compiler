#include<stdio.h>
#include<stdbool.h>
int arr[6];
int sum, i;
int main() {
arr[0] = 1;
arr[1] = 2;
arr[2] = 33;
arr[3] = 4;
arr[4] = 5;
arr[5] = 6;
sum = 0;
for (i = 0; i <= 5; i++) {
sum = sum + arr[i];
}
printf("%d",sum);
return 0;
}
