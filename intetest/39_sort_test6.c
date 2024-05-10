#include<stdio.h>
#include<stdbool.h>
int n, i;
int ini_arr[10],sorted_arr[10];
void countingsort()
{
int i, j, k, jj;
int count_arr[10];
for (k = 0; k <= n - 1; k++) {
count_arr[k] = 0;
}
for (i = 0; i <= n - 1; i++) {
count_arr[ini_arr[i]] = count_arr[ini_arr[i]] + 1;
}
for (k = 1; k <= n - 1; k++) {
count_arr[k] = count_arr[k] + count_arr[k - 1];
}
for (j = 0; j <= n - 1; j++) {
jj = n - j;
count_arr[ini_arr[jj - 1]] = count_arr[ini_arr[jj - 1]] - 1;
sorted_arr[count_arr[ini_arr[jj - 1]]] = ini_arr[jj - 1];
}
}
int main() {
n = 10;
ini_arr[0] = 4;
ini_arr[1] = 3;
ini_arr[2] = 9;
ini_arr[3] = 2;
ini_arr[4] = 0;
ini_arr[5] = 1;
ini_arr[6] = 6;
ini_arr[7] = 5;
ini_arr[8] = 7;
ini_arr[9] = 8;
countingsort();
for (i = 0; i <= n - 1; i++) {
printf("%d",sorted_arr[i]);
}
return 0;
}
