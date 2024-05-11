#include<stdio.h>
#include<stdbool.h>
int i, j, sum, t;
int arr[100];
int main() {
t = 5;
i = 0;
sum = 0;
for (j = 0; j <= t - 1; j++) {
i = i + 1;
arr[j] = i;
}
for (j = 0; j <= i - 1; j++) {
sum = sum + arr[j];
}
printf("%d",sum % 79);
return 0;
}
