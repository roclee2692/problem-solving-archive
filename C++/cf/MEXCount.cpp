#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int t,n;

int main(){
ios::sync_with_stdio(0);cin.tie(0);
cin>>t;
    while(t--){
        cin>>n;
vector<int> A(n),F(n+1);//统计频率利用了数组模拟哈希表 数据范围是0~n so your arrary need to n+1;
for(int i=0;i<n;i++){
    cin>>A[i];
    if(A[i]<=n) { F[A[i]]++; }
}
// freq[m]：记录每个数字 m 出现次数，用于判断最少要删多少个 m

// M0：原始数组的 MEX
// 因为更大的 M 不可能是删完后 MEX，所以只枚举到 M0

// diff 数组：用于统计每个 k 能得到多少种不同的 MEX
// 差分思想：先把所有区间修改记录到 diff 数组
// 区间叠加不立刻改结果，而是累积在 diff
// 最终一次前缀和就能算出每个 k 能取多少种不同的 MEX                                
   int M0=0;
   while(M0<=n && F[M0]>0) M0++;
    vector<int> diff(n+2,0);
     // 2. 对每个 m∈[0, M0] 做区间 [L, R] 差分
    for(int m=0;m<=M0;m++){ // m 表示期望最终得到的 MEX 值
        int L=F[m];  // L：最少要删掉 freq[m] 个 m
        int R=n-m; // R：最多能删 n-m 个数
    // 因为至少要保留 0…m-1 共 m 个不同的数
        if(L > R) continue; //理论不会，但留保险
        diff[L]+=1;//左闭区间
        diff[R+1]-=1;//右开区间 不会取到R+1
    }
  // 3. 前缀和得到答案
  // cur 累加差分，得到 ans[k]
// ans[k] 表示删 k 个数后能得到多少种不同的 MEX
  vector<int> ans(n+1,0);
  int cur=0;
  for(int k=0;k<=n;k++){
    cur+=diff[k];
    ans[k]=cur;
  }

    // 4. 输出
    for(int k=0;k<=n;k++){
        cout<<ans[k]<<" \n"[k==n];
    }

}

  return 0;
}
