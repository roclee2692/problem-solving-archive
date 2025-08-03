#include <bits/stdc++.h>
using namespace std;

/* ========== ① 边结点结构 ==========
   单链表节点，存：终点编号 to、权重 w、下一条边指针 next        */
struct Edge {
    int  to;           // 终点顶点编号
    int  w;            // 权重
    Edge* next;        // 下一条边
    Edge(int t, int wt, Edge* n) : to(t), w(wt), next(n) {}
};

/* ========== ② 顶点结构 ==========
   每个顶点存：info 字符、head 指向该顶点出边链表头          */
struct Vertex {
    char  info;        // 顶点字符
    Edge* head = nullptr;
};

/* ========== ③ 图结构 ==========
   Vn 顶点数  En 边数  V 顶点数组                          */
struct Graph {
    int Vn, En;
    vector<Vertex> V;  // 大小 = 当前顶点数

    /* ---------- 构造：读入并建图（头插法） ---------- */
    Graph() {
        int kMax, m;
        cin >> kMax >> Vn >> m;
        En = m;
        V.resize(Vn);
        for (int i = 0; i < Vn; ++i) cin >> V[i].info;

        while (m--) {
            int u, v, w; cin >> u >> v >> w;
            /* 头插：新边 e 指向旧链表头，再把顶点 u 的 head 改成 e
               时间 O(1)，且满足题目 “最后输入的成为链头” 规则        */
            V[u].head = new Edge(v, w, V[u].head);
        }//这里的 V[u].head指的是指针的作用域=使它指向边节点，
        //边中的V[u].head，是未更新指针作用域之前指向的具体对象，
        //首次代指空指针，以后代指除此顶点之外的所有边链表
    }

    // 插入边（头插法）：
// 假设插入从顶点 2 出发的三条边：
//     2 -> 0 权重2
//     2 -> 3 权重1
//     2 -> 4 权重2
//
// 每次插入一条边 e = new Edge(v, w, head)，都将其接在链表前面，形成如下结构：
//
// 第一步插入边 2→0：
//     V[2].head ─? [0:2 | next=null]
//
// 第二步插入边 2→3：
//     V[2].head ─? [3:1] ─? [0:2] ─? null
//
// 第三步插入边 2→4：
//     V[2].head ─? [4:2] ─? [3:1] ─? [0:2] ─? null
//
// 最终：
//     - V[2].head 永远指向“最新插入的边”
//     - 每个 Edge 结点通过 next 指向下一个邻接点
//     - 遍历从 V[2].head 开始，一直 p = p->next 即可访问所有出边

// 指针赋值：左边决定“谁来指向”，右边提供“指向哪里的地址”。
//A = B 的意思是：让 A 指向 B 当前所指向的那个对象。

//cur->to 表示：“通过指针 cur，访问它所指向的结构体对象中的成员变量 to。”
//cur->to    ≡    (*cur).to
//也就是先解引用 *cur 拿到对象，然后用 . 访问成员。

//. 是访问结构体对象的成员，-> 是访问结构体指针的成员。

    /* ---------- 打印邻接表 ---------- */
    void print() const {
        cout << "邻接表为：\n";
        for (int i = 0; i < Vn; ++i) {
            cout << "list[" << i << "]";
            for (Edge* p = V[i].head; p; p = p->next)
                cout << "->" << p->to << ":" << p->w;
            cout << "->end\n";
        }
    }

    /* ---------- 边存在性 ---------- */
    bool hasEdge(int u, int v) const {
        for (Edge* p = V[u].head; p; p = p->next)
            if (p->to == v) return true;
        return false;
    }

    /* ---------- 第一个邻接点 ---------- */
    int firstAdj(int v) const { return V[v].head ? V[v].head->to : -1; }

    /* ---------- 删除顶点 v 及其相关边 ---------- */
    void removeVertex(int v) {
        char oldInfo = V[v].info;     // 先记录要打印的字符
        int  delCnt  = 0;             // 统计被删边条数

        /* 1) 遍历所有链，：
              - 删掉“从 i 出发指向 v” 的边
              - 删掉“i==v 这整条链”（v 的出边）
              - 把指向末尾顶点 (Vn-1) 的边改成指向 v
           用 Edge** pp （指针的指针）删链，能同时处理头结点   */
        for (int i = 0; i < Vn; ++i) {
            Edge** pp = &V[i].head;
 // 指针的指针（Edge**）能修改当前链指针的指向，不论它是 head 还是 next，实现链表结构的灵活重接。
 //而一旦你使用单个指针就是重新分配了一次内存，无法再修改原hand指针
            while (*pp) {
                Edge* cur = *pp;
                bool del = (i == v) || (cur->to == v);
                if (del) {                   // 删除当前结点
                    *pp = cur->next;//同时解决了出边和入边！！！
                    delete cur;//释放内存
                    ++delCnt;
                } else {//不删的情况，检查是否指向最后一个顶点
                    if (cur->to == Vn - 1) 
                        cur->to = v;// 指向末尾顶点即空节点 → 改成指向 v
                    pp = &cur->next;    // 前进  继续检查下一条边 我们要找到未节点才为止
                }
            }
    }
        /* 2) 用末尾顶点覆盖 v（若 v 不是最后一个） */
        if (v != Vn - 1) {
            V[v].info = V[Vn - 1].info;
            // info 是顶点的字符信息，仅拷贝一个 char，和邻接表无关。
            V[v].head = V[Vn - 1].head;//我们只需要将顶点的编号更新一下即可，后面的顶点会由指针直接指过去
        }
        V.pop_back();
        Vn--;
        En -= delCnt;

        cout << "待删除的顶点信息为 " << oldInfo << "\n";
    }
};

/* ========== ④ 主流程 ========== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Graph g;                                 // 读图
    g.print();
    cout << "顶点数 = " << g.Vn << '\n';

    for (int i = 0; i < 2; ++i) {            // 边存在性查询
        int u, v; cin >> u >> v;
        cout << '<' << u << ", " << v << "> 的存在性 = "
             << g.hasEdge(u, v) << '\n';
    }

    int q; cin >> q;                         // 第一个邻接点
    cout << "顶点" << q << "的第一个邻接点 = "
         << g.firstAdj(q) << '\n';

    int del; cin >> del;                     // 删顶点
    g.removeVertex(del);

    /* 输出删除后的图 */
    cout << "当前顶点数 = " << g.Vn << '\n';
    cout << "当前边数 = " << g.En << '\n';
    for (auto& vtx : g.V) cout << vtx.info;  cout << '\n';
    g.print();
    return 0;
}
