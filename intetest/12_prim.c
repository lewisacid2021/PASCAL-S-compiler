#include<stdio.h>
#include<stdbool.h>
int n, m;
int ret, i;
int u[1005],v[1005],c[1005],fa[1005];
int find(int x)
{
int _find_;
int asdf;
if (x == fa[x])
{
_find_ = x;
}
else {
asdf = find(fa[x]);
fa[x] = asdf;
_find_ = asdf;
}
return _find_;
}
int same(int x,int y)
{
int _same_;
x = find(x);
y = find(y);
if (x == y)
{
_same_ = 1;
}
else {
_same_ = 0;
}
return _same_;
}
int prim()
{
int _prim_;
int i, j, t, res;
for (i = 0; i <= m - 1; i++) {
for (j = i + 1; j <= m - 1; j++) {
if (c[i] > c[j])
{
t = u[i];
u[i] = u[j];
u[j] = t;
t = v[i];
v[i] = v[j];
v[j] = t;
t = c[i];
c[i] = c[j];
c[j] = t;
}
}
}
for (i = 1; i <= n; i++) {
fa[i] = i;
}
res = 0;
for (i = 0; i <= m - 1; i++) {
if (same(u[i], v[i]) == 0)
{
res = res + c[i];
fa[find(u[i])] = v[i];
}
}
_prim_ = res;
return _prim_;
}
int main() {
ret = 0;
scanf("%d",&n);
scanf("%d",&m);
for (i = 0; i <= m - 1; i++) {
scanf("%d",&u[i]);
scanf("%d",&v[i]);
scanf("%d",&c[i]);
}
ret = prim();
printf("%d",ret);
return 0;
}
