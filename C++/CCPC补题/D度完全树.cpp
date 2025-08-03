/*
reserve() 只会预留容量（capacity），并不会改变 size。

for (int &x : P) 会循环 size 个元素，而你 P 的 size = 0，所以 for循环不会执行，导致 P 根本没读入数据。

| 功能                | `reserve()`   | `resize()`      | `assign()`   |
| ----------------- | ------------- | --------------- | ------------ |
| 是否改变 `size()`     | ? (不变)        | ? (改变为 n)       | ? (改变为 n)    |
| 是否改变 `capacity()` | ? (≥n)        | 可能改变（按需要分配）     | 可能改变（至少满足 n） |
| 是否填充元素            | ? (不填充)       | ? (填充默认值或 val)  | ? (填充 val)   |
| 主要用途              | 预留空间、提高性能     | 调整大小、初始化元素      | 清空后赋新值       |
| 典型场景              | 优化 push\_back | 初始化数组、快速改变 size | 清空并重置所有元素    |
作用：为 vector 预分配内存，但不改变大小 (size)。

语法：P.reserve(n);

特点：

只是预留空间，size() 不变，仍然是 0。

之后的 push_back() 会更高效（避免频繁扩容）。

作用：直接改变 vector 的大小 (size)，并初始化元素。

语法：

resize(n)：默认初始化（int 为 0）

resize(n, val)：每个元素都初始化为 val

特点：

会填充或删除元素。

如果 n > 当前 size()，会新加元素。

如果 n < 当前 size()，会删除多余的元素。
vector<int> P;
P.resize(5);       // P = {0,0,0,0,0}  无论是否全局数组，P.resize(5); 都会默认填充 0！
P.resize(7, 42);   // P = {0,0,0,0,0,42,42}

3?? assign(n, val)
作用：清空原有元素，并重新填充 n 个 val。

语法：P.assign(n, val);

特点：

彻底替换原有内容。

size() 和 capacity() 都会调整（capacity 至少保证能容纳 n）。

2?? 没有 assign(n) 这种单参数形式
和 resize() 不同，assign() 必须指定值
*/#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int n,d,k,pos;
vector<int> P,F;//P存储读入的先序序列  F最后存储按层序下标排列的节点值
/* 递归将先序值填到层序下标 i 对应的位置 
度为d的树 d*i+j j<d D 叉「完全树」
顺序存储可由父节点推出子节点 也可由子节点推出父节点 */
void build(int i){//i是编号索引 从0开始
    if(i>=n) return; //P 的索引 0~n-1 递归终止条件
    F[i]=P[pos++];
    for(int t=1;t<=d;t++) { build(i*d+t); } //这里 i = i * d + t 会 改变原本的 i
}
int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>n>>d;
    P.assign(n,0);
    for(int &x:P){ cin>>x; }//根 左 右
    F.assign(n,0);// 层序数组 F 也需大小为 n，用来存放重建后的节点值
   // for(int &x:F){ cin>>x; } F不作为存储要查询元素的数组了 这里改用 while 连续读取替代
    build(0);
    //注意同行数字间以 1 个空格分隔，行首尾不得有多余空格。
    for (int i = 0; i < n; i++) cout << F[i] << " \n"[i == n-1];
    cin>>k;
    while(k--){
        int x;cin>>x;
        while(1){
            cout<<F[x];
            if(x==0) break;
            cout<<'\n';
            x=(x-1)/d;
        }
        cout<<'\n';
    }
  return 0;
}
