#include<stdio.h>
#include<stdbool.h>
int store[30];
int n, m;
int graph[30][30];
int edges[600][2];
int i, ret;
int is_clique(int num)
{
int _is_clique_;
int i, j;
_is_clique_ = 1;
for (i = 1; i <= num - 1; i++) {
for (j = i + 1; j <= num - 1; j++) {
if (graph[store[i]][store[j]] == 0)
{
_is_clique_ = 0;
}
}
}
return _is_clique_;
}
int maxcliques(int i,int k)
{
int _maxcliques_;
int max_, j, tmp;
max_ = 0;
for (j = 1; j <= n; j++) {
store[k] = j;
if (is_clique(k + 1) != 0)
{
if (k > max_)
{
max_ = k;
}
tmp = maxcliques(j, k + 1);
if (tmp > max_)
{
max_ = tmp;
}
}
}
_maxcliques_ = max_;
return _maxcliques_;
}
int main() {
scanf("%d",&n);
scanf("%d",&m);
for (i = 0; i <= m - 1; i++) {
scanf("%d",&edges[i][0]);
scanf("%d",&edges[i][1]);
}
for (i = 0; i <= m - 1; i++) {
graph[edges[i][0]][edges[i][1]] = 1;
graph[edges[i][1]][edges[i][0]] = 1;
}
ret = maxcliques(0, 1);
printf("%d",ret);
return 0;
}
