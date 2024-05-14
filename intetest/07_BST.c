#include<stdio.h>
#include<stdbool.h>
int value[10000];
int left_child[10000];
int right_child[10000];
int now;
int ret, n, readn, i, root;
int search(int root,int x)
{
int _search_;
if ((root == -1) || (value[root] == x))
{
_search_ = root;
}
else {
if ((x > value[root]))
{
_search_ = search(right_child[root], x);
}
else {
_search_ = search(left_child[root], x);
}
}
return _search_;
}
int find_minimum(int root)
{
int _find_minimum_;
if ((root == -1))
{
_find_minimum_ = -1;
}
else {
if ((left_child[root] != -1))
{
_find_minimum_ = find_minimum(left_child[root]);
}
else {
_find_minimum_ = root;
}
}
return _find_minimum_;
}
int new_node(int x)
{
int _new_node_;
value[now] = x;
left_child[now] = -1;
right_child[now] = -1;
_new_node_ = now;
now = now + 1;
return _new_node_;
}
int insert(int root,int x)
{
int _insert_;
if ((root == -1))
{
_insert_ = new_node(x);
}
else {
if ((x > value[root]))
{
right_child[root] = insert(right_child[root], x);
}
else {
left_child[root] = insert(left_child[root], x);
}
}
_insert_ = root;
return _insert_;
}
int delete_node(int root,int x)
{
int _delete_node_;
int tmp;
if ((x > value[root]))
{
right_child[root] = delete_node(right_child[root], x);
}
else {
if ((x < value[root]))
{
left_child[root] = delete_node(left_child[root], x);
}
else {
if ((left_child[root] == -1) && (right_child[root] == -1))
{
_delete_node_ = -1;
}
else {
if ((left_child[root] == -1) || (right_child[root] == -1))
{
if ((left_child[root] == -1))
{
_delete_node_ = right_child[root];
}
else {
_delete_node_ = left_child[root];
}
}
else {
tmp = find_minimum(right_child[root]);
value[root] = value[tmp];
right_child[root] = delete_node(right_child[root], value[tmp]);
}
}
}
}
_delete_node_ = root;
return _delete_node_;
}
void inorder(int root)
{
if ((root != -1))
{
inorder(left_child[root]);
printf("%d%c",value[root], ' ');
inorder(right_child[root]);
}
}
int main() {
ret = 0;
now = 0;
scanf("%d",&n);
if ((n == 0))
{
ret = 0;
}
scanf("%d",&readn);
root = new_node(readn);
for (i = 1; i <= n - 1; i++) {
scanf("%d",&readn);
insert(root, readn);
}
inorder(root);
scanf("%d",&n);
for (i = 1; i <= n; i++) {
scanf("%d",&readn);
root = delete_node(root, readn);
}
inorder(root);
return 0;
}
