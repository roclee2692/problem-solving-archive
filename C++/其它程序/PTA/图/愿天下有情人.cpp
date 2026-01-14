#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using pll = pair<ll,ll>;

struct P { char sex; ll fa, mo; };
unordered_map<ll, P> info;      // 仅记录出现过的人
unordered_map<ll, char> sexOf;  // 仅记录已知性别
const int LIM = 4;              // 五服以内：本人(0)~高祖(4)

unordered_map<ll,int> getDist(ll id){
    unordered_map<ll,int> d;
    queue<pair<ll,int>> q;
    q.push({id,0});
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        ll u = cur.first; int dep = cur.second;
        if(u == -1 || d.count(u)) continue;
        d[u] = dep;
        if(dep == LIM) continue;
        auto it = info.find(u);
        if(it != info.end()){
            q.push({it->second.fa, dep+1});
            q.push({it->second.mo, dep+1});
        }
    }
    return d;
}

bool withinFour(ll a, ll b){
    auto da = getDist(a);                   // a 到各祖先的最短代数
    queue<pair<ll,int>> q;                  // 从 b 往上 BFS
    unordered_set<ll> vis;
    q.push({b,0});
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        ll u = cur.first; int dep = cur.second;
        if(u == -1 || vis.count(u)) continue;
        vis.insert(u);
        auto it = da.find(u);
        if(it != da.end() && it->second <= LIM && dep <= LIM) return true; // 共同祖先，且双方≤4
        if(dep == LIM) continue;
        auto jt = info.find(u);
        if(jt != info.end()){
            q.push({jt->second.fa, dep+1});
            q.push({jt->second.mo, dep+1});
        }
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N; 
    if(!(cin >> N)) return 0;               // 防止误喂控制台提示
    for(ll i=0;i<N;i++){
        ll id, fa, mo; char s;
        cin >> id >> s >> fa >> mo;
        info[id] = {s, fa, mo};
        sexOf[id] = s;                      // 只标记出现过的人的性别
    }

    ll K; cin >> K;
    while(K--){
        ll a, b; cin >> a >> b;
        bool bothKnown = sexOf.count(a) && sexOf.count(b);
        if(bothKnown && sexOf[a] == sexOf[b]){   // 只在“性别都已知且相同”时判 Never Mind
            cout << "Never Mind\n";
            continue;
        }
        cout << (withinFour(a,b) ? "No" : "Yes") << "\n";
    }
    return 0;
}
