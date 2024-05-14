#include<stdio.h>
#include<stdbool.h>
const float pi = 3.14159265359;
const float two_pi = 6.28318530718;
const float epsilon = 0.000001;
float test_block[8][8],test_dct[8][8],test_idct[8][8];
int dim_x, dim_y, i, j;
float my_fabs(float x)
{
float _my_fabs_;
if (x > 0.0)
{
_my_fabs_ = x;
}
else {
_my_fabs_ = -x;
}
return _my_fabs_;
}
float p(float x)
{
float _p_;
_p_ = 3 * x - 4 * x * x * x;
return _p_;
}
float my_sin_impl(float x)
{
float _my_sin_impl_;
if (my_fabs(x) <= epsilon)
{
_my_sin_impl_ = x;
}
else {
_my_sin_impl_ = p(my_sin_impl(x / 3.0));
}
return _my_sin_impl_;
}
float my_sin(float x)
{
float _my_sin_;
int xx;
if ((x > two_pi) || (x < -two_pi))
{
xx = 1;
x = x - 1.0;
}
if (x > pi)
{
x = x - two_pi;
}
if (x < -pi)
{
x = x + two_pi;
}
_my_sin_ = my_sin_impl(x);
return _my_sin_;
}
float my_cos(float x)
{
float _my_cos_;
_my_cos_ = my_sin(x * pi / 2);
return _my_cos_;
}
void write_mat(int n,int m)
{
int i, j;
for (i = 0; i <= n - 1; i++) {
printf("%f",test_dct[i][0]);
for (j = 1; j <= m - 1; j++) {
printf("%f",test_dct[i][j]);
}
}
}
void write_mat2(int n,int m)
{
int i, j;
for (i = 0; i <= n - 1; i++) {
printf("%f",test_idct[i][0]);
for (j = 1; j <= m - 1; j++) {
printf("%f",test_idct[i][j]);
}
}
}
void dct(int n,int m)
{
int u, v, i, j;
for (u = 0; u <= n - 1; u++) {
for (v = 0; v <= m - 1; v++) {
test_dct[u][v] = 0;
for (i = 0; i <= n - 1; i++) {
for (j = 0; j <= m - 1; j++) {
test_dct[u][v] = test_dct[u][v] + test_block[i][j] * my_cos(pi / n * (i + 1.0 / 2.0) * u) * my_cos(pi / m * (i + 1.0 / 2.0) * v);
}
}
}
}
}
void idct(int n,int m)
{
int u, v, i, j;
for (u = 0; u <= n - 1; u++) {
for (v = 0; v <= m - 1; v++) {
test_idct[u][v] = 1 / 4.0 * test_dct[0][0];
for (i = 1; i <= n - 1; i++) {
test_idct[u][v] = test_idct[u][v] + 1 / 2.0 * test_dct[i][0];
}
for (j = 1; j <= m - 1; j++) {
test_idct[u][v] = test_idct[u][v] + 1 / 2.0 * test_dct[0][j];
}
for (i = 1; i <= n - 1; i++) {
for (j = 1; j <= m - 1; j++) {
test_idct[u][v] = test_idct[u][v] + test_dct[i][j] * my_cos(pi / n * (u + 1.0 / 2.0) * i) * my_cos(pi / m * (v + 1.0 / 2.0) * j);
}
}
test_idct[u][v] = test_idct[u][v] * 2.0 / n * 2.0 / m;
}
}
}
int main() {
dim_x = 0;
dim_y = 0;
scanf("%d",&dim_x);
scanf("%d",&dim_y);
for (i = 0; i <= dim_x - 1; i++) {
for (j = 0; j <= dim_y - 1; j++) {
scanf("%f",&test_block[i][j]);
}
}
dct(dim_x, dim_y);
write_mat(dim_x, dim_y);
idct(dim_x, dim_y);
write_mat2(dim_x, dim_y);
return 0;
}
