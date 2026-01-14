// ========================================
// 教师科研工作量管理系统 v1.0
// ========================================
#include <iostream>   // cin cout
#include <fstream>    // ifstream ofstream
#include <iomanip>    // setw setprecision
#include <string>     // string
#include <vector>     // vector
#include <functional> // function
#include <algorithm>  // sort
#include <unordered_map>
#include <sstream>  // 加在文件开头
#include <limits>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

// ===================== 数据结构 =====================

struct College {
    ll cid;
    string name;
};

struct User {
    ll uid;          // 工号（直接用作登录账号）
    ll cid;          // 学院ID
    string name;     // 姓名
    string password; // 密码
    ll role;         // 0=teacher, 1=admin
};

// 申请状态：0待审核 1通过 2驳回
// type：1论文 2项目 3经费
struct Apply {
    ll aid;
    ll type;
    ll uid;
    ll year;

    // 论文/项目：level + order + title
    string title;
    string level;    // 级别（校/省/国）
    ll ord;          // 顺序（第几作者/第几负责人等）

    // 经费：amount
    double amount;

    // 审核信息
    ll status;       // 0/1/2
    double score;    // 审核确认分数
    string feedback; // 审核意见
};

// ===================== 全局数据 =====================

vector<College> colleges;
vector<User> users;
vector<Apply> applies;

const string F_COL = "colleges.txt";
const string F_USR = "users.txt";
const string F_APL = "applies.txt";
const string F_RULE = "score_rules.txt";  // 计分规则文件

// 当前登录
ll cur_uid = -1;
ll cur_role = -1;

// ===================== 规则驱动计分系统 =====================
// 规则存储：用map实现表驱动
unordered_map<string, double> scoreRules;  // 存储所有计分规则

// ===================== 工具 =====================

static inline void line(){ cout << "----------------------------------------\n"; }

vector<string> splitByBar(const string &s){//依据 | 拆分输入字符
    vector<string> p;
    string cur;
    for(char c: s){
        if(c=='|'){ p.push_back(cur); cur.clear(); }
        else cur.push_back(c);//push_back 实现字符串累加
    }
    p.push_back(cur);//加上最后一个拆分的
    return p;
}

string trim(const string &s){//去除字符两边空白
    int l=0, r=(int)s.size()-1;
    while(l<=r && isspace((unsigned char)s[l])) l++;
    while(l<=r && isspace((unsigned char)s[r])) r--;
    if(l>r) return "";
    return s.substr(l, r-l+1);
}
//快速查找学院 用户 申请的索引
int findCollegeIdx(ll cid){
    for(int i=0;i<(int)colleges.size();i++) if(colleges[i].cid==cid) return i;
    return -1;
}
int findUserIdxByUid(ll uid){
    for(int i=0;i<(int)users.size();i++) if(users[i].uid==uid) return i;
    return -1;
}
// 已删除 findUserIdxByUsername，改用 uid 登录
int findApplyIdx(ll aid){
    for(int i=0;i<(int)applies.size();i++) if(applies[i].aid==aid) return i;
    return -1;
}

ll nextApplyId(){//每次重新启动程序 从之前申请中找到最大申请标号 自增作为当前申请id
    ll mx=0;
    for(auto &a: applies) mx=max(mx, a.aid);
    return mx+1;
}

// ===================== 规则驱动计分系统 =====================
// 【创新点】：计分规则可配置，从score_rules.txt读取
// 优点：适配不同学院标准、规则透明可解释、便于维护

// 加载计分规则
void loadScoreRules(){
    scoreRules.clear();
    ifstream fin(F_RULE);//in 数据流 流向程序 是读出
    if(!fin.is_open()){
        cout << "[警告] 规则文件不存在，使用默认规则\n";//双重保险
        // 默认规则写入内存
        scoreRules["paper|national"] = 30; scoreRules["paper|provincial"] = 20;
        scoreRules["paper|school"] = 10; scoreRules["paper|other"] = 8;
        scoreRules["paper_order|1"] = 1.0; scoreRules["paper_order|2"] = 0.7;
        scoreRules["paper_order|3"] = 0.5; scoreRules["paper_order|other"] = 0.3;
        scoreRules["project|national"] = 50; scoreRules["project|provincial"] = 35;
        scoreRules["project|school"] = 20; scoreRules["project|other"] = 15;
        scoreRules["project_order|1"] = 1.0; scoreRules["project_order|2"] = 0.6;
        scoreRules["project_order|3"] = 0.4; scoreRules["project_order|other"] = 0.25;
        scoreRules["fund|rate"] = 1.0; scoreRules["fund|max"] = 50.0;
        return;
    }
    
    string line;
    while(getline(fin, line)){
        line = trim(line);  // 去除首尾空格
        if(line.empty() || line[0]=='#') continue;  // 跳过空行和注释行（以#开头）
        
        auto parts = splitByBar(line);  // 按|分割，得到字符串数组
        // 【关键】至少需要3个字段：类型|键|值，少于3个说明格式错误
        if(parts.size() < 3) continue;  // 跳过格式不完整的行
        
        string type = trim(parts[0]);   // 第1列：类型(paper/project/fund)
        string key = trim(parts[1]);    // 第2列：键(national/1/rate等)
        double value = stod(trim(parts[2]));  // 第3列：数值(分数或系数)
        
        // 【创新点核心】构建哈希表的键值对
        // 经费规则特殊处理：第2列是rate，第3列是max
        if(type == "fund"){
            scoreRules["fund|rate"] = value;  // 每万元对应分数
            // 经费有两个值：费率和上限，都在第3列
            if(parts.size() >= 3) scoreRules["fund|max"] = stod(trim(parts[2]));
        }else{
            // 论文/项目规则：拼接"类型|键"作为哈希表的key
            // 例如："paper|national" → 30
            //      "paper_order|1" → 1.0
            scoreRules[type + "|" + key] = value;
        }
    }
    fin.close();
    cout << "[系统] 已加载 " << scoreRules.size() << " 条计分规则\n";
}

// 查询规则（带默认值）
double getRule(const string &key, double defaultVal = 0){
    if(scoreRules.count(key)) return scoreRules[key];
    return defaultVal;
}

// 论文计分（规则驱动）
double scorePaper(const string &level, ll ord){
    double base = getRule("paper|" + level, 8.0);  // 默认8分
    
    string ordKey = (ord<=3) ? to_string(ord) : "other";
    double k = getRule("paper_order|" + ordKey, 0.3);
    
    return base * k;
}

// 项目计分（规则驱动）
double scoreProject(const string &level, ll ord){
    double base = getRule("project|" + level, 15.0);
    
    string ordKey = (ord<=3) ? to_string(ord) : "other";
    double k = getRule("project_order|" + ordKey, 0.25);
    
    return base * k;
}

// 经费计分（规则驱动）
double scoreFund(double amount){
    double rate = getRule("fund|rate", 1.0);   // 每万元分数
    double maxScore = getRule("fund|max", 50.0);
    
    double sc = amount / 10000.0 * rate;
    if(sc > maxScore) sc = maxScore;
    if(sc < 0) sc = 0;
    return sc;
}

double calcScore(const Apply &a){
    if(a.type==1) return scorePaper(a.level, a.ord);
    if(a.type==2) return scoreProject(a.level, a.ord);
    if(a.type==3) return scoreFund(a.amount);
    return 0;
}

// ===================== 文件读写 =====================
// colleges: cid|name
// users   : uid|cid|name|password|role
// applies : aid|type|uid|year|title|level|ord|amount|status|score|feedback

void loadColleges(){
    colleges.clear();
    ifstream fin(F_COL);//读
    if(!fin.is_open()) return;//无法打开就退出
    string s;
    while(getline(fin, s)){//循环读行
        if(trim(s).empty()) continue;
        auto p = splitByBar(s);//依旧分块 去空格
        if((int)p.size()!=2) continue;//只要能分成两块的
        College c;
        c.cid = stoll(p[0]);
        c.name = p[1];
        colleges.push_back(c);
    }
    fin.close();
}

void saveColleges(){
    ofstream fout(F_COL);//写入文件
    for(auto &c: colleges){
        fout << c.cid << "|" << c.name << "\n";
    }
    fout.close();
}

void loadUsers(){
    users.clear();
    ifstream fin(F_USR);
    if(!fin.is_open()) return;
    string s;
    while(getline(fin, s)){
        if(trim(s).empty()) continue;
        auto p = splitByBar(s);
        if((int)p.size()!=5) continue;
        User u;
        u.uid = stoll(p[0]);
        u.cid = stoll(p[1]);
        u.name = p[2];
        u.password = p[3];
        u.role = stoll(p[4]);
        users.push_back(u);
    }
    fin.close();
}

void saveUsers(){
    ofstream fout(F_USR);
    for(auto &u: users){
        fout << u.uid << "|" << u.cid << "|" << u.name
             << "|" << u.password << "|" << u.role << "\n";
    }
    fout.close();
}

void loadApplies(){//读出之前所有申请记录
    applies.clear();
    ifstream fin(F_APL);
    if(!fin.is_open()) return;
    string s;
    while(getline(fin, s)){
        if(trim(s).empty()) continue;
        auto p = splitByBar(s);
        if((int)p.size()!=11) continue;
        Apply a;
        a.aid = stoll(p[0]);
        a.type = stoll(p[1]);
        a.uid = stoll(p[2]);
        a.year = stoll(p[3]);
        a.title = p[4];
        a.level = p[5];
        a.ord = stoll(p[6]);
        a.amount = stod(p[7]);
        a.status = stoll(p[8]);
        a.score = stod(p[9]);
        a.feedback = p[10];
        applies.push_back(a);
    }
    fin.close();
}

void saveApplies(){//写入所有申请记录
    ofstream fout(F_APL);
    for(auto &a: applies){
        fout << a.aid << "|" << a.type << "|" << a.uid << "|" << a.year << "|"
             << a.title << "|" << a.level << "|" << a.ord << "|"
             << a.amount << "|" << a.status << "|" << a.score << "|"
             << a.feedback << "\n";
    }
    fout.close();
}

void loadAll(){//统筹加载
    loadScoreRules();  // 【新增】先加载计分规则
    loadColleges();
    loadUsers();
    loadApplies();

    // 没有管理员账号则生成一个默认管理员
    if(users.empty()){
        colleges.push_back({1, "DefaultCollege"});
        User admin;
        admin.uid = 1;
        admin.cid = 1;
        admin.name = "Admin";
        admin.password = "admin";
        admin.role = 1;
        users.push_back(admin);
        saveColleges();
        saveUsers();
    }
}

void saveAll(){
    saveColleges();
    saveUsers();
    saveApplies();
}

// ===================== 展示 =====================

string typeName(ll t){
    if(t==1) return "Paper";
    if(t==2) return "Project";
    if(t==3) return "Fund";
    return "Unknown";
}
string statusName(ll s){
    if(s==0) return "Pending";
    if(s==1) return "Approved";
    if(s==2) return "Rejected";
    return "Unknown";
}

void showColleges(){
    line();//添加一根线
    cout << left << setw(8) << "CID" << "Name\n";//控制宽度输出
    line();
    for(auto &c: colleges) cout << left << setw(8) << c.cid << c.name << "\n";
    line();
}

void showUsers(){
    line();
    cout << left << setw(8) << "UID" << setw(14) << "Name" << setw(8) << "CID"
         << "Role\n";
    line();
    for(auto &u: users){
        cout << left << setw(8) << u.uid << setw(14) << u.name << setw(8) << u.cid
             << (u.role==1?"admin":"teacher") << "\n";
    }
    line();
}

void showAppliesFiltered(function<bool(const Apply&)> ok){
    line();
    cout << left << setw(6) << "AID" << setw(8) << "Type" << setw(8) << "UID"
         << setw(6) << "Year" << setw(10) << "Status" << setw(8) << "Score"
         << "Title/Info\n";
    line();
    for(auto &a: applies){
        if(!ok(a)) continue;
        cout << left << setw(6) << a.aid << setw(8) << typeName(a.type)
             << setw(8) << a.uid << setw(6) << a.year
             << setw(10) << statusName(a.status)
             << setw(8) << fixed << setprecision(2) << a.score;

        cout.unsetf(std::ios::floatfield);

        if(a.type==3){
            cout << "amount=" << a.amount << " feedback=" << a.feedback << "\n";
        }else{
            cout << a.title << " level=" << a.level << " ord=" << a.ord
                 << " feedback=" << a.feedback << "\n";
        }
    }
    line();
}

// ===================== 登录 =====================

bool login(){
    ll inputUid;
    string pw;//password
    cout << "工号: ";
    cin >> inputUid;
    cout << "密码: ";
    cin >> pw;
    int idx = findUserIdxByUid(inputUid);
    if(idx==-1 || users[idx].password!=pw){
        cout << "Login failed.\n";
        return false;
    }
    cur_uid = users[idx].uid;
    cur_role = users[idx].role;
    cout << "Login OK. role=" << (cur_role==1?"admin":"teacher") << "\n";
    return true;
}

void logout(){
    cur_uid = -1;
    cur_role = -1;
}

// ===================== Admin：学院/教师 CRUD =====================

void addCollege(){
    College c;
    cout << "cid: "; cin >> c.cid;
    if(findCollegeIdx(c.cid)!=-1){ cout << "cid exists.\n"; return; }
    cout << "name: ";
    // 清除缓冲区：cin>>后会留下换行符，需清理否则getline会读到空行
    // max()确保能清除所有垃圾字符，'\n'指定遇到换行符时停止
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, c.name);
    c.name = trim(c.name);
    colleges.push_back(c);
    cout << "OK.\n";
}

void delCollege(){
    ll cid; cout << "cid to delete: "; cin >> cid;
    int idx = findCollegeIdx(cid);
    if(idx==-1){ cout << "not found.\n"; return; }
    colleges.erase(colleges.begin()+idx);
    cout << "OK.\n";
}

// 修改学院信息（完整CRUD中的Update）
void editCollege(){
    ll cid; 
    cout << "cid to edit: "; 
    cin >> cid;
    
    int idx = findCollegeIdx(cid);
    if(idx==-1){ 
        cout << "not found.\n"; 
        return; 
    }
    
    // 显示当前信息
    cout << "Current name: " << colleges[idx].name << "\n";
    cout << "New name (press Enter to keep current): ";
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string newName;
    getline(cin, newName);
    newName = trim(newName);
    
    // 如果输入为空，保持原值；否则更新
    if(!newName.empty()){
        colleges[idx].name = newName;
        cout << "Updated.\n";
    }else{
        cout << "Unchanged.\n";
    }
}

void addTeacherUser(){
    User u;
    u.role = 0;
    cout << "uid: "; cin >> u.uid;
    if(findUserIdxByUid(u.uid)!=-1){ cout << "uid exists.\n"; return; }
    cout << "cid: "; cin >> u.cid;
    if(findCollegeIdx(u.cid)==-1) cout << "warning: cid not found.\n";
    cout << "name: ";
    // cin>>读取数字后，缓冲区剩余换行符，必须清理后才能用getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, u.name); u.name=trim(u.name);//trim修剪 削减
    cout << "password: "; getline(cin, u.password); u.password=trim(u.password);
    users.push_back(u);
    cout << "OK.\n";
}

// ===================== Teacher：提交申请 =====================

void submitPaper(){
    Apply a;
    a.aid = nextApplyId();
    a.type = 1;
    a.uid = cur_uid;

    cout << "year: "; cin >> a.year;
    cout << "title: ";
    // 【重要】cin>>year后缓冲区剩余换行符，必须清理否则getline会读到空字符串
    // max()确保能清除所有垃圾字符(如用户误输入2025abc)，遇\n停止
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, a.title); a.title=trim(a.title);

    cout << "level (e.g. national/provincial/school): ";
    getline(cin, a.level); a.level=trim(a.level);

    cout << "order (1/2/3...): ";
    cin >> a.ord;

    a.amount = 0;
    a.status = 0;
    a.score = 0;
    a.feedback = "";

    applies.push_back(a);
    cout << "Submit OK. aid=" << a.aid << "\n";
}

void submitProject(){
    Apply a;
    a.aid = nextApplyId();
    a.type = 2;
    a.uid = cur_uid;

    cout << "year: "; cin >> a.year;
    cout << "title: ";
    // 同submitPaper，清除cin>>后的缓冲区残留(换行符+可能的垃圾字符)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, a.title); a.title=trim(a.title);

    cout << "level (e.g. national/provincial/school): ";
    getline(cin, a.level); a.level=trim(a.level);

    cout << "order (1/2/3...): ";
    cin >> a.ord;

    a.amount = 0;
    a.status = 0;
    a.score = 0;
    a.feedback = "";

    applies.push_back(a);
    cout << "Submit OK. aid=" << a.aid << "\n";
}

void submitFund(){
    Apply a;
    a.aid = nextApplyId();
    a.type = 3;
    a.uid = cur_uid;

    cout << "year: "; cin >> a.year;
    cout << "amount: "; cin >> a.amount;

    a.title = "";
    a.level = "";
    a.ord = 0;

    a.status = 0;
    a.score = 0;
    a.feedback = "";

    applies.push_back(a);
    cout << "Submit OK. aid=" << a.aid << "\n";
}

// ===================== Admin：审核 =====================

void reviewOne(){
    // 只给管理员用：列出待审核 
    showAppliesFiltered([](const Apply& a){ return a.status==0; });
    //输入aid
    ll aid; cout << "aid to review: "; cin >> aid;
    int idx = findApplyIdx(aid);
    if(idx==-1){ cout << "not found.\n"; return; }
    if(applies[idx].status!=0){ cout << "not pending.\n"; return; }
    
    Apply &a = applies[idx];
    cout << "Type=" << typeName(a.type) << " UID=" << a.uid << "\n";
    //通过/驳回
    int op;
    cout << "1=approve, 2=reject : ";
    cin >> op;
    //可修改score/feedback
    cout << "feedback: ";
    // cin>>op读取操作码后，清除剩余换行符，避免getline读空
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string fb; getline(cin, fb); fb=trim(fb);

    if(op==1){
        a.status = 1;  // 设置为已通过
        
        // 【创新点应用】调用规则驱动的自动计分
        double auto_sc = calcScore(a);
        
        // 【技巧】临时设置浮点数格式为固定小数点2位
        cout << "auto score = " << fixed << setprecision(2) << auto_sc << "\n";
        // 【关键】取消浮点数格式设置，恢复默认（否则影响后续输出）
        cout.unsetf(std::ios::floatfield);

        // 【人工覆盖机制】允许管理员修改系统建议分
        cout << "override score? (enter -1 keep auto): ";
        double x; cin >> x;
        
        // 【技巧】用-0.5作为阈值判断（防止浮点数精度问题）
        // 如果输入-1（或更小），使用系统建议分；否则使用自定义分
        if(x < -0.5) a.score = auto_sc;  // 使用系统计算的分数
        else a.score = x;                // 使用管理员输入的分数

        a.feedback = fb;
        cout << "Approved.\n";
    }else if(op==2){
        a.status = 2;
        a.score = 0;
        a.feedback = fb;
        cout << "Rejected.\n";
    }else{
        cout << "invalid.\n";
    }
}

// ===================== 统计（加分项） =====================

void statsTeacher(){
    // 按教师统计：通过的申请总分（论文/项目/经费分别 + 总分）
    unordered_map<ll, double> sp, sj, sf, st;
    for(auto &a: applies){
        if(a.status!=1) continue;
        if(a.type==1) sp[a.uid]+=a.score;
        if(a.type==2) sj[a.uid]+=a.score;
        if(a.type==3) sf[a.uid]+=a.score;
        st[a.uid]+=a.score;
    }

    struct Row{ ll uid; string name; ll cid; double p,j,f,t; };//新建结构体用于存储数据 方便排序
    vector<Row> rows;
    for(auto &u: users){
        if(u.role!=0) continue;
        Row r;
        r.uid=u.uid; r.name=u.name; r.cid=u.cid;
        r.p=sp[u.uid]; r.j=sj[u.uid]; r.f=sf[u.uid]; r.t=st[u.uid];
        rows.push_back(r);
    }

    sort(rows.begin(), rows.end(), [](const Row& a, const Row& b){
        if(a.t!=b.t) return a.t>b.t;//拉姆达表达式 自定义使用总分排序
        return a.uid<b.uid;//同分按照uid升序排序
    });

    line();//输出
    cout << left << setw(8) << "UID" << setw(14) << "Name" << setw(8) << "CID"
         << setw(10) << "Paper" << setw(10) << "Proj" << setw(10) << "Fund" << "Total\n";
    line();
    for(auto &r: rows){
        cout << left << setw(8) << r.uid << setw(14) << r.name << setw(8) << r.cid
             << setw(10) << fixed << setprecision(2) << r.p
             << setw(10) << r.j << setw(10) << r.f << r.t << "\n";
    }
    line();
}

void statsCollege(){
    // 按学院统计：学院下教师通过总分
    unordered_map<ll, double> tscore;
    for(auto &a: applies) if(a.status==1) tscore[a.uid]+=a.score;

    unordered_map<ll, double> csum;
    for(auto &u: users){
        if(u.role!=0) continue;//排除管理者
        csum[u.cid] += tscore[u.uid];
    }

    struct Row{ ll cid; string name; double sum; };
    vector<Row> rows;
    for(auto &c: colleges){
        Row r{c.cid, c.name, csum[c.cid]};
        rows.push_back(r);
    }
    sort(rows.begin(), rows.end(), [](const Row& a, const Row& b){
        if(a.sum!=b.sum) return a.sum>b.sum;
        return a.cid<b.cid;
    });

    line();
    cout << left << setw(8) << "CID" << setw(20) << "College" << "TotalScore\n";
    line();
    for(auto &r: rows){
        cout << left << setw(8) << r.cid << setw(20) << r.name
             << fixed << setprecision(2) << r.sum << "\n";
    }
    line();
}

// ===================== 菜单 =====================

void menuTeacher(){
    cout << "\n=== Teacher Menu ===\n";
    cout << "1. Submit Paper\n";
    cout << "2. Submit Project\n";
    cout << "3. Submit Fund\n";
    cout << "4. View My Applies\n";
    cout << "5. View My Approved Applies\n";
    cout << "s. Save\n";
    cout << "0. Logout\n";
    cout << "Select: ";
}

void menuAdmin(){
    cout << "\n=== Admin Menu ===\n";
    cout << "1. Show Colleges\n";
    cout << "2. Add College\n";
    cout << "3. Delete College\n";
    cout << "4. Show Users\n";
    cout << "5. Add Teacher User\n";
    cout << "6. Show All Applies\n";
    cout << "7. Show Pending Applies\n";
    cout << "8. Review One Apply\n";
    cout << "9. Stats By Teacher\n";
    cout << "10. Stats By College\n";
    cout << "s. Save\n";
    cout << "0. Logout\n";
    cout << "Select: ";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    loadAll();

    while(1){
        cout << "\n=== System ===\n";
        cout << "1. Login\n";
        cout << "0. Exit\n";
        cout << "Select: ";
        int op;
        if(!(cin >> op)) break;
        if(op==0){
            saveAll();
            cout << "Saved. Bye.\n";
            break;
        }
        if(op!=1) continue;
        if(!login()) continue;//这里调用登录函数 登录成功继续

        if(cur_role==0){//教师
            while(1){//循环菜单
                menuTeacher();
                string input; cin >> input;
                if(input=="0"){ logout(); break; }
                if(input=="s" || input=="S"){ saveAll(); cout << "Saved.\n"; continue; }//s 保存
                int x = (input.size()==1 && input[0]>='0' && input[0]<='9') ? (input[0]-'0') : -1;//对输入的字符串处理 转化为数字
                if(x==1) submitPaper();
                else if(x==2) submitProject();
                else if(x==3) submitFund();
                else if(x==4) showAppliesFiltered([](const Apply& a){ return a.uid==cur_uid; });//筛选 所有申请
                else if(x==5) showAppliesFiltered([](const Apply& a){ return a.uid==cur_uid && a.status==1; });//通过的所有申请
                else cout << "Invalid.\n";
            }
        }else{
            while(1){
                menuAdmin();//管理员菜单
                string input; cin >> input;
                if(input=="0"){ logout(); break; }
                if(input=="s" || input=="S"){ saveAll(); cout << "Saved.\n"; continue; }

                int x = -1;
                if(input=="10") x=10;//对于读入的字符串 单独处理10
                else if(input.size()==1 && input[0]>='0' && input[0]<='9') x = input[0]-'0';
                
                if(x==1) showColleges();
                else if(x==2) addCollege();//增删改查
                else if(x==3) delCollege();
                else if(x==4) showUsers();
                else if(x==5) addTeacherUser();
                else if(x==6) showAppliesFiltered([](const Apply&){ return true; });
                else if(x==7) showAppliesFiltered([](const Apply& a){ return a.status==0; });
                else if(x==8) reviewOne();
                else if(x==9) statsTeacher();//统计老师
                else if(x==10) statsCollege();//统计学院
                else cout << "Invalid.\n";
            }
        }
    }

    return 0;
}
