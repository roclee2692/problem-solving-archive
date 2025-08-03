#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// a：工作日每天做题数，b：周末每天做题数，n：目标总题数
// m：完整的“周数”，t：一周总题数，d：剩余题数
// r：工作日补题天数，f：周末补题天数，ans：答案（最早满足天数）
ll a,b,m,n,d,ans,t,r,f; 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b >> n;

    t = 5 * a + 2 * b; // 每周最多能做的题目数
    m = n / t;         // 完整的周数
    d = n % t;         // 剩余题数

    if (d > 5 * a) {
        // ? 情况1：工作日最多做5*a题，剩下的题需要在周末完成
        // ? 易错点1：不能写成 ans = 7*m + 6，必须根据 b 判断周末需要几天
        // 用 (d - 5*a + b - 1) / b 向上取整周末天数，避免整除误差
        f = ((d - 5 * a) + b - 1) / b;
        ans = 7 * m + 5 + f; // 前5天+周末补题天数
    } else {
        // ? 情况2：剩余题目能在工作日完成
        // ? 易错点2：必须用 (d + a - 1) / a 来向上取整，而不是固定除数
        r = (d + a - 1) / a;
        ans = 7 * m + r;
    }

    cout << ans << endl;
    return 0;
}
