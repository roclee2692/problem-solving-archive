#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX=1e9+7;
const int ROOM=1e5+7;
const double INF = 1e18;
int n,k; 

// 小顶堆：存储 (当前值, 下标)
    // 注意：C++ 默认是大顶堆，所以我们用 greater<pair<...>>
    priority_queue<pair<ll,int>, 
                   vector<pair<ll,int>>, 
                   greater<pair<ll,int>> > pq;
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>k;      // a[i]：下标 i 对应的当前值（会被多次更新）
	vector<ll> a(n);//存储最初的真实值，如果与后续累加后的不符直接舍弃 
// pre[i], nxt[i]：分别存储 i 的左、右邻居下标(若不存在则设为 -1 或 n)
vector<int> pre(n), nxt(n);
// removed[i]：标记下标 i 是否已被删除
vector<bool> removed(n, false);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	 for(int i = 0; i < n; i++){
        pre[i] = i - 1;   // i 的左邻居
        nxt[i] = i + 1;   // i 的右邻居
    }
	pre[0] = -1;       // 第 0 个元素没有左邻居
	nxt[n - 1] = -1;   // 最后一个元素没有右邻居
// 初始化堆
    for(int i = 0; i < n; i++){
        pq.push({a[i], i});
    }
     // 执行 k 次“删除最小值”操作
    while(k>0){//这里不能直接用k--;
	//原因是后面在第一个if中使用了continue 这样会使得k的值被多消耗 
        // 取出堆顶
        pair<ll,int> temp = pq.top();
        ll val=temp.first;
        int idx=temp.second;
        pq.pop();
		// 如果该元素已经被删除 or 与当前 a[idx] 不符，则说明是“过期”元素，跳过
        if(removed[idx] || a[idx] != val) {
            continue;
        }
		k--; 
        // 否则，这就是此时真正的最小值，需要执行“删除”操作
        removed[idx] = true; // 标记删除
         // 把它的值加给它的“未被删除的”左邻居和右邻居
        int L = pre[idx];
        int R = nxt[idx];

        // 如果左邻居存在且未被删，就更新它的值 a[L]
        if(L != -1 && !removed[L]){
            a[L] += val;
            // 更新后把 (新的值, L) 推回堆
            pq.push({a[L], L});//这里很重要，最小堆中同时也有无效的值，
			//即与更新后的a[i]不符合的，但是不会被再次利用 
        }
          // 如果右邻居存在且未被删，就更新它的值 a[R]
        if(R != -1 && !removed[R]){
            a[R] += val;
            // 更新后把 (新的值, R) 推回堆
            pq.push({a[R], R});
        }
          // 让 L 和 R 变为邻居，跳过当前 idx
        if(L != -1) nxt[L] = R;
        if(R != -1) pre[R] = L;
           }
           // 输出剩下未被删除的元素
    // 题意通常不会要求保持原顺序(取决于题目)，如果需保持原顺序，就按 i=0..n-1 判断输出即可
    for(int i = 0; i < n; i++){
        if(!removed[i]){
            cout << a[i] << " ";
        }
    }
    cout<<endl; 
  return 0;
}
