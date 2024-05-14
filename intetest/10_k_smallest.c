#include<stdio.h>
#include<stdbool.h>
const int space = 32;
int arr[1000];
int n, k, i, low, high;
void swap(int a,int b)
{
int tmp;
tmp = arr[a];
arr[a] = arr[b];
arr[b] = tmp;
}
int findpivot(int start,int endindex)
{
int _findpivot_;
int pivot, pindex, i;
pivot = arr[endindex];
pindex = start;
for (i = start; i <= endindex - 1; i++) {
if (arr[i] <= pivot)
{
swap(i, pindex);
pindex = pindex + 1;
}
}
swap(pindex, endindex);
_findpivot_ = pindex;
return _findpivot_;
}
void findsmallest(int low,int high,int k,int n)
{
int pindex, i;
if (low != high)
{
pindex = findpivot(low, high);
if (k == pindex)
{
for (i = 0; i <= pindex - 1; i++) {
printf("%d",arr[i]);
}
}
else {
if (k < pindex)
{
findsmallest(low, pindex - 1, k, n);
}
else {
findsmallest(pindex + 1, high, k, n);
}
}
}
}
int getint()
{
int _getint_;
int n;
scanf("%d",&n);
_getint_ = n;
return _getint_;
}
int main() {
n = getint();
k = getint();
for (i = 0; i <= n - 1; i++) {
arr[i] = getint();
}
low = 0;
high = n - 1;
findsmallest(low, high, k, n);
return 0;
}
