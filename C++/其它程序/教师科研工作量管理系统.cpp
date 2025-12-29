#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

// ===================== 数据结构 =====================

struct College {
    ll cid;
    string name;
};

struct User {
    ll uid;          // 教师ID/账号ID
    ll cid;          // 学院ID
    string name;
    string username;
    string password;
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
    string level;    // 级别（你按老师口径定义：校/省/国；或A/B/C等）
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

// 当前登录
ll cur_uid = -1;
ll cur_role = -1;

// ===================== 工具 =====================

static inline void line(){ cout << "----------------------------------------\n"; }

vector<string> splitByBar(const string &s){
    vector<string> p;
    string cur;
    for(char c: s){
        if(c=='|'){ p.push_back(cur); cur.clear(); }
        else cur.push_back(c);
    }
    p.push_back(cur);
    return p;
}

string trim(const string &s){
    int l=0, r=(int)s.size()-1;
    while(l<=r && isspace((unsigned char)s[l])) l++;
    while(l<=r && isspace((unsigned char)s[r])) r--;
    if(l>r) return "";
    return s.substr(l, r-l+1);
}

int findCollegeIdx(ll cid){
    for(int i=0;i<(int)colleges.size();i++) if(colleges[i].cid==cid) return i;
    return -1;
}
int findUserIdxByUid(ll uid){
    for(int i=0;i<(int)users.size();i++) if(users[i].uid==uid) return i;
    return -1;
}
int findUserIdxByUsername(const string &un){
    for(int i=0;i<(int)users.size();i++) if(users[i].username==un) return i;
    return -1;
}
int findApplyIdx(ll aid){
    for(int i=0;i<(int)applies.size();i++) if(applies[i].aid==aid) return i;
    return -1;
}

ll nextApplyId(){
    ll mx=0;
    for(auto &a: applies) mx=max(mx, a.aid);
    return mx+1;
}

// ===================== 计分规则（你最后按老师口径改这里就行） =====================
// 这里给一个“可运行的默认规则”，保证系统完整。
// 你要拿高分：把规则写成表驱动（从txt读规则）也行。

double scorePaper(const string &level, ll ord){
    // level: national/provincial/school (示例)
    double base = 0;
    if(level=="national") base = 30;
    else if(level=="provincial") base = 20;
    else if(level=="school") base = 10;
    else base = 8;

    // 顺序折扣：1=100%, 2=70%, 3=50%, 4+=30%
    double k = 0.3;
    if(ord==1) k=1.0;
    else if(ord==2) k=0.7;
    else if(ord==3) k=0.5;
    else k=0.3;
    return base*k;
}

double scoreProject(const string &level, ll ord){
    double base = 0;
    if(level=="national") base = 50;
    else if(level=="provincial") base = 35;
    else if(level=="school") base = 20;
    else base = 15;

    double k = 0.4;
    if(ord==1) k=1.0;
    else if(ord==2) k=0.6;
    else if(ord==3) k=0.4;
    else k=0.25;
    return base*k;
}

double scoreFund(double amount){
    // 示例：每1万=1分，上限50分
    double sc = amount / 10000.0;
    if(sc > 50) sc = 50;
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
// users   : uid|cid|name|username|password|role
// applies : aid|type|uid|year|title|level|ord|amount|status|score|feedback

void loadColleges(){
    colleges.clear();
    ifstream fin(F_COL);
    if(!fin.is_open()) return;
    string s;
    while(getline(fin, s)){
        if(trim(s).empty()) continue;
        auto p = splitByBar(s);
        if((int)p.size()!=2) continue;
        College c;
        c.cid = stoll(p[0]);
        c.name = p[1];
        colleges.push_back(c);
    }
    fin.close();
}

void saveColleges(){
    ofstream fout(F_COL);
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
        if((int)p.size()!=6) continue;
        User u;
        u.uid = stoll(p[0]);
        u.cid = stoll(p[1]);
        u.name = p[2];
        u.username = p[3];
        u.password = p[4];
        u.role = stoll(p[5]);
        users.push_back(u);
    }
    fin.close();
}

void saveUsers(){
    ofstream fout(F_USR);
    for(auto &u: users){
        fout << u.uid << "|" << u.cid << "|" << u.name << "|" << u.username
             << "|" << u.password << "|" << u.role << "\n";
    }
    fout.close();
}

void loadApplies(){
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

void saveApplies(){
    ofstream fout(F_APL);
    for(auto &a: applies){
        fout << a.aid << "|" << a.type << "|" << a.uid << "|" << a.year << "|"
             << a.title << "|" << a.level << "|" << a.ord << "|"
             << a.amount << "|" << a.status << "|" << a.score << "|"
             << a.feedback << "\n";
    }
    fout.close();
}

void loadAll(){
    loadColleges();
    loadUsers();
    loadApplies();

    // 没有管理员账号则生成一个默认管理员（方便你直接跑）
    if(users.empty()){
        colleges.push_back({1, "DefaultCollege"});
        User admin;
        admin.uid = 1;
        admin.cid = 1;
        admin.name = "Admin";
        admin.username = "admin";
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
    line();
    cout << left << setw(8) << "CID" << "Name\n";
    line();
    for(auto &c: colleges) cout << left << setw(8) << c.cid << c.name << "\n";
    line();
}

void showUsers(){
    line();
    cout << left << setw(8) << "UID" << setw(14) << "Name" << setw(8) << "CID"
         << setw(12) << "Role" << "Username\n";
    line();
    for(auto &u: users){
        cout << left << setw(8) << u.uid << setw(14) << u.name << setw(8) << u.cid
             << setw(12) << (u.role==1?"admin":"teacher") << u.username << "\n";
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
    string un, pw;
    cout << "username: ";
    cin >> un;
    cout << "password: ";
    cin >> pw;
    int idx = findUserIdxByUsername(un);
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

void addTeacherUser(){
    User u;
    u.role = 0;
    cout << "uid: "; cin >> u.uid;
    if(findUserIdxByUid(u.uid)!=-1){ cout << "uid exists.\n"; return; }
    cout << "cid: "; cin >> u.cid;
    if(findCollegeIdx(u.cid)==-1) cout << "warning: cid not found.\n";
    cout << "name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, u.name); u.name=trim(u.name);
    cout << "username: "; getline(cin, u.username); u.username=trim(u.username);
    cout << "password: "; getline(cin, u.password); u.password=trim(u.password);
    if(findUserIdxByUsername(u.username)!=-1){ cout << "username exists.\n"; return; }
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
    // 只给管理员用：列出待审核 -> 输入aid -> 通过/驳回 -> 可修改score/feedback
    showAppliesFiltered([](const Apply& a){ return a.status==0; });

    ll aid; cout << "aid to review: "; cin >> aid;
    int idx = findApplyIdx(aid);
    if(idx==-1){ cout << "not found.\n"; return; }
    if(applies[idx].status!=0){ cout << "not pending.\n"; return; }

    Apply &a = applies[idx];
    cout << "Type=" << typeName(a.type) << " UID=" << a.uid << "\n";

    int op;
    cout << "1=approve, 2=reject : ";
    cin >> op;

    cout << "feedback: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string fb; getline(cin, fb); fb=trim(fb);

    if(op==1){
        a.status = 1;
        double auto_sc = calcScore(a);
        cout << "auto score = " << fixed << setprecision(2) << auto_sc << "\n";
        cout.unsetf(std::ios::floatfield);

        cout << "override score? (enter -1 keep auto): ";
        double x; cin >> x;
        if(x < -0.5) a.score = auto_sc;
        else a.score = x;

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

    struct Row{ ll uid; string name; ll cid; double p,j,f,t; };
    vector<Row> rows;
    for(auto &u: users){
        if(u.role!=0) continue;
        Row r;
        r.uid=u.uid; r.name=u.name; r.cid=u.cid;
        r.p=sp[u.uid]; r.j=sj[u.uid]; r.f=sf[u.uid]; r.t=st[u.uid];
        rows.push_back(r);
    }

    sort(rows.begin(), rows.end(), [](const Row& a, const Row& b){
        if(a.t!=b.t) return a.t>b.t;
        return a.uid<b.uid;
    });

    line();
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
        if(u.role!=0) continue;
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
    cout << "90. Save\n";
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
    cout << "90. Save\n";
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
        if(!login()) continue;

        if(cur_role==0){
            while(1){
                menuTeacher();
                int x; cin >> x;
                if(x==0){ logout(); break; }
                if(x==90){ saveAll(); cout << "Saved.\n"; continue; }
                if(x==1) submitPaper();
                else if(x==2) submitProject();
                else if(x==3) submitFund();
                else if(x==4) showAppliesFiltered([](const Apply& a){ return a.uid==cur_uid; });
                else if(x==5) showAppliesFiltered([](const Apply& a){ return a.uid==cur_uid && a.status==1; });
                else cout << "Invalid.\n";
            }
        }else{
            while(1){
                menuAdmin();
                int x; cin >> x;
                if(x==0){ logout(); break; }
                if(x==90){ saveAll(); cout << "Saved.\n"; continue; }

                if(x==1) showColleges();
                else if(x==2) addCollege();
                else if(x==3) delCollege();
                else if(x==4) showUsers();
                else if(x==5) addTeacherUser();
                else if(x==6) showAppliesFiltered([](const Apply&){ return true; });
                else if(x==7) showAppliesFiltered([](const Apply& a){ return a.status==0; });
                else if(x==8) reviewOne();
                else if(x==9) statsTeacher();
                else if(x==10) statsCollege();
                else cout << "Invalid.\n";
            }
        }
    }

    return 0;
}
