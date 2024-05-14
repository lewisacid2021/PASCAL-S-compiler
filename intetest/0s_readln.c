#include<stdio.h>
#include<stdbool.h>
int a, b, c, d, e;
int main() {
char input[100000];
  fgets(input, sizeof(input), stdin);sscanf(input, "%i%i%i",a, b, c);
char input[100000];
  fgets(input, sizeof(input), stdin);sscanf(input, "%i%i",d, e);
printf("%d%d%d%d%d\n",a, b, c, d, e);
return 0;
}
