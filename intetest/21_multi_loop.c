#include<stdio.h>
#include<stdbool.h>
int a, i, j, k, ii, jj, kk, iii, jjj, kkk, iiii, jjjj, kkkk, iiiii, jjjjj, kkkkk;
int main() {
a = 0;
for (i = 0; i <= 2; i++) {
for (j = 0; j <= 3; j++) {
for (k = 0; k <= 4; k++) {
for (ii = 0; ii <= 2; ii++) {
for (jj = 0; jj <= 4; jj++) {
for (kk = 0; kk <= 3; kk++) {
for (iii = 0; iii <= 5; iii++) {
for (jjj = 0; jjj <= 4; jjj++) {
for (kkk = 0; kkk <= 4; kkk++) {
for (iiii = 0; iiii <= 2; iiii++) {
for (jjjj = 0; jjjj <= 5; jjjj++) {
for (kkkk = 0; kkkk <= 6; kkkk++) {
for (iiiii = 0; iiiii <= 4; iiiii++) {
for (jjjjj = 0; jjjjj <= 2; jjjjj++) {
for (kkkkk = 0; kkkkk <= 5; kkkkk++) {
a = (a + 3) % 999;
}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
printf("%d",a);
return 0;
}
