// D. Inversion Value of a Permutation
// 设排列 p 长度 n。\n
// inversion value = 含至少一个逆序对的子区间 (l,r) (l<r) 数量。\n
// 所有 (l,r) 对总数 T = C(n,2)。无逆序的子区间 ⇔ 完全严格递增。\n
// 若把排列分成若干极大递增段长度 Li，则所有严格递增子区间只会在同一段内：S = Σ C(Li,2)。\n
// 目标：给定 k（想要的 inversion value），令 S_target = T - k，需要找分拆 Li 使 Σ Li = n 且 Σ C(Li,2)=S_target。\n
// n ≤ 30，S_target ≤ C(30,2)=435，可用 DP：dp[len][s] 表示用掉 len 元素得到严格递增子区间数 s 可达。\n
// 构造：得到段长度序列后，用数值从大到小分段，每段内部升序，段与段之间形成下降即可。\n
// 因为第一段使用最大的一组数升序，后面段使用更小的数升序，所以跨段必出现下降，保证极大递增段结构。\n

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

static inline int comb2(int x){ return x*(x-1)/2; }

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; if(!(cin>>T)) return 0;
	while(T--){
		int n; long long k; cin>>n>>k;
		long long Tpairs = 1LL*n*(n-1)/2; // 总无序对数(子区间长度≥2的数量)
		if(k < 0 || k > Tpairs){ cout<<0<<"\n"; continue; }
		long long S_target_ll = Tpairs - k; // 需要的严格递增子区间数量
		int S_target = (int)S_target_ll; // 安全，因为最大 435

		vector<vector<char>> dp(n+1, vector<char>(S_target+1, 0));
		vector<vector<int>> preLen(n+1, vector<int>(S_target+1, -1));
		vector<vector<int>> preSum(n+1, vector<int>(S_target+1, -1));
		dp[0][0] = 1;
		for(int used=0; used<n; ++used){
			for(int s=0; s<=S_target; ++s){
				if(!dp[used][s]) continue;
				for(int l=1; l+used<=n; ++l){
					int ns = s + comb2(l);
					if(ns > S_target) continue;
					if(!dp[used+l][ns]){ // 记录一次即可
						dp[used+l][ns] = 1;
						preLen[used+l][ns] = l;
						preSum[used+l][ns] = s;
					}
				}
			}
		}
		if(!dp[n][S_target]){ cout<<0<<"\n"; continue; }
		// 回溯段长度
		vector<int> runs; runs.reserve(n);
		int curLen = n, curS = S_target;
		while(curLen>0){
			int l = preLen[curLen][curS];
			int ps = preSum[curLen][curS];
			if(l==-1){ runs.clear(); break; }
			runs.push_back(l);
			curLen -= l; curS = ps;
		}
		reverse(runs.begin(), runs.end());
		// 构造排列
		vector<int> perm; perm.reserve(n);
		int nextHigh = n;
		for(int L: runs){
			// 取最大的 L 个数字：nextHigh-L+1 ... nextHigh，升序加入
			for(int v = nextHigh - L + 1; v <= nextHigh; ++v) perm.push_back(v);
			nextHigh -= L;
		}
		for(int i=0;i<n;i++){
			if(i) cout<<' ';
			cout<<perm[i];
		}
		cout<<'\n';
	}
	return 0;
}
