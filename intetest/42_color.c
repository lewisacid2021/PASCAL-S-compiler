#include<stdio.h>
#include<stdbool.h>
const int modn = 1000000007;
int dp[18][18][18][18][18][7];
int list[200];
int cns[19];
int n;
int i, j, k, l, m, h;
int ans;
int equal(int a,int b)
{
if (a == b)
{
return 1;
}
else {
return 0;
}
}
int dfs(int a,int b,int c,int d,int e,int last)
{
int anss;
if (dp[a][b][c][d][e][last] != -1)
{
return dp[a][b][c][d][e][last];
}
if (a + b + c + d + e == 0)
{
return 1;
}
else {
anss = 0;
if (a != 0)
{
anss = (anss + (a - equal(last, 2)) * dfs(a - 1, b, c, d, e, 1)) % modn;
}
if (b != 0)
{
anss = (anss + (b - equal(last, 3)) * dfs(a + 1, b - 1, c, d, e, 2)) % modn;
}
if (c != 0)
{
anss = (anss + (c - equal(last, 4)) * dfs(a, b + 1, c - 1, d, e, 3)) % modn;
}
if (d != 0)
{
anss = (anss + (d - equal(last, 5)) * dfs(a, b, c + 1, d - 1, e, 4)) % modn;
}
if (e != 0)
{
anss = (anss + e * dfs(a, b, c, d + 1, e - 1, 5)) % modn;
}
dp[a][b][c][d][e][last] = anss % modn;
return dp[a][b][c][d][e][last];
}
}
int main() {
scanf("%d",&n);
for (i = 0; i <= 17; i++) {
for (j = 0; j <= 17; j++) {
for (k = 0; k <= 17; k++) {
for (l = 0; l <= 17; l++) {
for (m = 0; m <= 17; m++) {
for (h = 0; h <= 6; h++) {
dp[i][j][k][l][m][h] = -1;
}
}
}
}
}
}
for (i = 0; i <= n - 1; i++) {
scanf("%d",&list[i]);
cns[list[i]] = cns[list[i]] + 1;
}
ans = dfs(cns[1], cns[2], cns[3], cns[4], cns[5], 0);
printf("%d",ans);
return 0;
}
