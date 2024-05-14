#include<stdio.h>
#include<stdbool.h>
const int n = 100;
const int m = 20;
int arr[100][20];
int i, j, sum;
int main() {
for (i = 0; i <= m - 1; i++) {
for (j = 0; j <= n - 1; j++) {
arr[i][j] = j;
}
}
sum = arr[0][arr[1][arr[2][arr[3][arr[4][arr[5][arr[6][arr[7][arr[8][arr[9][arr[10][arr[11][arr[12][arr[13][arr[14][arr[15][arr[16][arr[17][arr[18][arr[19][19]]]]]]]]]]]]]]]]]]]] + arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[arr[19][18]][17]][16]][15]][14]][13]][12]][11]][10]][9]][8]][7]][6]][5]][4]][3]][2]][1]][0]][19];
printf("%d",sum);
return 0;
}
