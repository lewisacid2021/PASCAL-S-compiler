#include<stdio.h>
#include<stdbool.h>
int arr1[10][2][3][4][5][6][2];
int arr2[10][2][3][2][4][8][7];
int x, y, h, i, j, k, l, m, n, ret;
void loop1(int x,int y)
{
int a, b, c, d, e, f, g;
for (a = 0; a <= x - 1; a++) {
for (b = 0; b <= 1; b++) {
for (c = 0; c <= 2; c++) {
for (d = 0; d <= 3; d++) {
for (e = 0; e <= 4; e++) {
for (f = 0; f <= 5; f++) {
for (g = 0; g <= 1; g++) {
arr1[a][b][c][d][e][f][g] = a + b + c + d + e + f + g + x + y;
}
}
}
}
}
}
}
}
void loop2()
{
int a, b, c, d, e, f, g;
for (a = 0; a <= 9; a++) {
for (b = 0; b <= 1; b++) {
for (c = 0; c <= 2; c++) {
for (d = 0; d <= 1; d++) {
for (e = 0; e <= 3; e++) {
for (f = 0; f <= 7; f++) {
for (g = 0; g <= 6; g++) {
arr2[a][b][c][d][e][f][g] = a + b + d + g;
}
}
}
}
}
}
}
}
int loop3(int h,int i,int j,int k,int l,int m,int n)
{
int ans, a, b, c, d, e, f, g;
ans = 0;
for (a = 0; a <= h - 1; a++) {
for (b = 0; b <= i - 1; b++) {
for (c = 0; c <= j - 1; c++) {
for (d = 0; d <= k - 1; d++) {
for (e = 0; e <= l - 1; e++) {
for (f = 0; f <= m - 1; f++) {
for (g = 0; g <= n - 1; g++) {
ans = (ans % 817) + arr1[a][b][c][d][e][f][g] + arr2[a][b][c][d][e][f][g];
}
}
}
}
}
}
}
return ans;
}
int main() {
ret = 0;
x = 1;
y = 2;
h = 3;
i = 4;
j = 5;
k = 6;
l = 7;
m = 8;
n = 9;
loop1(x, y);
loop2();
ret = loop3(h, i, j, k, l, m, n);
printf("%d",ret);
return 0;
}
