#include<stdio.h>
#include<stdbool.h>
int ret;
int a[5][3];
int b[5][3];
int c[5][3];
int d[5][3];
int e[5][3];
int f[5];
int g[5][3];
int h[3];
int i[2][3][4];
int main() {
ret = 0;
a[1 - 1][1 - 1] = 0;
a[1 - 1][2 - 1] = 0;
a[1 - 1][3 - 1] = 0;
a[2 - 1][1 - 1] = 0;
a[2 - 1][2 - 1] = 0;
a[2 - 1][3 - 1] = 0;
a[3 - 1][1 - 1] = 0;
a[3 - 1][2 - 1] = 0;
a[3 - 1][3 - 1] = 0;
a[4 - 1][1 - 1] = 0;
a[4 - 1][2 - 1] = 0;
a[4 - 1][3 - 1] = 0;
a[5 - 1][1 - 1] = 0;
a[5 - 1][2 - 1] = 0;
a[5 - 1][3 - 1] = 0;
b[1 - 1][1 - 1] = 0;
b[1 - 1][2 - 1] = 0;
b[1 - 1][3 - 1] = 0;
b[2 - 1][1 - 1] = 0;
b[2 - 1][2 - 1] = 0;
b[2 - 1][3 - 1] = 0;
b[3 - 1][1 - 1] = 0;
b[3 - 1][2 - 1] = 0;
b[3 - 1][3 - 1] = 0;
b[4 - 1][1 - 1] = 0;
b[4 - 1][2 - 1] = 0;
b[4 - 1][3 - 1] = 0;
b[5 - 1][1 - 1] = 0;
b[5 - 1][2 - 1] = 0;
b[5 - 1][3 - 1] = 0;
c[1 - 1][1 - 1] = 1;
c[1 - 1][2 - 1] = 2;
c[1 - 1][3 - 1] = 3;
c[2 - 1][1 - 1] = 4;
c[2 - 1][2 - 1] = 5;
c[2 - 1][3 - 1] = 6;
c[3 - 1][1 - 1] = 7;
c[3 - 1][2 - 1] = 8;
c[3 - 1][3 - 1] = 9;
c[4 - 1][1 - 1] = 10;
c[4 - 1][2 - 1] = 11;
c[4 - 1][3 - 1] = 12;
c[5 - 1][1 - 1] = 13;
c[5 - 1][2 - 1] = 14;
c[5 - 1][3 - 1] = 15;
d[1 - 1][1 - 1] = 1;
d[1 - 1][2 - 1] = 2;
d[1 - 1][3 - 1] = 3;
d[2 - 1][1 - 1] = 4;
d[2 - 1][2 - 1] = 5;
d[2 - 1][3 - 1] = 6;
d[3 - 1][1 - 1] = 7;
d[3 - 1][2 - 1] = 8;
d[3 - 1][3 - 1] = 9;
d[4 - 1][1 - 1] = 10;
d[4 - 1][2 - 1] = 11;
d[4 - 1][3 - 1] = 12;
d[5 - 1][1 - 1] = 13;
d[5 - 1][2 - 1] = 14;
d[5 - 1][3 - 1] = 15;
e[1 - 1][1 - 1] = 1;
e[1 - 1][2 - 1] = 2;
e[1 - 1][3 - 1] = 3;
e[2 - 1][1 - 1] = 4;
e[2 - 1][2 - 1] = 5;
e[2 - 1][3 - 1] = 6;
e[3 - 1][1 - 1] = 7;
e[3 - 1][2 - 1] = 8;
e[3 - 1][3 - 1] = 9;
e[4 - 1][1 - 1] = 10;
e[4 - 1][2 - 1] = 11;
e[4 - 1][3 - 1] = 12;
e[5 - 1][1 - 1] = 13;
e[5 - 1][2 - 1] = 14;
e[5 - 1][3 - 1] = 15;
f[1 - 1] = 0;
f[2 - 1] = 0;
f[3 - 1] = 0;
f[4 - 1] = 0;
f[5 - 1] = 0;
g[1 - 1][1 - 1] = 1;
g[1 - 1][2 - 1] = 2;
g[1 - 1][3 - 1] = 3;
g[2 - 1][1 - 1] = 4;
g[2 - 1][2 - 1] = 0;
g[2 - 1][3 - 1] = 0;
g[3 - 1][1 - 1] = 7;
g[3 - 1][2 - 1] = 0;
g[3 - 1][3 - 1] = 0;
g[4 - 1][1 - 1] = 10;
g[4 - 1][2 - 1] = 11;
g[4 - 1][3 - 1] = 12;
g[5 - 1][1 - 1] = 0;
g[5 - 1][2 - 1] = 0;
g[5 - 1][3 - 1] = 0;
h[1 - 1] = 0;
h[2 - 1] = 0;
h[3 - 1] = 0;
i[1 - 1][1 - 1][1 - 1] = 1;
i[1 - 1][1 - 1][2 - 1] = 2;
i[1 - 1][1 - 1][3 - 1] = 3;
i[1 - 1][1 - 1][4 - 1] = 4;
i[1 - 1][2 - 1][1 - 1] = 5;
i[1 - 1][2 - 1][2 - 1] = 0;
i[1 - 1][2 - 1][3 - 1] = 0;
i[1 - 1][2 - 1][4 - 1] = 0;
i[2 - 1][1 - 1][1 - 1] = 0;
i[2 - 1][1 - 1][2 - 1] = 0;
i[2 - 1][1 - 1][3 - 1] = 0;
i[2 - 1][1 - 1][4 - 1] = 0;
i[2 - 1][2 - 1][1 - 1] = 0;
i[2 - 1][2 - 1][2 - 1] = 0;
i[2 - 1][2 - 1][3 - 1] = 0;
i[2 - 1][2 - 1][4 - 1] = 0;
i[2 - 1][3 - 1][1 - 1] = 0;
i[2 - 1][3 - 1][2 - 1] = 0;
i[2 - 1][3 - 1][3 - 1] = 0;
i[2 - 1][3 - 1][4 - 1] = 0;
ret = 4;
printf("%d",ret);
return 0;
}
