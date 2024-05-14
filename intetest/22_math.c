#include<stdio.h>
#include<stdbool.h>
const float e = 2.1718281828459045;
const char *split = "--";
float x, y;
int num, i;
float my_fabs(float x)
{
float _my_fabs_;
if (x > 0)
{
_my_fabs_ = x;
}
else {
_my_fabs_ = -x;
}
return _my_fabs_;
}
float my_pow(float a,int n)
{
float _my_pow_;
int i;
float res;
if (n < 0)
{
_my_pow_ = 1 / (my_pow(a, -n));
}
else {
res = 1.0;
for (i = 0; i <= n - 1; i++) {
res = res * a;
}
_my_pow_ = res;
}
return _my_pow_;
}
float my_sqrt(float x)
{
float _my_sqrt_;
float t;
int c;
if (x > 100)
{
_my_sqrt_ = 10.0 * my_sqrt(x / 100);
}
else {
t = x / 8 + 0.5 + 2 * x / (4 + x);
for (c = 0; c <= 9; c++) {
t = (t + x / t) / 2;
}
_my_sqrt_ = t;
}
return _my_sqrt_;
}
float f1(float x)
{
float _f1_;
_f1_ = 1 / x;
return _f1_;
}
float f2(float x)
{
float _f2_;
_f2_ = 1 / my_sqrt(1 - x * x);
return _f2_;
}
float simpson(float a,float b,int flag)
{
float _simpson_;
float c;
c = a + (b - a) / 2;
_simpson_ = 0;
if (flag == 1)
{
_simpson_ = (f1(a) + 4 * f1(c) + f1(b)) * (b - a) / 6;
}
else {
_simpson_ = (f2(a) + 4 * f2(c) + f2(b)) * (b - a) / 6;
}
return _simpson_;
}
float asr5(float a,float b,float eps,float aa,int flag)
{
float _asr5_;
float c, l, r;
c = a + (b - a) / 2;
l = simpson(a, c, flag);
r = simpson(c, b, flag);
if (my_fabs(l + r - aa) <= (15 * eps))
{
_asr5_ = l + r + (l + r - aa) / 15.0;
}
else {
_asr5_ = asr5(a, c, eps / 2, l, flag) + asr5(c, b, eps / 2, r, flag);
}
return _asr5_;
}
float asr4(float a,float b,float eps,int flag)
{
float _asr4_;
_asr4_ = asr5(a, b, eps, simpson(a, b, flag), flag);
return _asr4_;
}
float eee(float x)
{
float _eee_;
float ee;
if (x > 0.001)
{
ee = eee(x / 2);
_eee_ = ee * ee;
}
else {
_eee_ = 1 + x + x * x / 2 + my_pow(x, 3) / 6 + my_pow(x, 4) / 24 + my_pow(x, 5) / 120;
}
return _eee_;
}
float my_exp(float x)
{
float _my_exp_;
float e1, e2;
int n;
if (x < 0)
{
_my_exp_ = 1 / my_exp(-x);
}
else {
n = 1;
x = x - 1.0;
e1 = my_pow(e, n);
e2 = eee(x);
_my_exp_ = e1 * e2;
}
return _my_exp_;
}
float my_ln(float x)
{
float _my_ln_;
_my_ln_ = asr4(1, x, 0.00000001, 1);
return _my_ln_;
}
float my_log(float a,float n)
{
float _my_log_;
_my_log_ = my_ln(n) / my_ln(a);
return _my_log_;
}
float my_powf(float a,float x)
{
float _my_powf_;
_my_powf_ = my_exp(x * my_ln(a));
return _my_powf_;
}
void putfloat(float f)
{
printf("%f",f);
}
float getfloat()
{
float _getfloat_;
scanf("%f",&_getfloat_);
return _getfloat_;
}
int main() {
num = 2;
for (i = 0; i <= num - 1; i++) {
x = getfloat();
y = getfloat();
putfloat(my_fabs(x));
putfloat(my_pow(x, 2));
putfloat(my_sqrt(x));
putfloat(my_exp(x));
if (x > 0.0)
{
putfloat(my_ln(x));
}
else {
printf("%s",split);
}
if ((x > 0.0) && (y > 0.0))
{
putfloat(my_log(x, y));
}
else {
printf("%s",split);
}
if (x > 0.0)
{
putfloat(my_powf(x, y));
}
else {
printf("%s",split);
}
}
scanf("%d",&num);
return 0;
}
