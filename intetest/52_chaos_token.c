#include<stdio.h>
#include<stdbool.h>
int n;
int i, tmp;
int iniArr[10],sortedArr[10];
int countingSort(int n)
{
int countArr[10];
int i, j, k, jj;
for (k = 0; k <= 9; k++) {
countArr[k] = 0;
}
for (i = 0; i <= n - 1; i++) {
countArr[iniArr[i]] = countArr[iniArr[i]] + 1;
}
for (k = 1; k <= 9; k++) {
countArr[k] = countArr[k] + countArr[k - 1];
}
for (jj = 0; jj <= n - 1; jj++) {
j = n - jj;
countArr[iniArr[j - 1]] = countArr[iniArr[j - 1]] - 1;
sortedArr[countArr[iniArr[j - 1]]] = iniArr[j - 1];
}
return 0;
}
int main() {
n = 10;
iniArr[0] = 4;
iniArr[1] = 3;
iniArr[2] = 9;
iniArr[3] = 2;
iniArr[4] = 0;
iniArr[5] = 1;
iniArr[6] = 6;
iniArr[7] = 5;
iniArr[8] = 7;
iniArr[9] = 8;
countingSort(n);
for (i = 0; i <= n - 1; i++) {
tmp = sortedArr[i];
printf("%d",tmp);
}
return 0;
}
