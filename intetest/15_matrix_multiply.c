#include<stdio.h>
#include<stdbool.h>
int a[100][100],b[100][100],res[100][100];
int n1, m1, n2, m2, i, j, k;
void matrix_multiply()
{
for (i = 1; i <= m1; i++) {
for (j = 1; j <= n2; j++) {
for (k = 1; k <= n1; k++) {
res[i - 1][j - 1] = res[i - 1][j - 1] + a[i - 1][k - 1] * b[k - 1][j - 1];
}
}
}
}
int getint()
{
int _getint_;
scanf("%d",&_getint_);
return _getint_;
}
int main() {
m1 = getint();
n1 = getint();
for (i = 1; i <= m1; i++) {
for (j = 1; j <= n1; j++) {
a[i - 1][j - 1] = getint();
}
}
m2 = getint();
n2 = getint();
for (i = 1; i <= m2; i++) {
for (j = 1; j <= n2; j++) {
b[i - 1][j - 1] = getint();
}
}
matrix_multiply();
for (i = 1; i <= m1; i++) {
for (j = 1; j <= n2; j++) {
printf("%d",res[i - 1][j - 1]);
}
}
return 0;
}
