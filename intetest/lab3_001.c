#include<stdio.h>
#include<stdbool.h>
const int a = 1;
const double b = 3.0000000000000000;
const char c = 'c';
const char blank = ' ';
int d;
double e;
char f;
bool g;
int main() {
d = 6;
e = 6.0000000000000000;
f = 'f';
g = 2 > 1;
printf("\n");
printf("%d%c%.6lf%c%c%c%d%c%.6lf%c%c",a, blank, b, blank, c, blank, 1, blank, 1.0000000000000000, blank, 'y');
printf("\n");
printf("\n");
printf("\n");
return 0;
}
