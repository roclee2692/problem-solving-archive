/*
 * 【凸包 Convex Hull】- Graham 扫描法
 * 
 * 时间复杂度：O(n log n)
 * 空间复杂度：O(n)
 * 
 * 适用场景：
 *   - 计算凸包
 *   - 最远点对
 *   - 旋转卡壳
 *   - 最小外接圆
 * 
 * 模板题：
 *   - 洛谷 P2742 - 【模板】二维凸包
 *   - Codeforces 166B - Polygon
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const double EPS = 1e-9;

// ===== 点结构 =====
struct Point {
    ll x, y;
    
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
    
    // 向量加法
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    
    // 向量减法
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    
    // 数乘
    Point operator * (ll k) const {
        return Point(x * k, y * k);
    }
    
    // 叉积：a × b = ax * by - ay * bx
    // 几何意义：a 和 b 构成的平行四边形的有向面积
    // > 0：b 在 a 的逆时针方向
    // < 0：b 在 a 的顺时针方向
    // = 0：a 和 b 共线
    ll cross(const Point &p) const {
        return x * p.y - y * p.x;
    }
    
    // 点积：a · b = ax * bx + ay * by
    ll dot(const Point &p) const {
        return x * p.x + y * p.y;
    }
    
    // 向量长度的平方
    ll len2() const {
        return x * x + y * y;
    }
    
    // 向量长度
    double len() const {
        return sqrt(len2());
    }
};

// ===== 叉积（用于判断方向）=====
// 返回 (p1 - p0) × (p2 - p0)
// > 0：p2 在 p0p1 的左侧（逆时针）
// < 0：p2 在 p0p1 的右侧（顺时针）
// = 0：三点共线
ll cross(const Point &p0, const Point &p1, const Point &p2) {
    return (p1 - p0).cross(p2 - p0);
}

// ===== 距离的平方 =====
ll dis2(const Point &p1, const Point &p2) {
    return (p1 - p2).len2();
}

// ===== Graham 扫描法求凸包 =====
// 返回凸包上的点（逆时针顺序）
// 时间复杂度：O(n log n)
vector<Point> convexHull(vector<Point> points) {
    int n = points.size();
    if (n <= 2) return points;  // 少于 3 个点，直接返回
    
    // ===== 步骤 1：找到最左下角的点作为起点 =====
    // 为什么选最左下角？保证起点一定在凸包上
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[start].y || 
            (points[i].y == points[start].y && points[i].x < points[start].x)) {
            start = i;
        }
    }
    swap(points[0], points[start]);
    Point p0 = points[0];
    
    // ===== 步骤 2：按极角排序 =====
    // 所有点按相对于 p0 的极角从小到大排序
    // 极角相同时，距离近的在前
    // 为什么这样排序？Graham 扫描需要按逆时针顺序处理
    sort(points.begin() + 1, points.end(), [&](const Point &a, const Point &b) {
        ll c = cross(p0, a, b);
        if (c != 0) return c > 0;  // 极角小的在前（逆时针）
        return dis2(p0, a) < dis2(p0, b);  // 极角相同，距离近的在前
    });
    
    // ===== 步骤 3：Graham 扫描 =====
    // 用栈维护凸包，不断判断是否需要弹出
    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);
    
    for (int i = 2; i < n; i++) {
        // ===== 关键判断：右转则弹出 =====
        // 如果新点在栈顶两点的右侧（顺时针），说明栈顶点不在凸包上
        // 为什么？凸包的边界应该是逆时针的，右转说明凹进去了
        while (hull.size() >= 2) {
            Point p1 = hull[hull.size() - 2];
            Point p2 = hull[hull.size() - 1];
            
            // cross < 0：右转，弹出
            // cross = 0：共线，也弹出（不需要中间点）
            // cross > 0：左转，保留
            if (cross(p1, p2, points[i]) <= 0) {
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(points[i]);
    }
    
    return hull;
}

// ===== 凸包周长 =====
double perimeter(const vector<Point> &hull) {
    double per = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        per += (hull[(i + 1) % n] - hull[i]).len();
    }
    return per;
}

// ===== 凸包面积 =====
// 使用叉积计算多边形面积
// 面积 = Σ (xi * yi+1 - xi+1 * yi) / 2
double area(const vector<Point> &hull) {
    ll a = 0;
    int n = hull.size();
    for (int i = 0; i < n; i++) {
        a += hull[i].cross(hull[(i + 1) % n]);
    }
    return abs(a) / 2.0;
}

// ===== 旋转卡壳：求凸包上的最远点对 =====
// 时间复杂度：O(n)
// 核心思想：对每条边，找距离最远的顶点（单调性）
ll rotatingCalipers(const vector<Point> &hull) {
    int n = hull.size();
    if (n <= 2) return dis2(hull[0], hull[n - 1]);
    
    ll max_dis = 0;
    int j = 1;
    
    // ===== 枚举每条边 =====
    for (int i = 0; i < n; i++) {
        // ===== 旋转卡壳：找距离 i 边最远的点 =====
        // 当叉积递增时，j 继续前进
        // 叉积开始递减时，j-1 就是最远点
        while (true) {
            ll c1 = cross(hull[i], hull[(i + 1) % n], hull[j]);
            ll c2 = cross(hull[i], hull[(i + 1) % n], hull[(j + 1) % n]);
            if (c2 > c1) {
                j = (j + 1) % n;
            } else {
                break;
            }
        }
        
        // 更新最大距离
        max_dis = max(max_dis, dis2(hull[i], hull[j]));
        max_dis = max(max_dis, dis2(hull[(i + 1) % n], hull[j]));
    }
    
    return max_dis;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    // 求凸包
    vector<Point> hull = convexHull(points);
    
    // 输出凸包周长
    cout << fixed << setprecision(2) << perimeter(hull) << "\n";
    
    return 0;
}

/*
 * ========== 凸包核心原理 ==========
 * 
 * 【什么是凸包？】
 * - 包含所有点的最小凸多边形
 * - 直观理解：用橡皮筋套住所有点，橡皮筋的形状就是凸包
 * 
 * 【凸多边形的性质】
 * - 任意两点的连线都在多边形内部
 * - 所有内角 < 180°
 * - 边界上任意三个连续点都是逆时针（或顺时针）
 * 
 * 【Graham 扫描法】
 * 核心思想：
 * 1. 找起点（最左下角的点）
 * 2. 按极角排序（相对于起点的角度）
 * 3. 用栈维护凸包，遇到"右转"就弹出
 * 
 * 【为什么 Graham 扫描法正确？】
 * - 按极角排序后，凸包上的点按逆时针顺序排列
 * - 如果出现"右转"，说明中间的点在内部，不在凸包上
 * - 栈保证了凸包的凸性（所有转折都是左转）
 * 
 * 【叉积的几何意义】
 * (p1 - p0) × (p2 - p0) 的符号：
 * - > 0：p2 在 p0p1 的左侧（逆时针，左转）
 * - < 0：p2 在 p0p1 的右侧（顺时针，右转）
 * - = 0：三点共线
 * 
 * 大小：平行四边形的有向面积
 * 
 * 【凸包算法对比】
 * 
 * | 算法 | 复杂度 | 特点 |
 * |------|--------|------|
 * | Graham 扫描 | O(n log n) | 实现简单，最常用 |
 * | Andrew 算法 | O(n log n) | 分别求上下凸包 |
 * | Jarvis 步进 | O(nh) | h 是凸包点数，适合 h 很小 |
 * | 增量法 | O(n log n) | 动态维护凸包 |
 * 
 * 【旋转卡壳】
 * - 用途：求凸包上的最远点对、最小外接矩形等
 * - 核心思想：对每条边，找距离最远的顶点（利用单调性）
 * - 复杂度：O(n)（线性扫描）
 * 
 * 【凸包的经典应用】
 * 
 * 1. **最远点对**
 *    - 最远点对一定在凸包上
 *    - 用旋转卡壳 O(n)
 * 
 * 2. **最小外接圆**
 *    - 圆心在凸包内或凸包边上
 *    - 随机增量法 O(n)
 * 
 * 3. **最小外接矩形**
 *    - 矩形的一条边与凸包的某条边平行
 *    - 旋转卡壳 O(n)
 * 
 * 4. **点是否在多边形内**
 *    - 先判断是否在凸包内
 *    - 射线法或叉积法
 * 
 * 【点积和叉积】
 * 
 * 点积 a · b = |a| * |b| * cos(θ)
 * - 判断角度：> 0 锐角，= 0 垂直，< 0 钝角
 * 
 * 叉积 a × b = |a| * |b| * sin(θ)
 * - 判断方向：> 0 逆时针，< 0 顺时针，= 0 共线
 * - 计算面积：平行四边形面积 = |a × b|
 * 
 * 【常见错误】
 * 1. 排序时没有处理共线情况
 * 2. 弹栈条件错误（应该 <= 0，不是 < 0）
 * 3. 忘记处理 n ≤ 2 的情况
 * 4. 叉积溢出（用 ll）
 * 5. 浮点数精度问题
 * 
 * 【调试技巧】
 * 1. 画图验证：小数据（4-5个点）手动画凸包
 * 2. 检查排序：打印排序后的点，看是否按极角排列
 * 3. 检查弹栈：打印每次弹栈的原因（右转/共线）
 * 4. 特殊情况：所有点共线、所有点相同
 * 
 * 【精度处理】
 * 1. 坐标用整数（ll）避免精度问题
 * 2. 只有最后计算周长/面积时用 double
 * 3. 比较时用 EPS：abs(x) < EPS 判断为 0
 * 
 * 【提交前检查】
 * ✓ 处理 n ≤ 2 的情况
 * ✓ 排序时处理共线和距离
 * ✓ 弹栈条件：cross <= 0
 * ✓ 叉积用 ll 防溢出
 * ✓ 输出格式（小数位数）
 * 
 * 【优化技巧】
 * 1. 去重：排序后去除重复点
 * 2. 共线点：只保留最远的
 * 3. 预分配内存：hull.reserve(n)
 * 
 * 【竞赛考察频率】
 * - NOI/省选：⭐⭐⭐⭐（计算几何专题）
 * - ICPC/CCPC：⭐⭐⭐（区域赛常考）
 * - Codeforces：⭐⭐（Div1 D/E）
 * 
 * 【推荐练习】
 * 1. 洛谷 P2742 - 二维凸包模板
 * 2. POJ 1113 - Wall（凸包 + 圆）
 * 3. POJ 2187 - Beauty Contest（最远点对）
 * 4. HDU 3934 - Merry X'mas（凸包应用）
 */
