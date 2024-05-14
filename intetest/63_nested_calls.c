#include<stdio.h>
#include<stdbool.h>
int i, i1, i2, i3, i4, a;
int arr[10];
int func1(int x,int y,int z)
{
int _func1_;
if (z == 0)
{
_func1_ = x * y;
}
else {
_func1_ = func1(x, y - z, 0);
}
return _func1_;
}
int func2(int x,int y)
{
int _func2_;
if (y != 0)
{
_func2_ = func2(x % y, 0);
}
else {
_func2_ = x;
}
return _func2_;
}
int func3(int x,int y)
{
int _func3_;
if (y == 0)
{
_func3_ = x + 1;
}
else {
_func3_ = func3(x + y, 0);
}
return _func3_;
}
int func4(int x,int y,int z)
{
int _func4_;
if (x != 0)
{
_func4_ = y;
}
else {
_func4_ = z;
}
return _func4_;
}
int func5(int x)
{
int _func5_;
_func5_ = -x;
return _func5_;
}
int func6(int x,int y)
{
int _func6_;
if ((x != 0) && (y != 0))
{
_func6_ = 1;
}
else {
_func6_ = 0;
}
return _func6_;
}
int func7(int x)
{
int _func7_;
if (x == 0)
{
_func7_ = 1;
}
else {
_func7_ = 0;
}
return _func7_;
}
int main() {
i1 = 1;
i2 = 2;
i3 = 3;
i4 = 4;
for (i = 0; i <= 9; i++) {
arr[i] = i + 1;
}
a = func1(func2(func1(func3(func4(func5(func3(func2(func6(func7(i1), func5(i2)), i3), i4)), arr[0], func1(func2(func3(func4(func5(arr[1]), func6(arr[2], func7(arr[3])), func2(arr[4], func7(arr[5]))), arr[6]), arr[7]), func3(arr[8], func7(arr[9])), i1)), func2(i2, func3(func7(i3), i4))), arr[0], arr[1]), arr[2]), arr[3], func3(func2(func1(func2(func3(arr[4], func5(arr[5])), func5(arr[6])), arr[7], func7(arr[8])), func5(arr[9])), i1));
printf("%d",a);
return 0;
}
