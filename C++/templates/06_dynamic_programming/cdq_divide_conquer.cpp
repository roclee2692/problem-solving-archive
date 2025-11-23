/*
 * 【CDQ 分治】- 三维偏序问题
 * 
 * 时间复杂度：O(n log² n)
 * 空间复杂度：O(n log n)
 * 
 * 适用场景：
 *   - 三维偏序统计
 *   - 动态逆序对
 *   - 带修改的区间查询
 *   - 二维数点
 * 
 * 模板题：
 *   - 洛谷 P3810 - 【模板】三维偏序（陌上花开）
 *   - Codeforces 688E - Maximal GCD
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 5;

// ===== 三维点结构 =====
struct Point {
    int a, b, c;    // 三个维度的值
    int cnt;        // 相同点的个数（去重优化）
    int ans;        // 答案：有多少个点三维都 ≤ 它
    
    bool operator < (const Point &p) const {
        if (a != p.a) return a < p.a;
        if (b != p.b) return b < p.b;
        return c < p.c;
    }
    
    bool operator == (const Point &p) const {
        return a == p.a && b == p.b && c == p.c;
    }
};

Point p[MAXN], tmp[MAXN];  // 原数组和临时数组
int n, k;
int ans[MAXN];  // ans[i] = 有 i 个点三维都 ≤ 它的点数

// ===== 树状数组（维护第三维）=====
// 为什么用树状数组？因为需要快速查询前缀和（第三维的累计）
struct BIT {
    int c[MAXN];
    int maxn;
    
    void init(int n) {
        maxn = n;
        fill(c, c + n + 1, 0);
    }
    
    int lowbit(int x) {
        return x & (-x);
    }
    
    void add(int x, int val) {
        while (x <= maxn) {
            c[x] += val;
            x += lowbit(x);
        }
    }
    
    int query(int x) {
        int res = 0;
        while (x > 0) {
            res += c[x];
            x -= lowbit(x);
        }
        return res;
    }
} bit;

// ===== CDQ 分治：处理区间 [l, r] =====
// 核心思想：
// 1. 分治：[l, mid] 和 [mid+1, r]
// 2. 统计：[l, mid] 对 [mid+1, r] 的贡献
// 3. 合并：归并排序，保证第二维有序
void cdq(int l, int r) {
    if (l >= r) return;
    
    int mid = (l + r) / 2;
    
    // ===== 步骤 1：递归处理左右两部分 =====
    cdq(l, mid);
    cdq(mid + 1, r);
    
    // ===== 步骤 2：统计左半部分对右半部分的贡献 =====
    // 核心思想：
    // - 第一维已经排好序（递归前保证）
    // - 现在按第二维归并排序
    // - 用树状数组维护第三维
    
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        // ===== 归并排序（按第二维）=====
        if (p[i].b <= p[j].b) {
            // 左半部分的点 i，它的第三维对右半部分有贡献
            // 把 p[i].c 加入树状数组
            bit.add(p[i].c, p[i].cnt);
            tmp[k++] = p[i++];
        } else {
            // 右半部分的点 j，查询有多少左半部分的点三维都 ≤ j
            // 条件：p[i].a ≤ p[j].a（因为 i ≤ mid < j，第一维已排序）
            //       p[i].b ≤ p[j].b（归并保证）
            //       p[i].c ≤ p[j].c（树状数组查询）
            p[j].ans += bit.query(p[j].c);
            tmp[k++] = p[j++];
        }
    }
    
    // ===== 处理剩余的点 =====
    while (j <= r) {
        p[j].ans += bit.query(p[j].c);
        tmp[k++] = p[j++];
    }
    while (i <= mid) {
        bit.add(p[i].c, p[i].cnt);
        tmp[k++] = p[i++];
    }
    
    // ===== 清空树状数组（重要！）=====
    for (int i = l; i <= mid; i++) {
        bit.add(p[i].c, -p[i].cnt);
    }
    
    // ===== 步骤 3：复制回原数组 =====
    for (int i = l; i <= r; i++) {
        p[i] = tmp[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    // ===== 读入数据 =====
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].a >> points[i].b >> points[i].c;
        points[i].cnt = 1;
        points[i].ans = 0;
    }
    
    // ===== 去重优化 =====
    // 相同的点合并，cnt 记录个数
    // 为什么去重？避免重复计算，优化常数
    sort(points.begin(), points.end());
    int m = 0;
    for (int i = 0; i < n; i++) {
        if (m == 0 || !(points[i] == p[m])) {
            p[++m] = points[i];
        } else {
            p[m].cnt++;
        }
    }
    
    // ===== 初始化树状数组 =====
    bit.init(k);
    
    // ===== CDQ 分治 =====
    cdq(1, m);
    
    // ===== 统计答案 =====
    // ans[i] = 有多少个点被 i 个点支配（三维都 ≤ 它）
    for (int i = 1; i <= m; i++) {
        // p[i].ans：有多少个不同的点三维都 ≤ p[i]
        // 加上 p[i].cnt - 1：相同的点也算
        ans[p[i].ans + p[i].cnt - 1] += p[i].cnt;
    }
    
    // ===== 输出 =====
    for (int i = 0; i < n; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}

/*
 * ========== CDQ 分治核心原理 ==========
 * 
 * 【什么是 CDQ 分治？】
 * - 一种离线算法，用于解决带偏序关系的统计问题
 * - 核心思想：分治 + 归并，利用偏序关系减少重复计算
 * - 命名来源：陈丹琪（CDQ），中国 OI 选手
 * 
 * 【三维偏序问题】
 * 给定 n 个三维点 (a, b, c)，对每个点统计有多少个点满足：
 * - a' ≤ a
 * - b' ≤ b
 * - c' ≤ c
 * 
 * 暴力：O(n²)
 * CDQ 分治：O(n log² n)
 * 
 * 【核心思想】
 * 三个维度分别处理：
 * 1. 第一维：排序（预处理）
 * 2. 第二维：归并排序（分治过程中）
 * 3. 第三维：树状数组（维护动态前缀和）
 * 
 * 【CDQ 分治的三个步骤】
 * 1. **分治**：递归处理 [l, mid] 和 [mid+1, r]
 * 2. **统计**：计算左半部分对右半部分的贡献
 * 3. **合并**：归并排序（按第二维）
 * 
 * 【为什么要归并排序？】
 * - 保证第二维有序
 * - 左半部分的点按第二维遍历时，可以及时更新树状数组
 * - 右半部分的点查询时，保证左边所有 b ≤ 当前点的 b 的点都已加入
 * 
 * 【为什么用树状数组？】
 * - 需要动态维护第三维的前缀和
 * - 查询：有多少个点的 c ≤ 当前点的 c
 * - 单点修改 + 区间查询，树状数组最合适
 * 
 * 【CDQ 分治的适用条件】
 * 1. 离线算法（所有询问已知）
 * 2. 偏序关系（可以分治）
 * 3. 贡献可以合并（加法）
 * 
 * 【CDQ 分治的经典应用】
 * 
 * 1. **三维偏序（陌上花开）**
 *    - 本模板的问题
 * 
 * 2. **动态逆序对**
 *    - 支持删除元素，查询当前逆序对数
 *    - 转化为三维偏序：(时间, 位置, 值)
 * 
 * 3. **二维数点**
 *    - 查询矩形内有多少个点
 *    - 转化为二维偏序
 * 
 * 4. **带修改的区间查询**
 *    - 支持区间加、单点查询
 *    - CDQ 分治优化
 * 
 * 【复杂度分析】
 * - 递归深度：O(log n)
 * - 每层：
 *   - 归并排序：O(n)
 *   - 树状数组操作：O(n log k)（k 是第三维范围）
 * - 总复杂度：O(n log n * log k) ≈ O(n log² n)
 * 
 * 【去重优化】
 * - 相同的点合并，用 cnt 记录个数
 * - 优化常数，避免重复计算
 * - 最后统计答案时要加上 cnt - 1
 * 
 * 【为什么要清空树状数组？】
 * - 每次统计完左半部分对右半部分的贡献后，要清空
 * - 否则会影响下一次递归的结果
 * - 清空方法：bit.add(p[i].c, -p[i].cnt)
 * 
 * 【CDQ 分治 vs 其他算法】
 * 
 * | 算法 | 复杂度 | 在线/离线 | 适用场景 |
 * |------|--------|-----------|----------|
 * | 暴力 | O(n²) | 在线 | n ≤ 5000 |
 * | CDQ 分治 | O(n log² n) | 离线 | 偏序统计 |
 * | K-D Tree | O(n log n) | 在线 | 多维查询 |
 * | 树套树 | O(n log² n) | 在线 | 动态维护 |
 * 
 * 【常见错误】
 * 1. 忘记清空树状数组
 * 2. 归并排序写错（第二维不有序）
 * 3. 去重后忘记更新 n（应该用 m）
 * 4. ans 统计时忘记加 cnt - 1
 * 5. 树状数组下标从 0 开始（应该从 1）
 * 
 * 【调试技巧】
 * 1. 小数据验证：n = 5，手动模拟分治过程
 * 2. 检查归并：打印每次归并后的数组，看第二维是否有序
 * 3. 检查树状数组：打印每次 add 和 query 的值
 * 4. 特殊情况：所有点相同、所有点第一维相同
 * 
 * 【提交前检查】
 * ✓ 清空树状数组
 * ✓ 归并排序正确
 * ✓ 去重后用 m 而不是 n
 * ✓ ans 统计加 cnt - 1
 * ✓ 树状数组下标从 1 开始
 * ✓ 数组大小足够
 * 
 * 【扩展：四维及以上偏序】
 * - 三维偏序：CDQ 分治 + 树状数组
 * - 四维偏序：CDQ 套 CDQ
 * - 复杂度：O(n log³ n)
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐⭐（必会！）
 * - ICPC/CCPC：⭐⭐⭐（区域赛及以上）
 * - Codeforces：⭐⭐（Div1 E/F）
 * 
 * 【推荐练习】
 * 1. 洛谷 P3810 - 三维偏序（陌上花开）
 * 2. 洛谷 P1975 - 动态逆序对
 * 3. BZOJ 3262 - 陌上花开（加强版）
 * 4. Codeforces 629D - Babaei and Birthday Cake
 * 
 * 【学习建议】
 * 1. 先理解分治思想
 * 2. 掌握归并排序
 * 3. 熟练树状数组
 * 4. 画图模拟小数据
 * 5. 多做练习题
 */
