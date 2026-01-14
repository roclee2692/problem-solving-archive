// ========================================
// 【学习笔记-第3步】高级功能练习
// ========================================
// 目标：掌握完整系统中你还不会的核心知识点
// 时间：2-3小时
// 前置：已完成第2步的5个基础任务

// ========================================
// 【系统架构图】教师科研工作量管理系统
// ========================================
/*
┌─────────────────────────────────────────────────────────┐
│                    教师科研工作量管理系统                    │
├─────────────────────────────────────────────────────────┤
│  第1层：数据结构 (你已掌握 Apply，新增 College + User)      │
│    struct College { cid, name }                         │
│    struct User    { uid, cid, name, password, role }    │
│    struct Apply   { aid, type, uid, year, ... }         │
├─────────────────────────────────────────────────────────┤
│  第2层：工具函数 (新知识点！)                               │
│    ① splitByBar() - 字符串分割（替代手动解析）               │
│    ② trim()       - 去除首尾空格                           │
│    ③ findXxxIdx() - 查找索引（封装线性查找）                │
│    ④ calcScore()  - 自动计分规则（策略模式）                │
├─────────────────────────────────────────────────────────┤
│  第3层：文件读写 (你已会单文件，新增3文件联合管理)            │
│    ① loadColleges()   ← colleges.txt                   │
│    ② loadUsers()      ← users.txt                      │
│    ③ loadApplies()    ← applies.txt                    │
│    ④ loadAll()        ← 按顺序加载（处理外键关系）          │
│    ⑤ saveAll()        ← 统一保存                         │
├─────────────────────────────────────────────────────────┤
│  第4层：业务功能                                            │
│    教师端：submitPaper/Project/Fund (你已掌握submitPaper)  │
│    管理端：reviewOne (你已掌握基础审核)                     │
│           addCollege/delCollege/editCollege (CRUD ★)    │
│           addUser/delUser/editUser (CRUD ★)             │
├─────────────────────────────────────────────────────────┤
│  第5层：统计查询 (新知识点！高级)                           │
│    ① statsTeacher()  - unordered_map 汇总 + sort 排序    │
│    ② statsCollege()  - 按学院汇总                         │
├─────────────────────────────────────────────────────────┤
│  第6层：菜单系统                                            │
│    teacherMenu() / adminMenu() - while循环 + switch     │
└─────────────────────────────────────────────────────────┘
*/

// ========================================
// 【核心新知识点提取】共8个重点
// ========================================
/*
┌──────────┬─────────────────────────┬──────────────┐
│ 优先级    │ 知识点                   │ 难度 & 时间  │
├──────────┼─────────────────────────┼──────────────┤
│ ★★★★★ │ ① splitByBar 字符串分割   │ 中 / 20分钟  │
│ ★★★★★ │ ② CRUD 增删改查模式       │ 中 / 30分钟  │
│ ★★★★★ │ ③ unordered_map 统计汇总 │ 高 / 40分钟  │
│ ★★★★★ │ ④ sort + lambda 排序     │ 中 / 20分钟  │
│ ★★★☆☆ │ ⑤ trim 去除空格          │ 低 / 10分钟  │
│ ★★★☆☆ │ ⑥ function<> 回调函数    │ 中 / 15分钟  │
│ ★★☆☆☆ │ ⑦ numeric_limits 清缓冲  │ 低 / 5分钟   │
│ ★★☆☆☆ │ ⑧ 策略模式 计分规则       │ 中 / 20分钟  │
└──────────┴─────────────────────────┴──────────────┘
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;

// ========================================
// 【知识点1】splitByBar - 字符串分割
// ========================================
// 问题：你之前用的 stringstream + getline(ss, temp, '|')
//       但如果要封装成工具函数，怎么写？
// 
// 应用场景：解析文件每一行
//   "1|2|3|hello|world" → ["1", "2", "3", "hello", "world"]

// 【TODO】请你手写实现
vector<string> splitByBar(const string &s) {
    // 提示1：创建空 vector<string> 和临时字符串 cur
    // 提示2：遍历字符串 s，遇到 '|' 就 push cur 并清空
    // 提示3：别忘了最后一个字段（没有结尾的 '|'）
    
    // 你的代码写在这里：
    vector<string> result;
    stringstream ss(s);
    string temp;
    while(getline(ss,temp,'|')){
        result.push_back(temp);
    }
    return result; 
}

// 测试用例
void test_splitByBar() {
    cout << "\n====== 测试 splitByBar ======\n";
    
    string line = "101|张三|123|teacher|0";
    vector<string> parts = splitByBar(line);
    
    cout << "原始字符串: " << line << endl;
    cout << "分割结果(" << parts.size() << "个): ";
    for (auto &p : parts) {
        cout << "[" << p << "] ";
    }
    cout << endl;
    
    // 预期输出：[101] [张三] [123] [teacher] [0]
}


// ========================================
// 【知识点2】trim - 去除首尾空格
// ========================================
// 问题：读取文件时，可能有 "  hello  \n" 这样的脏数据
// 需要去掉前后空格/换行符，保留中间内容

// 【TODO】请你手写实现
string trim(const string &s) {
    // 提示1：定义左右指针 l=0, r=s.size()-1
    // 提示2：while(l<=r && isspace(s[l])) l++;
    // 提示3：while(l<=r && isspace(s[r])) r--;
    // 提示4：return s.substr(l, r-l+1);
    
    // 你的代码写在这里：
    int l=0,r=s.size()-1;
    while(l<=r && isspace(s[l])) l++;
    while(l<=r && isspace(s[r])) r--;
    return s.substr(l,r-l+1);
    
}

void test_trim() {
    cout << "\n====== 测试 trim ======\n";
    
    string dirty = "  hello world  \n";
    string clean = trim(dirty);
    
    cout << "原始: [" << dirty << "]" << endl;
    cout << "清理: [" << clean << "]" << endl;
    
    // 预期输出：[hello world]
}


// ========================================
// 【知识点3】CRUD 增删改查模式
// ========================================
// 以学院管理为例，演示增删改查的标准写法

struct College {
    int cid;
    string name;
};

vector<College> colleges;

// -------- 查找工具函数 --------
int findCollegeIdx(int cid) {
    for (int i = 0; i < colleges.size(); i++) {
        if (colleges[i].cid == cid) return i;
    }
    return -1;  // 未找到
}

// -------- 增 (Create) --------
void addCollege() {
    College c;
    cout << "输入学院ID: "; cin >> c.cid;
    
    // 检查是否已存在
    if (findCollegeIdx(c.cid) != -1) {
        cout << "学院ID已存在！\n";
        return;
    }
    
    cout << "输入学院名称: ";
    cin.ignore();//清除缓冲区中的换行符
    getline(cin, c.name);
    
    colleges.push_back(c);
    cout << "添加成功！\n";
}

// -------- 删 (Delete) --------
void delCollege() {
    int cid;
    cout << "输入要删除的学院ID: "; cin >> cid;
    
    int idx = findCollegeIdx(cid);
    if (idx == -1) {
        cout << "学院不存在！\n";
        return;
    }
    
    // 【删除方法1】用 erase
    colleges.erase(colleges.begin() + idx);
    cout << "删除成功！\n";
    
    // 【删除方法2】交换到末尾再pop（更快，但不保证顺序）
    // colleges[idx] = colleges.back();
    // colleges.pop_back();
}

// -------- 改 (Update) --------
// 【TODO】请你手写实现
void editCollege() {
    // 提示1：输入要修改的 cid
    // 提示2：findCollegeIdx 找到索引
    // 提示3：提示用户输入新名称
    // 提示4：colleges[idx].name = 新名称
    
    // 你的代码写在这里：
    cout << "请输入要修改的cid: ";
    int cid;
    cin >> cid;
    
    int idx = findCollegeIdx(cid);
    if (idx == -1) {
        cout << "该学院不存在！\n";
        return;  // 找不到就退出
    }
    
    cout << "请输入新名称: ";
    cin.ignore();  // ← 关键！清除缓冲区
    getline(cin, colleges[idx].name);
    cout << "修改成功！\n";
    
}

// -------- 查 (Read) --------
void showColleges() {
    cout << "\n====== 学院列表 ======\n";
    cout << "ID\t名称\n";
    cout << "--------------------\n";
    for (auto &c : colleges) {
        cout << c.cid << "\t" << c.name << "\n";
    }
    cout << "--------------------\n";
}


// ========================================
// 【知识点4】unordered_map 统计汇总
// ========================================
// 场景：统计每个教师的总分
// 数据：多条申报记录，按 uid 分组求和

struct Apply {
    int aid;
    int uid;      // 教师工号
    double score; // 分数
    int status;   // 0待审核 1通过 2驳回
};

vector<Apply> applies;

// 【TODO】请你手写实现
void statsTeacherScore() {
    // 需求：统计每个教师通过的申请总分，并按总分降序排序
    
    // 提示1：unordered_map<int, double> scoreMap;
    // 提示2：遍历 applies，if (status==1) scoreMap[uid] += score;
    // 提示3：把 map 转成 vector<pair<uid, score>>
    // 提示4：sort 排序（降序）
    // 提示5：输出结果
    
    // 你的代码写在这里：
    // 第1步：统计每个教师的总分
    unordered_map<int, double> scoreMap;
    for (auto &a : applies) {  // ← 用引用避免拷贝
        if (a.status == 1) {   // 只统计通过的
            scoreMap[a.uid] += a.score;
        }
    }
    
    // 第2步：转成 vector 方便排序
    vector<pair<int, double>> vec;
    for (auto &kv : scoreMap) {  // ← 遍历 map，不是 applies！
        vec.push_back({kv.first, kv.second});  // {uid, score}
    }
    
    // 第3步：排序（降序）
    sort(vec.begin(), vec.end(), [](const pair<int,double> &a, const pair<int,double> &b) {
        return a.second > b.second;  // 按分数降序
    });
    
    // 第4步：输出结果
    cout << "\n====== 教师统计（按总分降序） ======\n";
    for (auto &p : vec) {
        cout << "教师ID:" << p.first << " 总分:" << p.second << "\n";
    }
    cout << "==================================\n";
      
    
}


// ========================================
// 【知识点5】sort + lambda 自定义排序
// ========================================
// 演示：按总分降序，总分相同按uid升序

void test_sort_lambda() {
    struct Row {
        int uid;
        string name;
        double total;
    };
    
    vector<Row> rows = {
        {101, "张三", 85.5},
        {102, "李四", 92.0},
        {103, "王五", 85.5},
        {104, "赵六", 78.0}
    };
    
    // 【TODO】请你手写排序逻辑
    // sort(rows.begin(), rows.end(), [](const Row &a, const Row &b) {
    //     提示：if (a.total != b.total) return a.total > b.total;  // 总分降序
    //          return a.uid < b.uid;                               // uid升序
    // });
    
    // 你的代码写在这里：
    sort(rows.begin(), rows.end(), [](const Row &a, const Row &b) {
        if (a.total != b.total) return a.total > b.total;  // 总分降序
        return a.uid < b.uid;  // 总分相同按uid升序
    });
    
    cout << "\n====== 排序后结果 ======\n";
    for (auto &r : rows) {
        cout << "UID:" << r.uid << " 姓名:" << r.name 
             << " 总分:" << r.total << "\n";
    }
}


// ========================================
// 【知识点6】function<> 回调函数
// ========================================
// 场景：showAppliesFiltered 需要动态过滤条件
// 用法：传入一个判断函数，决定哪些记录显示

void showAppliesFiltered(function<bool(const Apply&)> filter) {
    cout << "\n====== 过滤后的申报 ======\n";
    for (auto &a : applies) {
        if (filter(a)) {  // 调用传入的过滤函数
            cout << "AID:" << a.aid << " UID:" << a.uid 
                 << " Score:" << a.score << "\n";
        }
    }
}

void test_function_callback() {
    // 准备测试数据
    applies = {
        {1, 101, 30.0, 1},  // 通过
        {2, 102, 20.0, 0},  // 待审核
        {3, 101, 15.0, 1},  // 通过
        {4, 103, 25.0, 2}   // 驳回
    };
    
    // 用例1：只显示待审核的 (status==0)
    cout << "\n只显示待审核:\n";
    showAppliesFiltered([](const Apply &a) { return a.status == 0; });
    
    // 用例2：只显示101号教师的
    cout << "\n只显示101号教师:\n";
    showAppliesFiltered([](const Apply &a) { return a.uid == 101; });
    
    // 用例3：显示分数>=25的
    cout << "\n只显示分数>=25:\n";
    showAppliesFiltered([](const Apply &a) { return a.score >= 25; });
}


// ========================================
// 【知识点7】策略模式 - 自动计分规则
// ========================================
// 场景：不同类型申报有不同计分规则
// 解决方案：封装成函数，调用时根据类型分发

// 论文计分规则
double scorePaper(const string &level, int order) {
    double base = 0;
    if (level == "国家级") base = 30;
    else if (level == "省级") base = 20;
    else if (level == "校级") base = 10;
    else base = 5;
    
    // 顺序折扣
    double discount = 1.0;
    if (order == 1) discount = 1.0;
    else if (order == 2) discount = 0.7;
    else if (order == 3) discount = 0.5;
    else discount = 0.3;
    
    return base * discount;
}

// 项目计分规则
double scoreProject(const string &level, int order) {
    // 【TODO】请你参考 scorePaper 实现
    // 规则：国家级50分，省级35分，校级20分
    //       顺序折扣：1=100%, 2=60%, 3=40%, 4+=25%
    
    // 你的代码写在这里：
    double base = 0;
    if (level == "国家级") base = 50;
    else if (level == "省级") base = 35;
    else if (level == "校级") base = 20;
    else base = 5;
    
    double discount = 1.0;
    if (order == 1) discount = 1.0;
    else if (order == 2) discount = 0.6;
    else if (order == 3) discount = 0.4;
    else discount = 0.25;
    
    return base * discount;
}

// 经费计分规则
double scoreFund(double amount) {
    // 规则：每1万元 = 1分，上限50分
    double score = amount / 10000.0;
    if (score > 50) score = 50;
    return score;
}

void test_calcScore() {
    cout << "\n====== 测试计分规则 ======\n";
    
    // 论文：国家级第一作者
    cout << "论文-国家级-第1作者: " << scorePaper("国家级", 1) << "分\n";
    
    // 论文：省级第二作者
    cout << "论文-省级-第2作者: " << scorePaper("省级", 2) << "分\n";
    
    // 经费：30万元
    cout << "经费-30万元: " << scoreFund(300000) << "分\n";
}


// ========================================
// 【知识点8】numeric_limits 清除缓冲区
// ========================================
// 问题：cin >> int 后接 getline，需要清除换行符
// 解决方案：cin.ignore(numeric_limits<streamsize>::max(), '\n');

#include <limits>

void test_input_buffer() {
    cout << "\n====== 测试输入缓冲清理 ======\n";
    
    int num;
    string text;
    
    cout << "输入一个数字: ";
    cin >> num;
    
    // 【关键】清除缓冲区的换行符
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cout << "输入一段文字: ";
    getline(cin, text);
    
    cout << "你输入的数字: " << num << endl;
    cout << "你输入的文字: " << text << endl;
    
    // 如果不加 cin.ignore()，getline 会直接读到空行！
}


// ========================================
// 【主函数 - 测试所有知识点】
// ========================================
int main() {
    cout << "========================================\n";
    cout << "  【学习笔记-第3步】高级功能练习\n";
    cout << "========================================\n";
    
    // 测试菜单
    while (true) {
        cout << "\n请选择要测试的知识点：\n";
        cout << "1. splitByBar 字符串分割\n";
        cout << "2. trim 去除空格\n";
        cout << "3. CRUD 增删改查 (学院管理)\n";
        cout << "4. unordered_map 统计汇总\n";
        cout << "5. sort + lambda 排序\n";
        cout << "6. function<> 回调函数\n";
        cout << "7. 策略模式 计分规则\n";
        cout << "8. numeric_limits 清缓冲\n";
        cout << "0. 退出\n";
        cout << "选择: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 1: test_splitByBar(); break;
            case 2: test_trim(); break;
            case 3: {
                // CRUD 菜单
                while (true) {
                    cout << "\n【学院管理】\n";
                    cout << "1. 添加学院\n";
                    cout << "2. 删除学院\n";
                    cout << "3. 修改学院\n";
                    cout << "4. 查看学院\n";
                    cout << "0. 返回\n";
                    cout << "选择: ";
                    int op; cin >> op;
                    if (op == 0) break;
                    if (op == 1) addCollege();
                    else if (op == 2) delCollege();
                    else if (op == 3) editCollege();
                    else if (op == 4) showColleges();
                }
                break;
            }
            case 4: statsTeacherScore(); break;
            case 5: test_sort_lambda(); break;
            case 6: test_function_callback(); break;
            case 7: test_calcScore(); break;
            case 8: test_input_buffer(); break;
            case 0: 
                cout << "学习结束！\n";
                return 0;
            default:
                cout << "无效选择！\n";
        }
    }
    
    return 0;
}


// ========================================
// 【学习检查清单】
// ========================================
// 完成以下任务后，你就掌握了系统的核心知识：
//
// □ 1. splitByBar 手写实现并测试通过
// □ 2. trim 手写实现并测试通过
// □ 3. editCollege 手写实现
// □ 4. statsTeacherScore 手写实现（map汇总+sort排序）
// □ 5. test_sort_lambda 手写排序逻辑
// □ 6. scoreProject 手写项目计分规则
// □ 7. 理解 function<> 回调函数的用法
// □ 8. 理解 numeric_limits 清缓冲的原理
//
// ========================================
// 【下一步】
// ========================================
// 完成本练习后：
// 1. 编译运行，逐个测试8个知识点
// 2. 回到 教师科研工作量管理系统.cpp，对照理解完整代码
// 3. 运行完整系统，测试所有功能
// 4. 准备实习汇报材料（流程图、功能截图、代码说明）
