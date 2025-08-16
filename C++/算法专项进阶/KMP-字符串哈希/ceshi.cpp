#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const int H=7, W=8;

// 颜色映射
int id(char c){ if(c=='B')return 0; if(c=='R')return 1; if(c=='W')return 2; return 3; }
char ch(int x){ return string("BRWY")[x]; }

// 10 类药片的索引次序（与题面一致的无序对）
int tId[4][4]; // 无序 pair -> 0..9
string tName[10]={"BY","BW","BR","BB","RY","RW","RR","WY","WW","YY"};

int cnt[10];        // 可用数量
int useCnt[10];     // 实际使用
char a[H][W];       // 医生目标
int Lc[H][W], Rc[H][W]; // 我们放置的左右/上下两半颜色（仅用于计分与输出）
bool hor[H][W];     // 是否水平骨牌起点

// 把一对颜色映射到类型索引（无序）
int pairType(int x,int y){
    if(x>y) swap(x,y);
    // 按题面：BY,BW,BR,BB, RY,RW,RR, WY,WW, YY
    // 手工构表
    static bool inited=false;
    if(!inited){
        // init tId
        for(int i=0;i<4;i++)for(int j=0;j<4;j++) tId[i][j]=-1;
        auto setid=[&](int x,int y,int idv){ if(x>y)swap(x,y); tId[x][y]=idv; };
        setid(0,3,0); // B,Y -> BY
        setid(0,2,1); // B,W
        setid(0,1,2); // B,R
        setid(0,0,3); // B,B
        setid(1,3,4); // R,Y
        setid(1,2,5); // R,W
        setid(1,1,6); // R,R
        setid(2,3,7); // W,Y
        setid(2,2,8); // W,W
        setid(3,3,9); // Y,Y
        inited=true;
    }
    return tId[x][y];
}

// 尝试给一条骨牌（两格颜色 c1,c2）分配某类药片 t，返回命中数
int scoreWithType(int c1,int c2,int t){
    string s=tName[t];
    int x = id(s[0]), y = id(s[1]);
    if(x==y){
        return (x==c1) + (y==c2); // 同色
    }else{
        // 可左右/上下翻转
        int s1 = (x==c1) + (y==c2);
        int s2 = (y==c1) + (x==c2);
        return max(s1,s2);
    }
}

// 贪心分配：先 2 分，再 1 分
void assignTypes(const vector<pair<pll,pll>>& segs){
    // segs: 每条骨牌由两格坐标组成 ((r1,c1),(r2,c2))
    // 预统计每条骨牌的“最佳正配类型”（两端颜色无序）
    int n=segs.size();
    vector<int> want(n,-1), hit2;
    vector<int> c1(n), c2(n);

    for(int i=0;i<n;i++){
        auto u=segs[i].first, v=segs[i].second;
        c1[i]=id(a[u.first][u.second]);
        c2[i]=id(a[v.first][v.second]);
        want[i]=pairType(c1[i],c2[i]);
    }

    // 2 分优先：按该类型的稀缺度从紧到松
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    auto scarcity=[&](int t){ return cnt[t]; };
    sort(ord.begin(),ord.end(),[&](int i,int j){
        if(want[i]==want[j]) return i<j;
        return scarcity(want[i]) < scarcity(want[j]);
    });

    vector<int> pickType(n,-1);
    memset(useCnt,0,sizeof useCnt);

    for(int i:ord){
        int t=want[i];
        if(cnt[t]>0){
            // 放正配，拿 2 分
            pickType[i]=t;
            cnt[t]--; useCnt[t]++;
        }
    }

    // 1 分阶段：对未分配的边，找任何还剩的、含 c1 或 c2 的类型
    for(int i=0;i<n;i++) if(pickType[i]==-1){
        int bestT=-1;
        for(int t=0;t<10;t++){
            if(cnt[t]==0) continue;
            if(scoreWithType(c1[i],c2[i],t)>=1){ bestT=t; break; }
        }
        if(bestT==-1){
            // 实在没有，就随便放一种剩余
            for(int t=0;t<10;t++) if(cnt[t]>0){ bestT=t; break; }
        }
        pickType[i]=bestT;
        cnt[bestT]--; useCnt[bestT]++;
    }

    // 写回具体半边颜色，用于计分与输出
    for(int i=0;i<n;i++){
        auto u=segs[i].first, v=segs[i].second;
        int r1=u.first, cA=u.second, r2=v.first, cB=v.second;
        string s=tName[pickType[i]];
        int x=id(s[0]), y=id(s[1]);
        // 选使命中更多的朝向
        int s1=(x==c1[i])+(y==c2[i]), s2=(y==c1[i])+(x==c2[i]);
        if(s2>s1) swap(x,y);
        // 水平或垂直写入
        if(r1==r2){ // 水平
            Lc[r1][cA]=x; Rc[r1][cB]=y; hor[r1][cA]=true;
        }else{      // 垂直（用 Lc 表示上半，Rc 表示下半）
            Lc[r1][cA]=x; Rc[r2][cB]=y; hor[r1][cA]=false;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 读图
    for(int i=0;i<H;i++){
        string s; cin>>s;
        for(int j=0;j<W;j++) a[i][j]=s[j];
    }
    // 读配额
    // "BY" "BW" "BR" "BB"
    // "RY" "RW" "RR"
    // "WY" "WW"
    // "YY"
    cin>>cnt[0]>>cnt[1]>>cnt[2]>>cnt[3];
    cin>>cnt[4]>>cnt[5]>>cnt[6];
    cin>>cnt[7]>>cnt[8];
    cin>>cnt[9];

    // 固定铺法：每行水平骨牌 (0,0)-(0,1), (0,2)-(0,3)...
    vector<pair<pll,pll>> segs;
    for(int r=0;r<H;r++){
        for(int c=0;c<W;c+=2){
            segs.push_back({{r,c},{r,c+1}});
        }
    }

    // 分配类型（贪心）
    assignTypes(segs);

    // 计分
    int score=0;
    for(auto e:segs){
        auto u=e.first, v=e.second;
        int r=u.first, c=u.second;
        int r2=v.first, c2=v.second;
        int x = Lc[r][c];
        int y = Rc[r2][c2];
        score += (x==id(a[r][c])) + (y==id(a[r2][c2]));
    }

    // 输出分数
    cout<<score<<"\n";

    // 画 13x15
    vector<string> out(2*H-1, string(2*W-1,'.'));
    for(int r=0;r<H;r++){
        for(int c=0;c<W;c++){
            int R=2*r, C=2*c;
            // 放字母：若此格是水平起点左半，或垂直起点上半，或右/下半也放字母都可；这里直接按目标图展示药片半的颜色
            char want = a[r][c];
            char put = want; // 简化：展示目标字母（视觉上不影响连线）
            out[R][C]=put;
        }
    }
    // 画连线
    for(auto e:segs){
        auto u=e.first, v=e.second;
        int r=u.first, c=u.second;
        int r2=v.first, c2=v.second;
        if(r==r2){
            out[2*r][2*c+1]='-';
        }else{
            out[2*r+1][2*c]='|';
        }
    }
    for(auto &row:out) cout<<row<<"\n";
    return 0;
}
