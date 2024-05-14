#include<stdio.h>
#include<stdbool.h>
int ret, a, b, c, d, e, f;
int main() {
ret = 0;
a = 1;
b = 2;
c = 3;
d = 4;
e = 5;
f = 6;
if ((a * b + c < 6) && (d != 0))
{
if ((e != 0) || (~(a + 0 != 0)))
{
if ((c == 2) && (d + e > 2))
{
ret = 3;
}
else {
if ((f % c != 0) && (e != 0))
{
ret = 4;
}
else {
if ((d / b + a >= 2))
{
if ((e - f >= 0) || (d > 4))
{
ret = 6;
}
else {
if ((c != f))
{
if ((b + e * d > 10))
{
if ((f == 0))
{
ret = 9;
}
else {
ret = 10;
}
}
else {
ret = 8;
}
}
else {
ret = 7;
}
}
}
else {
ret = 5;
}
}
}
}
else {
ret = 2;
}
}
else {
ret = 1;
}
printf("%d",ret);
return 0;
}
