// E. Predicting Popularity
// 模型：用户 i 的“门槛差值” diff_i = max(ai - ac, 0) + max(di - dr, 0)。
// 过程：当前已观看人数 p，从未观看且 diff_i <= p 的用户会立刻观看，p++，直到无法扩张。
// 最终观看人数等价于：将所有 diff 升序，找到最大 p 使得对 0..p-1：diff_j <= j。
// 等价条件：对每个 k (1..p)，有 count{ diff <= k-1 } >= k。
// 若定义 prefixCount(x) = # { diff <= x }，则寻找最小 x 使 prefixCount(x) < x+1，答案 p = x；若不存在失败点则 p = n。
// 将问题转化为序列 b[x] = count[x] - 1 (x=0..n-1)，前缀和 PS[x] = Σ_{i=0..x} b[i] = prefixCount(x) - (x+1)。
// 找到首个 PS[x] < 0 的位置；若无则所有前缀合法 => 观看人数 = n。
// 动态更新：单点修改 (某用户 diff 旧值、新值)，需要 O(log n) 查询首个负前缀。
// 使用段树节点存：sum = 区间 Σ b[i]；minPref = 区间内最小前缀和（相对于本区间起点）。
// 合并：sum = L.sum + R.sum；minPref = min(L.minPref, L.sum + R.minPref)。
// 查找首个负前缀：若 root.minPref >=0 => p=n；否则遍历段树找到首个前缀和 <0 的索引。
// 只需关注 diff < n 的用户；diff >= n 不可能被激活（需要 >= n 个已观看，而最多 n-1 个在他之前），对前缀条件无贡献。

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	int sum;      // Σ b[i]
	int minPref;  // 区间内最小前缀和（基于区间起点为 0）
};

struct SegTree {
	int n;
	vector<Node> st;
	SegTree(int n=0){ init(n); }
	void init(int n_){ n = n_; st.assign(4*n, {0,0}); }
	static Node merge(const Node &L, const Node &R){
		Node res;
		res.sum = L.sum + R.sum;
		res.minPref = std::min(L.minPref, L.sum + R.minPref);
		return res;
	}
	void build(const vector<int>& b, int p, int l, int r){
		if(l==r){
			int val = b[l];
			st[p].sum = val;
			st[p].minPref = std::min(0, val);
			return;
		}
		int m=(l+r)>>1;
		build(b,p<<1,l,m);
		build(b,p<<1|1,m+1,r);
		st[p]=merge(st[p<<1],st[p<<1|1]);
	}
	void build(const vector<int>& b){ build(b,1,0,n-1); }
	void pointUpdate(int idx, int newVal, int p, int l, int r){
		if(l==r){
			st[p].sum = newVal;
			st[p].minPref = std::min(0, newVal);
			return;
		}
		int m=(l+r)>>1;
		if(idx<=m) pointUpdate(idx,newVal,p<<1,l,m); else pointUpdate(idx,newVal,p<<1|1,m+1,r);
		st[p]=merge(st[p<<1],st[p<<1|1]);
	}
	void pointUpdate(int idx, int newVal){ pointUpdate(idx,newVal,1,0,n-1); }
	// 返回首个前缀和 <0 的位置；若不存在返回 -1
	int firstNegative(){
		if(st[1].minPref>=0) return -1;
		int p=1,l=0,r=n-1; int pref=0; // pref = 已在上层累加的前缀和
		while(l!=r){
			int m=(l+r)>>1;
			Node &Lnode = st[p<<1];
			if(pref + Lnode.minPref < 0){
				// 在左侧
				p = p<<1; r = m;
				continue;
			} else {
				pref += Lnode.sum;
				p = p<<1|1; l = m+1;
			}
		}
		return l; // 该位置前缀首次 <0
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int ac, dr; if(!(cin>>ac>>dr)) return 0;
	int n; cin>>n;
	vector<int> a(n), d(n);
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++) cin>>d[i];
	auto calcDiff = [&](int A, int D)->int{
		long long da = (long long)A - ac; if(da<0) da=0;
		long long dd = (long long)D - dr; if(dd<0) dd=0;
		long long diff = da + dd; // up to 2e6
		if(diff >= n) return n; // 视为不可达
		return (int)diff;
	};
	vector<int> diff(n);
	vector<int> countIdx(n,0); // count of diff == i, only i in [0,n-1]
	for(int i=0;i<n;i++){
		int df = calcDiff(a[i], d[i]);
		diff[i]=df;
		if(df < n) countIdx[df]++;
	}
	// b[i] = countIdx[i] - 1
	vector<int> base(n);
	for(int i=0;i<n;i++) base[i]=countIdx[i]-1;
	SegTree st(n); st.build(base);
	int m; cin>>m;
	while(m--){
		int k, na, nd; cin>>k>>na>>nd; --k;
		// remove old
		int old = diff[k];
		if(old < n){
			countIdx[old]--;
			st.pointUpdate(old, countIdx[old]-1);
		}
		a[k]=na; d[k]=nd;
		int nw = calcDiff(a[k], d[k]);
		diff[k]=nw;
		if(nw < n){
			countIdx[nw]++;
			st.pointUpdate(nw, countIdx[nw]-1);
		}
		int pos = st.firstNegative();
		int ans = (pos==-1 ? n : pos); // 若无负前缀，全部可观看；否则，答案=首个失败位置
		cout<<ans<<"\n";
	}
	return 0;
}
