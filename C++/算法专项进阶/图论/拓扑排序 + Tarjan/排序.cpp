#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const int N=27;
const int M=605;
ll n,m;
vector<pll> G[N];//应该是 G[N]
ll indeg[N];//tmpgrees
vector<ll> save;
ll tmp[N];

ll topu(){
    save.clear();//save 没清空
    memcpy(tmp, indeg, sizeof(indeg)); // ✅ 每次判定只改 tmp，不动 indeg
    queue<ll> q; ll cnt=0;
    for(ll i=1;i<=n;i++){//遍历范围错了 n
        if(tmp[i]==0){
            q.push(i);
            cnt++;
        } 
    }
    if(cnt==0) return 0;//有环
    bool unique = true;
    while(!q.empty()){//唯一性判定的位置不对
        ll u=q.front();//要在每轮弹出前检查 q.size()
        if(q.size() > 1) unique = false;  // ✅ 某轮出现岔路 → 非唯一  信息不足把岔路连起来
        q.pop();
        save.push_back(u);
        for(auto &e:G[u]){
            ll v=e.first,id=e.second;
            if(--tmp[v]==0) q.push(v);
        }
        
    }
    ll num=save.size();   
    if(num==n) return unique==1? 1 : -1;//成功排序 无法确定输出-1
    if(num<n) return 0;//有环 矛盾为0
}

int main(){
    cin>>n>>m;
    for(ll i=1;i<=m;i++) {
    char A, lt, B; 
    cin >> A >> lt >> B;     // 读到 'A' '<' 'B'
    ll a = A - 'A' + 1;      // 再把字母映射到 1..n
    ll b = B - 'A' + 1;
    bool being=0;
    for(auto &e:G[a]){
        ll e_b=e.first;
        if(e_b==b){
            being=1;
            break;
        }
    }
    if(!being) {
        G[a].push_back(pll(b,i));
        indeg[b]++;
     } 
     // 这里始终调用一次判定（being 与否都判），但 being 时图未变化
     ll st=topu();// 返回 0/1/-1
        if(st == 0){
            cout << "Inconsistency found after " << i << " relations.\n";
            return 0;//0
        }
        if(st == 1){
            cout << "Sorted sequence determined after " << i << " relations: ";
            for(auto x : save) cout << char('A' + x - 1);
            cout << ".\n";//1
            return 0;
        }

    }
    
    cout << "Sorted sequence cannot be determined.\n";//-1
    return 0;
}