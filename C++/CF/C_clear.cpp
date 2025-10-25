// C. Monocarp's String - 最清晰的"思路分解"版本
// ============================================================

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        string s; cin >> s;
        
        // ============ 第一步：计算前缀和 ============
        // p[i] = 前 i 个字符的"差值"
        // 'a' 记为 +1，'b' 记为 -1
        // 
        // 例：s = "aabb"
        //     s[0]='a' s[1]='a' s[2]='b' s[3]='b'
        //     p[0]=0, p[1]=1, p[2]=2, p[3]=1, p[4]=0
        
        vector<int> p(n + 1);
        p[0] = 0;
        
        for(int i = 1; i <= n; ++i){
            p[i] = p[i-1] + (s[i-1] == 'a' ? 1 : -1);
        }
        
        // ============ 第二步：计算需删除子串的差值 D ============
        // 整个串的差值 = p[n]
        // 我们要删一个子串，使得剩余串差值为 0
        // 若子串差值为 D，则：剩余差值 = p[n] - D = 0
        // 所以 D = p[n]
        
        int D = p[n];
        
        // 若整个串已平衡，答案是 0
        if(D == 0){
            cout << 0 << '\n';
            continue;
        }
        
        // ============ 第三步：找最短子串，其差值 = D ============
        // 子串 [l+1, r] 的差值 = p[r] - p[l]
        // 我们要找 p[r] - p[l] = D 的子串，使 r-l 最小
        // 
        // 转化：p[r] - p[l] = D
        //      p[l] = p[r] - D
        //
        // 对于固定的 r，我们要找某个 l 使得 p[l] = p[r] - D
        // 为了让长度 r-l 最小，我们要 l 尽可能大（即最近出现）
        
        // last[val] 表示"差值为 val 的最新出现位置"
        map<int, int> last;
        last[0] = 0;  // 初始化：前缀 0 在位置 0
        
        int ans = n + 1;  // 初始化为"不存在"
        
        for(int r = 1; r <= n; ++r){
            int target = p[r] - D;  // 需要找的前缀值
            
            // 查询：是否存在某个位置 l，使得 p[l] = target？
            if(last.find(target) != last.end()){
                int l = last[target];
                int len = r - l;  // 子串 [l+1, r] 的长度
                ans = min(ans, len);
                
                // 如果找到长度为 1 的子串，已经最优，可以提前结束
                if(ans == 1) break;
            }
            
            // 更新：记录当前前缀值 p[r] 在位置 r
            // （如果 p[r] 之前出现过，这行会覆盖，保留最新的）
            last[p[r]] = r;
        }
        
        // ============ 第四步：输出结果 ============
        // 注意：我们要删一个"非空"的子串，即长度不能是 0
        // 删全部（长度=n）时输出 -1
        if(ans >= n){
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
    
    return 0;
}
