#include<stdio.h>
#include<stdbool.h>
const double RADIUS = 5.500000;
const double PI = 3.141596;
const double EPS = 0.000001;
const double EVAL1 = 95.033188;
const int CONV1 = 233;
const int MAX = 1000000000;
const double TWO = 2.900000;
const int THREE = 3;
const int FIVE = 5;
const char e = 'e';
const char o = 'o';
int p;
double arr[10];
double input, area, area_trunc;
double float_abs(double x)
{
if (x < 0)
{
return -x;
}
else {
return x;
}
}
double circle_area(int radius)
{
return (PI * radius * radius + (radius * radius) * PI) / 2;
}
int float_eq(double a,double b)
{
if (float_abs(a - b) < EPS)
{
return 1;
}
else {
return 0;
}
}
void error()
{
printf("%c",e);
}
void ok()
{
printf("%c",o);
}
void assert(int cond)
{
if (cond == 0)
{
error();
}
else {
ok();
}
}
int main() {
assert(float_eq(circle_area(5), circle_area(FIVE)));
if (1.500000 != 0.000000)
{
ok();
}
if ((~(3.300000 == 0.000000)))
{
ok();
}
if ((0.000000 != 0.000000) && (3 != 0.000000))
{
error();
}
if ((0 != 0.000000) || (0.300000 != 0.000000))
{
ok();
}
p = 0;
arr[0] = 1.000000;
arr[1] = 2.000000;
input = 0.520000;
area = PI * input * input;
area_trunc = circle_area(0);
arr[p] = arr[p] + input;
printf("%lf",area);
printf("%lf",area_trunc);
printf("%lf",arr[0]);
return 0;
}
