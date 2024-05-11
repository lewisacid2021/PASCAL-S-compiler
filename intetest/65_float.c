#include<stdio.h>
#include<stdbool.h>
const double radius = 5.5000000000000000;
const double pi = 3.1415956535897931;
const double eps = 0.0000010000000000;
const double eval1 = 95.0331879999999956;
const int conv1 = 233;
const int max = 1000000000;
const double two = 2.8999999999999999;
const int three = 3;
const int five = 5;
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
return (pi * radius * radius + (radius * radius) * pi) / 2;
}
int float_eq(double a,double b)
{
if (float_abs(a - b) < eps)
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
assert(float_eq(circle_area(5), circle_area(five)));
if (1.5000000000000000 != 0.0000000000000000)
{
ok();
}
if ((~(3.2999999999999998 == 0.0000000000000000)))
{
ok();
}
if ((0.0000000000000000 != 0.0000000000000000) && (3 != 0.0000000000000000))
{
error();
}
if ((0 != 0.0000000000000000) || (0.3000000000000000 != 0.0000000000000000))
{
ok();
}
p = 0;
arr[0] = 1.0000000000000000;
arr[1] = 2.0000000000000000;
input = 0.5200000000000000;
area = pi * input * input;
area_trunc = circle_area(0);
arr[p] = arr[p] + input;
printf("%.6lf",area);
printf("%.6lf",area_trunc);
printf("%.6lf",arr[0]);
return 0;
}
