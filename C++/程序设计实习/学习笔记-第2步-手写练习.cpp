// ========================================
// 第2步：手写练习 - 从零开始
// ========================================
// 【任务1】实现登录功能（30分钟）
// ========================================
// 需求：
// 1. 输入用户名和密码
// 2. 在 users 列表中查找匹配的用户
// 3. 如果找到，设置当前登录用户ID和角色
// 4. 返回是否登录成功

#include <iostream>
#include <vector>
#include <string>
#include <sstream>  // 加在文件开头
using namespace std;

struct User {
    int uid;         // 学工号（直接用作登录账号）
    string password; // 密码
    int role;        // 0教师 1管理员
};

// 全局变量
vector<User> users;
int currentUserId = -1;
int currentUserRole = -1;

// 【TODO】请你自己实现这个函数
bool login() {
    // 提示：
    // 1. 用 cin 读取学工号和密码
    // 2. 遍历 users 数组
    // 3. 比较学工号和密码是否匹配
    // 4. 如果匹配，设置 currentUserId 和 currentUserRole
    // 5. 返回 true/false
    
    // 你的代码写在这里：
    int inputUid;
    string inputPassword;
    
    cout << "学工号: "<<endl;//强制输出
    cin >> inputUid;
    cout << "密码: "<<endl;
    cin >> inputPassword;
    
    // 遍历所有用户
    for (int i = 0; i < users.size(); i++) {
        if (users[i].uid == inputUid && users[i].password == inputPassword) {
            // 找到匹配的用户
            currentUserId = users[i].uid;
            currentUserRole = users[i].role;
            return true;  // 登录成功
        }
    }
    
    return false;  // 没找到匹配用户，登录失败;

    
}

// ========================================
// 【任务2】实现教师提交论文申报（45分钟）
// ========================================
// 需求：
// 1. 生成新的申报ID（当前最大ID+1）
// 2. 输入论文信息（年份、标题、级别、顺序）
// 3. 自动设置申报人为当前登录用户
// 4. 状态设为"待审核"，分数为0
// 5. 加入到 applies 列表

struct Apply {
    int aid;
    int type;    // 1论文 2项目 3经费
    int uid;
    int year;
    string title;
    string level;
    int order;
    double amount;
    int status;  // 0待审核 1通过 2驳回
    double score;
    string feedback;
};

vector<Apply> applies;

// 【TODO】请你自己实现
void submitPaper() {
    // 提示1：如何生成新ID？
    // int maxId = 0;
    // for (所有申报) { 找最大的aid }
    // int newId = maxId + 1;
    
    // 提示2：如何输入多个字段？
    // cout << "输入年份: ";
    // cin >> year;
    // cout << "输入标题: ";
    // cin.ignore(); // 清空缓冲区！
    // getline(cin, title);
    
    // 你的代码写在这里：
    // cout<<" 请输入申报类别：1为论文 2为项目 3为经费 "<<endl;
    // cin>>
    int maxid=0;
    for(auto a:applies){
        maxid=max(maxid,a.aid);
    }
    int newId=++maxid;
    Apply newApply;
    newApply.aid=newId;
    newApply.type=1;
    newApply.uid=currentUserId;
    cout<<" 输入年份：";
    cin>>newApply.year;
    cout<<" 输入标题：";
    cin.ignore();
    getline(cin,newApply.title);
    cout<<" 输入级别：";
    getline(cin,newApply.level);
    cout<<"输入顺序（1=第一作者，2=第二作者...）：";
    cin>>newApply.order;
    newApply.status=0;
    newApply.score=0;
    newApply.feedback="";
    newApply.amount=0;
    applies.push_back(newApply);
    cout<<"提交成功！申报ID："<<newId<<endl;
    
}

// ========================================
// 【任务3】实现管理员审核功能（60分钟）
// ========================================
// 需求：
// 1. 显示所有待审核的申报
// 2. 输入要审核的申报ID
// 3. 输入审核结果（通过/驳回）
// 4. 如果通过，自动计算分数
// 5. 输入反馈意见

// 【TODO】请你自己实现
void reviewApply() {
    // 提示1：如何找到指定ID的申报？
    // int index = -1;
    // for (int i=0; i<applies.size(); i++) {
    //     if (applies[i].aid == 要找的ID) {
    //         index = i;
    //         break;
    //     }
    // }
    
    // 提示2：如何计算分数？（简化版）
    // double calcScore(Apply &a) {
    //     if (a.type == 1) { // 论文
    //         if (a.level == "国家级") return 30.0;
    //         if (a.level == "省级") return 20.0;
    //         return 10.0;
    //     }
    //     // ...其他类型
    // }
    
    // 你的代码写在这里：
    
    // 1. 显示所有待审核的申报
    cout << "\n====== 待审核列表 ======\n";
    for (int i = 0; i < applies.size(); i++) {
        if (applies[i].status == 0) {  // 0=待审核
            cout << "ID:" << applies[i].aid 
                 << " 类型:" << applies[i].type
                 << " 年份:" << applies[i].year << "\n";
        }
    }
    
    // 2. 输入要审核的ID
    int targetId;
    cout << "\n输入要审核的申报ID: ";
    cin >> targetId;
    
    // 3. 找到这个申报
    int index = -1;
    for (int i = 0; i < applies.size(); i++) {
        if (applies[i].aid == targetId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "未找到该申报！\n";
        return;
    }
    
    // 4. 审核
    cout << "1=通过  2=驳回: ";
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        applies[index].status = 1;  // 通过
        applies[index].score = 30.0;  // 简化版，直接给30分
    } else {
        applies[index].status = 2;  // 驳回
        applies[index].score = 0;
    }
    
    cout << "审核完成！\n";
    
    
    
    
    
}

// ========================================
// 【任务4】实现文件保存（45分钟）
// ========================================
// 需求：把 applies 数组保存到 applies.txt
// 格式：每行一个申报，字段用 | 分隔

#include <fstream>

// 【TODO】请你自己实现
void saveApplies() {
    // 提示：
    // ofstream fout("applies.txt");
    // for (每个申报) {
    //     fout << aid << "|" << type << "|" << ... << "\n";
    // }
    // fout.close();
    
    // 你的代码写在这里：
    ofstream fout("applies.txt");  
    if(!fout){
        cerr<<"文件写入出错"<<endl;
        return;
    }

    // 表头只写一次，放在循环外！
    fout << "申报ID|类型|用户ID|年份|标题|级别|顺序|金额|状态|分数|反馈\n";
    
    for(int i=0; i<applies.size(); i++){
        fout << applies[i].aid << "|"
             << applies[i].type << "|"
             << applies[i].uid << "|"
             << applies[i].year << "|"
             << applies[i].title << "|"
             << applies[i].level << "|"
             << applies[i].order << "|"
             << applies[i].amount << "|"
             << applies[i].status << "|"
             << applies[i].score << "|"
             << applies[i].feedback << "\n";  // 所有字段都要保存
    }
    fout.close();
    cout << "保存成功！共 " << applies.size() << " 条记录\n";
    
    
    
    
}

// ========================================
// 【任务5】实现文件读取（45分钟）
// ========================================
// 需求：从 applies.txt 读取数据到 applies 数组

// 【TODO】请你自己实现
void loadApplies() {
    // 提示1：如何按行读取？
    // ifstream fin("applies.txt");
    // string line;
    // while (getline(fin, line)) {
    //     // 处理每一行
    // }
    
    // 提示2：如何分割字符串？
    // 方法1：手动找 '|' 的位置
    // 方法2：用 stringstream
    
    // 你的代码写在这里：
    ifstream fin("applies.txt");
    if(!fin.is_open()){
        cerr<<"无法打开applies.txt文件进行读取"<<endl;
        return;
    }
    
    cout<<"\n===== 正在从 applies.txt 读取数据 =====\n";
    // 直接整行输出  避免格式变动读崩
    string line;
    getline(fin,line);

    while(getline(fin,line)){
        stringstream ss(line);
        Apply a;
        string temp;
        getline(ss,temp,'|');a.aid=stoi(temp);
        getline(ss,temp,'|');a.type=stoi(temp);
        getline(ss,temp,'|');a.uid=stoi(temp);
        getline(ss,temp,'|');a.year=stoi(temp);      // 别忘了年份！
        getline(ss,a.title,'|');
        getline(ss,a.level,'|');
        getline(ss,temp,'|');a.order=stoi(temp);
        getline(ss,temp,'|');a.amount=stoi(temp);
        getline(ss,temp,'|');a.status=stoi(temp);
        getline(ss,temp,'|');a.score=stod(temp);
        getline(ss,a.feedback);
        applies.push_back(a);

    }
    fin.close();
    cout<<"读取成功！共 "<<applies.size()<<" 条记录\n";
    
    
}

// ========================================
// 【自测题】
// ========================================
// 完成上面5个任务后，回答：
// 1. login() 函数为什么要返回 bool？ 登录成功与否对应true和false
// 2. submitPaper() 为什么要用 cin.ignore()？cin后会有换行干扰
// 3. reviewApply() 如果找不到指定ID应该怎么处理？返回未找到
// 4. saveApplies() 如果文件打开失败怎么办？返回文件打开失败
// 5. loadApplies() 如果某行数据格式错误怎么办？写个错误返回？

int main() {
    // 测试你写的函数
    
    // 1. 准备测试数据
    users.push_back({1, "admin", 1});        // 管理员：工号1，密码admin
    users.push_back({101, "123", 0});        // 教师：工号101，密码123
    
    // 2. 测试登录
    if (login()) {
        cout << "登录成功！角色：" << currentUserRole << endl;
    }
    
    // 3. 测试提交
    if (currentUserRole == 0) {
        submitPaper();
    }
    
    // 4. 测试保存
    saveApplies();
    
    // 5. 测试读取
    applies.clear();
    loadApplies();
    cout << "读取到 " << applies.size() << " 条申报" << endl;
    
    return 0;
}
