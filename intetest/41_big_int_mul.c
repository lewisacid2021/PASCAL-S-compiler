#include<stdio.h>
#include<stdbool.h>
const int len = 20;
int i, j, t, n, temp;
int len1, len2;
int mult1[20],mult2[20];
int c1[25],c2[25];
int result[40];
int main() {
len1 = len;
len2 = len;
for (i = 0; i <= 8; i++) {
mult1[i] = i + 1;
}
mult1[9] = 0;
for (i = 10; i <= 18; i++) {
mult1[i] = i - 9;
}
mult1[19] = 0;
mult2[0] = 2;
mult2[1] = 3;
mult2[2] = 4;
mult2[3] = 2;
mult2[4] = 5;
mult2[5] = 7;
mult2[6] = 9;
mult2[7] = 9;
mult2[8] = 0;
mult2[9] = 1;
mult2[10] = 9;
mult2[11] = 8;
mult2[12] = 7;
mult2[13] = 6;
mult2[14] = 4;
mult2[15] = 3;
mult2[16] = 2;
mult2[17] = 1;
mult2[18] = 2;
mult2[19] = 2;
for (i = 0; i <= len1 - 1; i++) {
c1[i] = mult1[i];
}
for (i = 0; i <= len2 - 1; i++) {
c2[i] = mult2[i];
}
n = len1 + len2 - 1;
for (i = 0; i <= n; i++) {
result[i] = 0;
}
temp = 0;
for (i = 0; i <= len2 - 1; i++) {
t = c2[len2 - 1 - i];
for (j = 0; j <= len1 - 1; j++) {
temp = result[n] + t * c1[len1 - 1 - j];
if (temp >= 10)
{
result[n] = temp;
result[n - 1] = result[n - 1] + temp / 10;
}
else {
result[n] = temp;
}
n = n - 1;
}
n = n + len1 - 1;
}
if (result[0] != 0)
{
printf("%d",result[0]);
}
for (i = 1; i <= (len1 + len2 - 1); i++) {
printf("%d",result[i]);
}
return 0;
}
