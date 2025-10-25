#include <bits/stdc++.h>
using namespace std;
using ld=long double;
const double PI = acos(-1.0);        // 精确的 π
int main()
{
  // 请在此输入您的代码
  ld R,x=233,y=666.0,myatan,l;
  R=sqrt(x*x+y*y);
  myatan=atan2(y, x);  // 使用atan2处理所有象限
  l=R*myatan;          // 弧长 = 半径 × 角度（弧度）
  cout<<fixed<<setprecision(0)<<l<<endl;
  return 0;
}