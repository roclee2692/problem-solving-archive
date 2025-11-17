#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = (ll)1e18;

int n, m, u, v, s, t;
vector<vector<pair<int, ll>>> G, rG;
vector<ll> dist_u, dist_to_v, dist_s, dist_to_t;

// 在 graph 上从 start 出发做 Dijkstra，把最短距离写入 dist[]
void dijkstra(int start, vector<ll> &dist, const vector<vector<pair<int, ll>>> &graph) {
    // 初始化
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    // 小根堆：pair<距离, 顶点>
    priority_queue< pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > pq;
    dist[start] = 0;
    pq.push(make_pair(0LL, start));

    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();
        ll d = cur.first;
        int x = cur.second;
        if (d > dist[x]) continue;  // 避免过时条目

        // 松弛所有邻边
        for (size_t i = 0; i < graph[x].size(); i++) {
            int to = graph[x][i].first;
            ll w = graph[x][i].second;
            if (dist[to] > d + w) {
                dist[to] = d + w;
                pq.push(make_pair(dist[to], to));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> u >> v >> s >> t;

    G.resize(n + 1);
    rG.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        ll w;
        cin >> a >> b >> w;
        G[a].push_back(make_pair(b, w));
        rG[b].push_back(make_pair(a, w));  // 反向图：把 (a->b, w) 存成 (b->a, w)
    }

    // 分别存储 4 次 Dijkstra 的结果
    dist_u.resize(n + 1);
    dist_to_v.resize(n + 1);
    dist_s.resize(n + 1);
    dist_to_t.resize(n + 1);

    // 1) dist_u[x] = 从 u 到 x 的最短距离（在正向图 G 上跑）
    dijkstra(u, dist_u, G);
    // 2) dist_to_v[x] = 从 x 到 v 的最短距离（在反向图 rG 上跑，以 v 为起点）
    dijkstra(v, dist_to_v, rG);

    // 3) dist_s[x] = 从 s 到 x 的最短距离（在正向图 G 上跑）
    dijkstra(s, dist_s, G);
    // 4) dist_to_t[x] = 从 x 到 t 的最短距离（在反向图 rG 上跑，以 t 为起点）
    dijkstra(t, dist_to_t, rG);

    // 如果 u->v 或 s->t 无法连接，则直接无交点
    if (dist_u[v] == INF || dist_s[t] == INF) {
        cout << "No Intersection\n";
        return 0;
    }

    vector<int> answer;
    // 枚举每个顶点 w，看是否同时属于 u->v 的某条最短路和 s->t 的某条最短路
    for (int w = 1; w <= n; w++) {
        // 检查 w 是否在 u->v 的一条最短路径上：
        //   1. u->w 存在，w->v 存在
        //   2. dist_u[w] + dist_to_v[w] == dist_u[v]
        if (dist_u[w] == INF || dist_to_v[w] == INF) continue;
        if (dist_u[w] + dist_to_v[w] != dist_u[v]) continue;

        // 检查 w 是否在 s->t 的一条最短路径上：
        //   1. s->w 存在，w->t 存在
        //   2. dist_s[w] + dist_to_t[w] == dist_s[t]
        if (dist_s[w] == INF || dist_to_t[w] == INF) continue;
        if (dist_s[w] + dist_to_t[w] != dist_s[t]) continue;

        answer.push_back(w);
    }

    if (answer.empty()) {
        cout << "No Intersection\n";
    } else {
        // 枚举时已经是按 w 从 1 到 n 的顺序，因此自然有序
        for (size_t i = 0; i < answer.size(); i++) {
            if (i > 0) cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }

    return 0;
}
