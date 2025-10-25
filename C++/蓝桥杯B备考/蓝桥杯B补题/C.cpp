// C. Monocarp's String
// 目标：删去一个最短的连续子串，使剩余串中 'a' 与 'b' 数量相等；若只能删全串输出 -1；若已平衡输出 0。
// 设全串差值 D = (#a - #b)。需找子串其差值 = D。
// 将 'a' 视为 +1，'b' 视为 -1，前缀和 p[i] 表示前 i 个字符的差值。
// 子串 (l,r] 差值 = p[r]-p[l]，要求 p[r]-p[l]=D => p[l]=p[r]-D。
// 为使 r-l 最小：在遍历 r 时希望选到“最大的 l”(即该前缀值最近出现位置)。
// 因此维护每个前缀值的“最新出现下标” last[prefix]。
// 对每个 r (1..n): pref = p[r], 若存在 last[pref-D] 则候选长度 r - last[pref-D]。
// 更新答案后，将 last[pref] = r 覆盖为最新出现。O(n) 期望复杂度。

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

void solve(){
	int n; cin >> n; string s; cin >> s;
	int ca=0, cb=0; for(char c: s) (c=='a'? ca: cb)++;
	int D = ca - cb;  // 需删除子串的差值
unordered_map<int,int> last;  // 前缀值 → 最近下标
last.reserve(n*2+7);  // 预分配，减少哈希冲突
last.max_load_factor(0.7f);  // 控制加载因子，保证查询快速

last[0] = 0;  // 初始化：前缀和为 0 在下标 0（表示"无字符"）
int pref = 0;
int best = n + 1;

for(int r = 1; r <= n; ++r){
    // 累加第 r 个字符（1-indexed，所以用 s[r-1]）
    pref += (s[r-1] == 'a' ? 1 : -1);
    
    // 寻找满足 pref - p[l] = D 的最大 l
    auto it = last.find(pref - D);
    if(it != last.end()){
        int len = r - it->second;  // it->second 就是 l
        if(len < best){ 
            best = len; 
            if(best == 1) break;  // 最短子串长度=1，无法更优，早停
        }
    }
    
    // 更新当前前缀值的最新出现下标（覆盖）
    last[pref] = r;
}

// 若 best > n，说明没找到任何非空平衡方案 → -1
if(best >= n) cout << -1 << '\n'; else cout << best << '\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; cin >> T; while(T--) solve();
	return 0;
}
