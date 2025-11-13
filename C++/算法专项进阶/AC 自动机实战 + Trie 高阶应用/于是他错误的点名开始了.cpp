/*
 * 于是他错误的点名开始了 - 字典树（Trie）解法
 * 
 * 题目描述：
 * 给定n个学生姓名，然后进行m次点名
 * 对每次点名，输出：
 * - WRONG：姓名不在名单中
 * - OK：姓名在名单中且第一次被点到
 * - REPEAT：姓名在名单中但之前已经点过了
 */

#include <bits/stdc++.h>
using namespace std;

// 类型定义
typedef long long ll;
using pll = pair<ll,ll>;

// 常量定义
// 总节点数估算：所有名字总长度 ≤ 1e4*50 = 5e5
const int SIG = 26;              // 字母表大小（26个小写字母）
const int MAXNODE = 500000 + 5;  // 字典树最大节点数

// 字典树数据结构
int nxt[MAXNODE][SIG];  // nxt[u][c] = 节点u通过字符c到达的子节点编号，0表示不存在
int endCnt[MAXNODE];    // endCnt[u] = 构建时为1（标记单词结尾），查询时累加计数
int tot = 1;            // 节点计数器，根节点编号为1

/**
 * 将字符转换为数组索引
 * @param ch 小写字母字符
 * @return 对应的数组索引 (0-25)
 */
inline int idx(char ch){ 
    return ch - 'a'; 
}

/**
 * 向字典树中插入一个字符串
 * @param s 要插入的字符串
 */
inline void insertStr(const string &s){
    int u = 1;  // 从根节点开始
    
    // 遍历字符串的每个字符
    for(char ch : s){
        int c = idx(ch);  // 获取字符对应的索引
        
        // 如果不存在对应的子节点，创建新节点
        if(!nxt[u][c]) nxt[u][c] = ++tot;
        
        u = nxt[u][c];  // 移动到子节点
    }
    endCnt[u] = 1;  // 标记该节点为单词结尾，初始计数为1
}

/**
 * 查询字符串并更新计数
 * @param s 要查询的字符串
 * @return 查询后的计数值，0表示不存在
 */
inline int queryAndCount(const string &s){
    int u = 1;  // 从根节点开始
    
    // 遍历字符串的每个字符
    for(char ch : s){
        int c = idx(ch);  // 获取字符对应的索引
        
        // 如果路径不存在，返回0
        if(!nxt[u][c]) return 0;
        
        u = nxt[u][c];  // 移动到子节点
    }
    
    // 如果不是单词（endCnt[u] == 0），返回0
    if(endCnt[u] == 0) return 0;
    
    // 增加查询计数并返回
    return ++endCnt[u];
}

/**
 * 主函数
 */
int main(){
    // 优化输入输出速度
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入学生数量
    int n; 
    if(!(cin >> n)) return 0;
    
    // 读入所有学生姓名并插入字典树
    for(int i = 0; i < n; ++i){
        string w; 
        cin >> w;
        insertStr(w);  // 将姓名插入字典树
    }

    // 读入点名次数
    int m; 
    cin >> m;
    
    // 处理每次点名
    while(m--){
        string q; 
        cin >> q;
        
        // 查询姓名并获取计数
        int count = queryAndCount(q);
        
        if(count == 0){
            // 情况1：姓名不存在（路径不存在或endCnt为0）
            cout << "WRONG\n";
        }else if(count == 2){
            // 情况2：第一次被点到（构建时1 + 查询时1 = 2）
            cout << "OK\n";
        }else{
            // 情况3：重复点名（count > 2）
            cout << "REPEAT\n";
        }
    }
    
    return 0;
}
