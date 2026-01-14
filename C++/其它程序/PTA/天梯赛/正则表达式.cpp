#include <regex>    // 引入正则表达式库
#include <string>   // 引入 std::string
#include <vector>   // 引入 std::vector
#include <iostream> // 为了演示，我们也会打印结果

using namespace std;

// 函数：把算式拆成一个个 token，返回一个字符串列表
vector<string> tokenize_regex(const string &expr) {
    vector<string> tokens;  // 最终要返回的列表

    // 1. 定义一个“正则表达式对象”
    //    R"( ... )" 是 C++ 原生字符串（raw string literal），可以省去对 \ 的额外转义
    //    匹配规则：(\\d+) 或 ([+\\-*/()])
    //      \\d+    —— 一个或多个数字
    //      [+\\-*/()] —— 一个加号 或 减号 或 乘号 或 除号 或 左右括号
    static const regex re(R"((\d+|[+\-*/()]))");

    // 2. 创建正则匹配迭代器  —— 会在 expr 中，找出所有符合 re 模式的子串
    auto begin_it = sregex_iterator(expr.begin(), expr.end(), re);
    auto   end_it = sregex_iterator();  // 默认构造表示“迭代结束”

    // 3. 依次遍历每个匹配结果
    for (auto it = begin_it; it != end_it; ++it) {
        smatch match = *it;          // *it 得到一个 smatch 对象，代表一次完整匹配
        tokens.push_back(match.str()); // 把匹配到的字符串（数字或符号）加进列表
    }

    return tokens;
}

int main() {
    // 示例算式
    string expr = "12+34*(56-7)";

    // 拆分
    vector<string> tok = tokenize_regex(expr);

    // 打印结果
    cout << "拆分后的 token 列表：\n";
    for (auto &s : tok) {
        cout << "[" << s << "]\n";
    }
    return 0;
}
