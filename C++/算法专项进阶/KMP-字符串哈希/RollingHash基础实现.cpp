/*若 B ≤ 字符映射的最大值，一定存在“进位合并”导致的确定性碰撞。
ASCII/字母映射常在 26、52、128、255、127… 这些范围，B=10 肯定不安全。
原则：B > 字符映射最大值，防止“进位合并”的确定性撞。

常用：131、13331（经验好，分布稳）；

更稳：随机基数（每次运行固定一次，范围可取 [256, 1e6) 的奇数）。

不是必须是质数，但常用质数/奇数、且与模数互素，分布更均匀。
模数 M
取 大质数：1e9+7、1e9+9、1e9+21、1e9+33、998244353 等。

双模数（两个不同的 M）或 ULL 溢出 + 单模数 做双哈希，基本无忧。
B 要大：至少 > 字符映射最大值（比如处理 ASCII，B 取 131 就很稳）。

别只信单模：能上 双哈希 就上（(B1,M1) + (B2,M2) 或 ULL + M）。

随机 B：每次程序启动随机一个 奇数 B 并固定，难被定向构造卡。
在 C/C++ 里，无符号整数（unsigned long long，简称 ULL）的加减乘是按模 
2^64 来做的。 
不写 % 取模，CPU 也会帮你“对 2^64取模
同一次程序内的基数 B 必须固定（否则前后缀表不匹配）。常用：131/13331 或随机一个奇数。
碰撞概率虽低,但理论上仍可能撞。更稳可用双哈希（再加一个大质数模），或“ULL + 单模数”*/
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull; // 用自然溢出避免取模
using uc=unsigned char;
using ll=long long;
const ull B = 131;              // 进制
// 全局数组（在本例中会被反复重置）
// H[i]  : 字符串前缀哈希值（下标从 1 开始）
// pB[i] : B 的 i 次方（用于计算子串哈希）
vector<ull> H, pB;
// 计算子串 [l, r]（1-index）的哈希值
// 利用前缀哈希公式： hash(l,r) = H[r] - H[l-1] * B^(r-l+1)
// 自然溢出（ULL）会自动按 2^64 取模
ull getHash(ll l,ll r){
    return H[r]-H[l-1]*pB[r-l+1];
}
//A) 判重（Luogu P3370 这类）
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin>>n;
    vector<string> s(n);
    for(int i=0;i<n;i++) cin>>s[i];
    vector<ull> hashes;// 存储每个字符串的整体哈希值
     hashes.reserve(n);  // 预分配容量（可选，提升性能）
     // 对每个字符串单独计算哈希值
     for(auto &str:s){
        ll m=str.size();// 当前字符串长度

         // 初始化前缀哈希数组和 B 的幂数组（长度 m+1，0 号位为哨兵）
        H.assign(m+1, 0);
        pB.assign(m+1, 1);
           // 构建前缀哈希与幂表
        // H[i]  = 前 i 个字符的哈希值（下标从 1 对应 str[0]）
        // pB[i] = B^i
        for(int i=1;i<=m;i++){
            H[i]=H[i-1]*B+(uc)str[i-1];
            pB[i]=pB[i-1]*B;
        }
         // 整个字符串的哈希值存入 hashes
        hashes.push_back(H[m]);
     }
     
    // 对所有字符串的哈希值排序
    sort(hashes.begin(), hashes.end());
     // unique 返回去重后新末尾的迭代器，减去 begin() 得到不重复的个数
    cout << unique(hashes.begin(), hashes.end()) - hashes.begin() << "\n";

    return 0;
}
//B) 子串判断（Luogu P5410 这类）
/*
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S, P; cin>>S>>P;
    B = gen_base();
    build_hash(S);
    ull hp = 0;
    for(char c: P) hp = hp*B + (unsigned char)c;

    int n=S.size(), m=P.size();
    bool ok=false;
    for(int i=1;i+m-1<=n;i++){
        if(get_hash(i, i+m-1) == hp){ ok=true; break; }
    }
    cout << (ok? "Yes\n" : "No\n");
    return 0;
}
*/