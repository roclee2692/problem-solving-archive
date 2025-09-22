/*把一个复杂的“集合”状态，压缩成了一个简单的整数。
DP 数组就可以这样定义：dp[mask] 表示当状态为 mask 时的最优解*/#include <iostream>


/*写 bitmask 枚举 1 到 (1<<n)-1
这个任务的本质是遍历一个包含 n 个元素的集合的所有非空子集。

1 << n: 相当于 2 
n
 。这是所有可能子集的数量（包括空集）。例如 n=3，1<<3 是 1000 (二进制)，即 8。

所有子集对应的 bitmask 范围是从 0 (空集 000) 到 (1<<n) - 1 (全集 111)。

题目要求从 1 开始，就是排除 0 (空集)。*/
#include <iostream>
#include <bitset> // 用于方便地打印二进制表示

void list_subsets(int n) {
    // 1 << n 计算出 2^n。循环从 1 到 2^n - 1。
    // 例如 n=3, 1<<3 = 8。循环范围是 [1, 7]。
    for (int mask = 1; mask < (1 << n); ++mask) {
        // std::bitset<8>(mask) 可以将整数 mask 格式化为 8 位的二进制，方便观察
        std::cout << "Decimal: " << mask << ", Binary: " << std::bitset<8>(mask) << " -> { ";
        
        // 打印出当前 mask 代表的集合
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) { // 检查第 i 位是否为 1
                std::cout << i << " ";
            }
        }
        std::cout << "}" << std::endl;
    }
}


//高效的技巧 (快):

/*for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
    // 直接遍历 mask 的所有非空子集 submask
    // 处理 submask ...
}*/
//这个 for 循环看起来像黑魔法，但它非常高效。 (submask - 1) & mask 这个操作会巧妙地生成 mask 的下一个（按字典序更小的）子集。它的总复杂度是 O(3 

 //) 级别的（所有状态的所有子集之和），远优于朴素的 O(4N)。
int main() {
    int n = 4;
    std::cout << "All non-empty subsets of " << n << " elements:" << std::endl;
    list_subsets(n);
    return 0;
}