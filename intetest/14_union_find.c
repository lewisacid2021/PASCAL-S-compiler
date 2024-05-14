#include<stdio.h>
#include<stdbool.h>
int parent[1005];
int n, m, i, p, q, clusters;
int getint()
{
int _getint_;
scanf("%d",&_getint_);
return _getint_;
}
int find(int root)
{
int _find_;
if (parent[root] == root)
{
_find_ = root;
}
else {
parent[root] = find(parent[root]);
_find_ = parent[root];
}
return _find_;
}
void merge(int p,int q)
{
int root_p, root_q;
root_p = find(p);
root_q = find(q);
if (root_p != root_q)
{
parent[root_q] = root_p;
}
}
int main() {
n = getint();
m = getint();
for (i = 0; i <= n - 1; i++) {
parent[i] = i;
}
for (i = 0; i <= m - 1; i++) {
p = getint();
q = getint();
merge(p, q);
}
clusters = 0;
for (i = 0; i <= n - 1; i++) {
if (parent[i] == i)
{
clusters = clusters + 1;
}
}
printf("%d",clusters);
scanf("%d",&clusters);
return 0;
}
