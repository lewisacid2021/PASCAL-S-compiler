#include<stdio.h>
#include<stdbool.h>
const int inf = 32767;
int e[16][16];
int dis[16],book[16];
int m, n;
int u, v, i, j;
void dijkstra()
{
int i, min_num, min_index, k, j;
for (i = 1; i <= n; i++) {
dis[i] = e[1][i];
book[i] = 0;
}
book[1] = 1;
for (i = 1; i <= n - 1; i++) {
min_num = inf;
min_index = 0;
for (k = 1; k <= n; k++) {
if ((min_num > dis[k]) && (book[k] == 0))
{
min_num = dis[k];
min_index = k;
}
}
book[min_index] = 1;
for (j = 1; j <= n; j++) {
if (e[min_index][j] < inf)
{
if (dis[j] > dis[min_index] + e[min_index][j])
{
dis[j] = dis[min_index] + e[min_index][j];
}
}
}
}
}
int main() {
scanf("%d",&n);
scanf("%d",&m);
for (i = 1; i <= n; i++) {
for (j = 1; j <= n; j++) {
if (i == j)
{
e[i][j] = 0;
}
else {
e[i][j] = inf;
}
}
}
for (i = 1; i <= m; i++) {
scanf("%d",&u);
scanf("%d",&v);
scanf("%d",&e[u][v]);
}
dijkstra();
for (i = 1; i <= n; i++) {
printf("%d",dis[i]);
}
scanf("%d",&e[0][0]);
return 0;
}
