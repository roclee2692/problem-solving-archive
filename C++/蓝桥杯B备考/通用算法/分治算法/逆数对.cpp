#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

// merge函数：合并已排序的左右区间，并统计逆序对数量
// 参数说明：
//   a：待排序数组
//   l：左区间起始索引
//   m：左右区间分界索引（左区间：l~m，右区间：m+1~r）
//   r：右区间结束索引
ll merge(vector<int> &a, int l, int m, int r) {//排序函数
    vector<int> t(r - l + 1);  // 临时数组，用于存放合并后的有序序列
    int i = l, j = m + 1, k = 0;
    ll c = 0;  // 记录逆序对数量  使用long long防止数据溢出

    // 归并过程：比较左右两个区间的元素，按升序合并到临时数组t中
    while (i <= m && j <= r) {
        if (a[i] <= a[j]) {
            t[k++] = a[i++];  // 左区间元素较小，直接放入t
        } else {
            t[k++] = a[j++];  // 右区间元素较小，放入t
            // 由于a[i] > a[j]，且左区间[a[i], ..., a[m]]均大于a[j]，故累加逆序对数：数量为(m - i + 1)
            c += (m - i + 1);//同运算级有无（）均可  是i不是l！！ 归并每次选最小的放前，为升序
        }
    }

    // 处理剩余的元素
    while (i <= m) t[k++] = a[i++];
    while (j <= r) t[k++] = a[j++];

    // 将临时数组t复制回原数组的对应位置
    for (i = l, k = 0; i <= r; i++, k++) {
        a[i] = t[k];
    }
    return c;
}

// msort函数：利用归并排序思想，对数组区间[l, r]排序并统计逆序对
ll msort(vector<int> &a, int l, int r) {
    if (l >= r) return 0;  // 递归终止条件：区间只有一个元素时没有逆序对
    int m = (l + r) / 2;   // 求中点，拆分左右区间
    // 递归排序左右区间，并合并统计逆序对数量
    return msort(a, l, m) + msort(a, m + 1, r) + merge(a, l, m, r);//分治的核心
// 依次递归，等左区间得出总共的逆数对数量后再递归右区间，最后再一次排序并计算左右大区间的逆数对数量
}//再相加，得出总数  这是每次递归的一个最小单元

int main(){
    int n;
    cin >> n;  // 输入数组元素个数
    vector<int> a(n);
    // 输入数组元素
    for (auto &x : a)
        cin >> x;
    // 调用msort函数统计并输出逆序对数量
    cout << msort(a, 0, n - 1) << "\n";
    return 0;
}
