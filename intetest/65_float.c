#include<stdio.h>
#include<stdbool.h>
const double radius = 5.500000000000000;
const double pi = 3.141595653589793;
const double eps = 0.000001000000000;
const double eval1 = 95.033187999999996;
const int conv1 = 233;
const int max = 1000000000;
const double two = 2.900000000000000;
const int three = 3;
const int five = 5;
const char e = 'e';
const char o = 'o';
int p;
double arr[10];
double input, area, area_trunc;
double float_abs(double x)
{
double _float_abs_;
if (x < 0)
{
_float_abs_ = -x;
}
else {
_float_abs_ = x;
}
return _float_abs_;
}
double circle_area(int radius)
{
double _circle_area_;
_circle_area_ = (pi * radius * radius + (radius * radius) * pi) / 2;
return _circle_area_;
}
int float_eq(double a,double b)
{
int _float_eq_;
if (float_abs(a - b) < eps)
{
_float_eq_ = 1;
}
else {
_float_eq_ = 0;
}
return _float_eq_;
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
if (1.500000000000000 != 0.000000000000000)
{
ok();
}
if ((~(3.300000000000000 == 0.000000000000000)))
{
ok();
}
if ((0.000000000000000 != 0.000000000000000) && (3 != 0.000000000000000))
{
error();
}
if ((0 != 0.000000000000000) || (0.300000000000000 != 0.000000000000000))
{
ok();
}
p = 0;
arr[0] = 1.000000000000000;
arr[1] = 2.000000000000000;
input = 0.520000000000000;
area = pi * input * input;
area_trunc = circle_area(0);
arr[p] = arr[p] + input;
printf("%.6lf",area);
printf("%.6lf",area_trunc);
printf("%.6lf",arr[0]);
return 0;
}
