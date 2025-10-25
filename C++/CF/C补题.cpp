#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll=pair<ll,ll>;

ll t;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>t;
    while(t--){
        ll n; cin>>n; 
        string s; cin>>s;
        ll cnta=0,cntb=0,ans=n,cp=0;
        vector<ll> p(n+1, 0);//前缀和
        for(char c : s){
            if(c == 'a') cnta++;
            else cntb++;
        }
        ll D=cnta-cntb;
        if(D==0) {cout<<0<<'\n'; continue; }

        for(int i=1;i<=n;i++){
            if(s[i-1]=='a') p[i]=++cp;
            else p[i]=--cp;
        }

        map<ll, ll> last_pos;
        last_pos[0] = 0;  // p[0] = 0 在位置 0
        ans = n+1;
 // 子串 (l,r] 差值 = p[r]-p[l]，要求 p[r]-p[l]=D => p[l]=p[r]-D。
// 为使 r-l 最小：在遍历 r 时希望选到“最大的 l”(即该前缀值最近出现位置)。
// 因此维护每个前缀值的“最新出现下标” last[prefix]。
// 对每个 r (1..n): pref = p[r], 若存在 last[pref-D] 则候选长度 r - last[pref-D]。
        for(int r=1;r<=n;r++){
            ll need = p[r] - D;
            if(last_pos.count(need)){  // 检查键是否存在
                ll l = last_pos[need];
                // 不允许删除整个数组 [0, n]
                if(r - l < n){  // 长度 < n，说明不是全部
                    ans = min(ans, (ll)(r - l));
                }
            }
            last_pos[p[r]] = r;//无论能否找到p[l]对应的键 都要将本次已经查过的r p[r] 位置记录在 哈希表 键值对中
        }
        
        if(ans > n) cout<<-1<<'\n';
        else cout<<ans<<'\n';
    }
    
    return 0;
}