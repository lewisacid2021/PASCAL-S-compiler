#include<stdio.h>
#include<stdbool.h>
int a[15];
int b[13];
int max(int a,int b)
{
int _max_;
if (a >= b)
{
_max_ = a;
}
else {
_max_ = b;
}
return _max_;
}
int max_sum_nonadjacent(int n)
{
int _max_sum_nonadjacent_;
int i;
int temp[16];
temp[0] = a[0];
temp[1] = max(a[0], a[1]);
for (i = 2; i <= n - 1; i++) {
temp[i] = max(temp[i - 2] + a[i], temp[i - 1]);
}
_max_sum_nonadjacent_ = temp[n - 1];
return _max_sum_nonadjacent_;
}
int longest_common_subseq(int len1,int len2)
{
int _longest_common_subseq_;
int i, j;
int p[16][16];
for (i = 0; i <= 15; i++) {
p[i][0] = 0;
}
for (j = 0; j <= 15; j++) {
p[0][j] = 0;
}
for (i = 1; i <= len1; i++) {
for (j = 1; j <= len2; j++) {
if (a[i - 1] == b[j - 1])
{
p[i][j] = p[i - 1][j - 1] + 1;
}
else {
p[i][j] = max(p[i - 1][j], p[i][j - 1]);
}
}
}
_longest_common_subseq_ = p[len1][len2];
return _longest_common_subseq_;
}
int main() {
a[0] = 8;
a[1] = 7;
a[2] = 4;
a[3] = 1;
a[4] = 2;
a[5] = 7;
a[6] = 0;
a[7] = 1;
a[8] = 9;
a[9] = 3;
a[10] = 4;
a[11] = 8;
a[12] = 3;
a[13] = 7;
a[14] = 0;
b[0] = 3;
b[1] = 9;
b[2] = 7;
b[3] = 1;
b[4] = 4;
b[5] = 2;
b[6] = 4;
b[7] = 3;
b[8] = 6;
b[9] = 8;
b[10] = 0;
b[11] = 1;
b[12] = 5;
printf("%d",max_sum_nonadjacent(15));
printf("%d",longest_common_subseq(15, 13));
return 0;
}
