#include<stdio.h>
#include<stdbool.h>
const int space = 32;
const char *ne = "Not exist";
int graph[4][4];
int color[4];
int i, m;
void printsolution()
{
int i;
for (i = 0; i <= 3; i++) {
printf("%d",color[i]);
}
}
void printmessage()
{
printf("%s",ne);
}
int issafe()
{
int _issafe_;
int i, j;
_issafe_ = 1;
for (i = 0; i <= 3; i++) {
for (j = i + 1; j <= 3; j++) {
if ((graph[i][j] != 0) && (color[j] == color[i]))
{
_issafe_ = 0;
}
}
}
return _issafe_;
}
int graphcoloring(int m,int i)
{
int _graphcoloring_;
int j;
bool foundsolution;
foundsolution = false;
if ((i == 4))
{
if ((issafe() != 0))
{
printsolution();
_graphcoloring_ = 1;
foundsolution = true;
}
}
else {
for (j = 1; j <= m; j++) {
color[i] = j;
if ((graphcoloring(m, i + 1) != 0))
{
foundsolution = true;
break;
}
color[i] = 0;
}
}
if (foundsolution)
{
_graphcoloring_ = 1;
}
else {
_graphcoloring_ = 0;
}
return _graphcoloring_;
}
int main() {
graph[0][0] = 0;
graph[0][1] = 1;
graph[0][2] = 1;
graph[0][3] = 1;
graph[1][0] = 1;
graph[1][1] = 0;
graph[1][2] = 1;
graph[1][3] = 0;
graph[2][0] = 1;
graph[2][1] = 1;
graph[2][2] = 0;
graph[2][3] = 1;
graph[3][0] = 1;
graph[3][1] = 0;
graph[3][2] = 1;
graph[3][3] = 0;
m = 3;
for (i = 0; i <= 3; i++) {
color[i] = 0;
}
if (graphcoloring(m, 0) == 0)
{
printmessage();
}
return 0;
}
