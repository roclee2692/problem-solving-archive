#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
//二进制枚举子集
// 用于计算二进制数中 1 的个数
int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
        n &= (n - 1);
        count++;
    }
    return count;
}
/*通用公式
这个 + (单个) - (两两交集) + (三三交集) - ... 的模式可以推广到任意 n 个集合。
这个公式的核心在于：一个元素的最终计数，取决于它属于多少个集合。奇数个交集前是加号，偶数个交集前是减号。
*/
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N;
    int k;
    cin >> N >> k;

    vector<long long> p(k);
    for (int i = 0; i < k; ++i) {
        cin >> p[i];
    }

    long long ans = 0;
    // 遍历所有非空子集，mask 从 1 到 2^k - 1
    for (int mask = 1; mask < (1 << k); ++mask) {
        long long product = 1;
        int subset_size = 0;

        // 根据 mask 构建子集
        for (int i = 0; i < k; ++i) {
            // 检查第 i 位是否为 1
            if ((mask >> i) & 1) {
                // 防止乘积溢出 long long
                if ((double)product * p[i] > 2e18) { // 设定一个比N大得多的安全上限
                    product = N + 1; // 使 N / product 结果为 0
                    break;
                }
                product *= p[i];
                subset_size++;
            }
        }

        // 容斥原理：奇加偶减
        if (subset_size % 2 == 1) { // 奇数个元素的子集，加
            ans += N / product;
        } else { // 偶数个元素的子集，减
            ans -= N / product;
        }
    }

    cout << ans << endl;

    return 0;
}