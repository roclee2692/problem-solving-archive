// 教师科研工作量管理系统
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<functional>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<limits>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

//数据结构
struct College{ll cid;string name;};
struct User{ll uid;ll cid;string name;string pwd;ll role;};//role:0教师1管理员
struct Apply{//申请 status:0待审1通过2驳回 type:1论文2项目3经费
    ll aid,type,uid,year;
    string title,level;
    ll ord;double amount;
    ll status;double score;string feedback;
};

//全局数据
vector<College>colleges;
vector<User>users;
vector<Apply>applies;
const string F_COL="colleges.txt",F_USR="users.txt",F_APL="applies.txt",F_RULE="score_rules.txt";
ll cur_uid=-1,cur_role=-1;//当前登录
unordered_map<string,double>scoreRules;//计分规则表

//工具函数
static inline void line(){cout<<"----------------------------------------\n";}
vector<string> splitByBar(const string&s){
    vector<string>p;string cur;
    for(char c:s){if(c=='|'){p.push_back(cur);cur.clear();}else cur.push_back(c);}
    p.push_back(cur);return p;
}
string trim(const string&s){
    int l=0,r=(int)s.size()-1;
    while(l<=r&&isspace((unsigned char)s[l]))l++;
    while(l<=r&&isspace((unsigned char)s[r]))r--;
    if(l>r)return "";
    return s.substr(l,r-l+1);
}
int findCollegeIdx(ll cid){for(int i=0;i<(int)colleges.size();i++)if(colleges[i].cid==cid)return i;return -1;}
int findUserIdx(ll uid){for(int i=0;i<(int)users.size();i++)if(users[i].uid==uid)return i;return -1;}
int findApplyIdx(ll aid){for(int i=0;i<(int)applies.size();i++)if(applies[i].aid==aid)return i;return -1;}
ll nextApplyId(){ll mx=0;for(auto&a:applies)mx=max(mx,a.aid);return mx+1;}

//规则驱动计分(创新点)
void loadScoreRules(){
    scoreRules.clear();
    ifstream fin(F_RULE);
    if(!fin.is_open()){
        cout<<"[警告]规则文件不存在,使用默认规则\n";
        scoreRules["paper|national"]=30;scoreRules["paper|provincial"]=20;
        scoreRules["paper|school"]=10;scoreRules["paper|other"]=8;
        scoreRules["paper_order|1"]=1.0;scoreRules["paper_order|2"]=0.7;
        scoreRules["paper_order|3"]=0.5;scoreRules["paper_order|other"]=0.3;
        scoreRules["project|national"]=50;scoreRules["project|provincial"]=35;
        scoreRules["project|school"]=20;scoreRules["project|other"]=15;
        scoreRules["project_order|1"]=1.0;scoreRules["project_order|2"]=0.6;
        scoreRules["project_order|3"]=0.4;scoreRules["project_order|other"]=0.25;
        scoreRules["fund|rate"]=1.0;scoreRules["fund|max"]=50.0;
        return;
    }
    string line;
    while(getline(fin,line)){
        line=trim(line);
        if(line.empty()||line[0]=='#')continue;
        auto parts=splitByBar(line);
        if(parts.size()<3)continue;//格式检查
        string type=trim(parts[0]),key=trim(parts[1]);
        double value=stod(trim(parts[2]));
        if(type=="fund"){
            scoreRules["fund|rate"]=value;
            if(parts.size()>=3)scoreRules["fund|max"]=stod(trim(parts[2]));
        }else scoreRules[type+"|"+key]=value;
    }
    fin.close();
    cout<<"[系统]已加载"<<scoreRules.size()<<"条计分规则\n";
}
double getRule(const string&key,double defaultVal=0){
    if(scoreRules.count(key))return scoreRules[key];
    return defaultVal;
}
double scorePaper(const string&level,ll ord){
    double base=getRule("paper|"+level,8.0);
    string ordKey=(ord<=3)?to_string(ord):"other";
    return base*getRule("paper_order|"+ordKey,0.3);
}
double scoreProject(const string&level,ll ord){
    double base=getRule("project|"+level,15.0);
    string ordKey=(ord<=3)?to_string(ord):"other";
    return base*getRule("project_order|"+ordKey,0.25);
}
double scoreFund(double amount){
    double rate=getRule("fund|rate",1.0),maxScore=getRule("fund|max",50.0);
    double sc=amount/10000.0*rate;
    if(sc>maxScore)sc=maxScore;
    if(sc<0)sc=0;
    return sc;
}
double calcScore(const Apply&a){
    if(a.type==1)return scorePaper(a.level,a.ord);
    if(a.type==2)return scoreProject(a.level,a.ord);
    if(a.type==3)return scoreFund(a.amount);
    return 0;
}

//文件读写
void loadColleges(){
    colleges.clear();
    ifstream fin(F_COL);
    if(!fin.is_open())return;
    string s;
    while(getline(fin,s)){
        if(trim(s).empty())continue;
        auto p=splitByBar(s);
        if((int)p.size()!=2)continue;
        College c;c.cid=stoll(p[0]);c.name=p[1];
        colleges.push_back(c);
    }
    fin.close();
}
void saveColleges(){//写入
    ofstream fout(F_COL);
    for(auto&c:colleges)fout<<c.cid<<"|"<<c.name<<"\n";
    fout.close();
}
void loadUsers(){
    users.clear();
    ifstream fin(F_USR);
    if(!fin.is_open())return;
    string s;
    while(getline(fin,s)){
        if(trim(s).empty())continue;
        auto p=splitByBar(s);
        if((int)p.size()!=5)continue;
        User u;u.uid=stoll(p[0]);u.cid=stoll(p[1]);u.name=p[2];u.pwd=p[3];u.role=stoll(p[4]);
        users.push_back(u);
    }
    fin.close();
}
void saveUsers(){
    ofstream fout(F_USR);
    for(auto&u:users)fout<<u.uid<<"|"<<u.cid<<"|"<<u.name<<"|"<<u.pwd<<"|"<<u.role<<"\n";
    fout.close();
}
void loadApplies(){
    applies.clear();
    ifstream fin(F_APL);
    if(!fin.is_open())return;
    string s;
    while(getline(fin,s)){
        if(trim(s).empty())continue;
        auto p=splitByBar(s);
        if((int)p.size()!=11)continue;
        Apply a;a.aid=stoll(p[0]);a.type=stoll(p[1]);a.uid=stoll(p[2]);a.year=stoll(p[3]);
        a.title=p[4];a.level=p[5];a.ord=stoll(p[6]);a.amount=stod(p[7]);
        a.status=stoll(p[8]);a.score=stod(p[9]);a.feedback=p[10];
        applies.push_back(a);
    }
    fin.close();
}
void saveApplies(){
    ofstream fout(F_APL);
    for(auto&a:applies){
        fout<<a.aid<<"|"<<a.type<<"|"<<a.uid<<"|"<<a.year<<"|"
            <<a.title<<"|"<<a.level<<"|"<<a.ord<<"|"<<a.amount<<"|"
            <<a.status<<"|"<<a.score<<"|"<<a.feedback<<"\n";
    }
    fout.close();
}
void loadAll(){loadColleges();loadUsers();loadApplies();loadScoreRules();}
void saveAll(){saveColleges();saveUsers();saveApplies();}

//查询显示
void showColleges(){
    line();
    cout<<left<<setw(10)<<"CID"<<setw(20)<<"Name"<<"\n";
    line();
    for(auto&c:colleges)cout<<left<<setw(10)<<c.cid<<setw(20)<<c.name<<"\n";
    line();
}
void showUsers(){
    line();
    cout<<left<<setw(10)<<"UID"<<setw(10)<<"CID"<<setw(15)<<"Name"<<setw(15)<<"Role"<<"\n";
    line();
    for(auto&u:users){
        cout<<left<<setw(10)<<u.uid<<setw(10)<<u.cid<<setw(15)<<u.name
            <<setw(15)<<(u.role==0?"Teacher":"Admin")<<"\n";
    }
    line();
}
void showAppliesFiltered(function<bool(const Apply&)>filter){
    line();
    cout<<left<<setw(6)<<"AID"<<setw(6)<<"Type"<<setw(8)<<"UID"<<setw(6)<<"Year"
        <<setw(20)<<"Title"<<setw(12)<<"Level"<<setw(5)<<"Ord"<<setw(10)<<"Amount"
        <<setw(8)<<"Status"<<setw(8)<<"Score"<<"\n";
    line();
    for(auto&a:applies){
        if(!filter(a))continue;
        string stype=(a.type==1?"Paper":(a.type==2?"Project":"Fund"));
        string sstatus=(a.status==0?"Pending":(a.status==1?"Pass":"Reject"));
        cout<<left<<setw(6)<<a.aid<<setw(6)<<stype<<setw(8)<<a.uid<<setw(6)<<a.year;
        if(a.type!=3){
            cout<<setw(20)<<a.title<<setw(12)<<a.level<<setw(5)<<a.ord<<setw(10)<<"-";
        }else{
            cout<<setw(20)<<"-"<<setw(12)<<"-"<<setw(5)<<"-"<<setw(10)<<a.amount;
        }
        cout<<setw(8)<<sstatus<<fixed<<setprecision(2)<<a.score<<"\n";
    }
    line();
}

//登录登出
bool login(){
    ll uid;string pwd;
    cout<<"用户ID：";cin>>uid;
    cout<<"密码：";cin>>pwd;
    int idx=findUserIdx(uid);
    if(idx==-1||users[idx].pwd!=pwd){cout<<"登录失败。\n";return false;}
    cur_uid=uid;cur_role=users[idx].role;
    cout<<"欢迎，"<<users[idx].name<<"！\n";
    return true;
}
void logout(){cur_uid=-1;cur_role=-1;cout<<"已退出登录。\n";}

//增删改学院
void addCollege(){
    College c;
    cout<<"学院ID：";cin>>c.cid;
    if(findCollegeIdx(c.cid)!=-1){cout<<"学院ID已存在。\n";return;}
    cout<<"学院名称：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,c.name);c.name=trim(c.name);
    colleges.push_back(c);
    cout<<"添加成功。\n";
}
void delCollege(){
    ll cid;cout<<"要删除的学院ID：";cin>>cid;
    int idx=findCollegeIdx(cid);
    if(idx==-1){cout<<"未找到该学院。\n";return;}
    colleges.erase(colleges.begin()+idx);
    cout<<"删除成功。\n";
}
void editCollege(){
    ll cid;cout<<"要编辑的学院ID：";cin>>cid;
    int idx=findCollegeIdx(cid);
    if(idx==-1){cout<<"未找到该学院。\n";return;}
    cout<<"当前名称："<<colleges[idx].name<<"\n";
    cout<<"新名称（直接回车保持不变）：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    string newName;getline(cin,newName);newName=trim(newName);
    if(!newName.empty()){colleges[idx].name=newName;cout<<"更新成功。\n";}
    else cout<<"未修改。\n";
}

//增删改教师
void addTeacherUser(){
    User u;u.role=0;
    cout<<"教师ID：";cin>>u.uid;
    if(findUserIdx(u.uid)!=-1){cout<<"教师ID已存在。\n";return;}
    cout<<"学院ID：";cin>>u.cid;
    if(findCollegeIdx(u.cid)==-1)cout<<"警告：学院ID未找到。\n";
    cout<<"姓名：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,u.name);u.name=trim(u.name);
    cout<<"密码：";
    getline(cin,u.pwd);u.pwd=trim(u.pwd);
    users.push_back(u);
    cout<<"添加成功。\n";
}
void delTeacherUser(){
    ll uid;cout<<"要删除的教师ID：";cin>>uid;
    int idx=findUserIdx(uid);
    if(idx==-1||users[idx].role!=0){cout<<"未找到该教师或该用户为管理员。\n";return;}
    users.erase(users.begin()+idx);
    cout<<"删除成功。\n";
}
void editTeacherUser(){
    ll uid;cout<<"要编辑的教师ID：";cin>>uid;
    int idx=findUserIdx(uid);
    if(idx==-1||users[idx].role!=0){cout<<"未找到该教师或该用户为管理员。\n";return;}
    cout<<"当前信息：\n";
    cout<<"  姓名："<<users[idx].name<<"\n";
    cout<<"  学院ID："<<users[idx].cid<<"\n";
    cout<<"  密码："<<users[idx].pwd<<"\n\n";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"新姓名（直接回车保持不变）：";
    string newName;getline(cin,newName);newName=trim(newName);
    if(!newName.empty())users[idx].name=newName;
    cout<<"新学院ID（直接回车保持不变）：";
    string cidStr;getline(cin,cidStr);cidStr=trim(cidStr);
    if(!cidStr.empty()){
        ll newCid=stoll(cidStr);
        if(findCollegeIdx(newCid)!=-1)users[idx].cid=newCid;
        else cout<<"[警告]学院ID "<<newCid<<" 未找到，学院ID未修改。\n";
    }
    cout<<"新密码（直接回车保持不变）：";
    string newPwd;getline(cin,newPwd);newPwd=trim(newPwd);
    if(!newPwd.empty())users[idx].pwd=newPwd;
    cout<<"更新成功。\n";
}

//教师提交申请
void submitPaper(){
    Apply a;a.aid=nextApplyId();a.type=1;a.uid=cur_uid;
    cout<<"年份：";cin>>a.year;
    cout<<"论文标题：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,a.title);a.title=trim(a.title);
    cout<<"级别（如national/provincial/school）：";
    getline(cin,a.level);a.level=trim(a.level);
    cout<<"作者顺序（第几作者）：";cin>>a.ord;
    a.amount=0;a.status=0;a.score=0;
    applies.push_back(a);
    cout<<"提交成功。申请ID="<<a.aid<<"\n";
}
void submitProject(){
    Apply a;a.aid=nextApplyId();a.type=2;a.uid=cur_uid;
    cout<<"年份：";cin>>a.year;
    cout<<"项目标题：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,a.title);a.title=trim(a.title);
    cout<<"级别（如national/provincial/school）：";
    getline(cin,a.level);a.level=trim(a.level);
    cout<<"负责人顺序（第几负责人）：";cin>>a.ord;
    a.amount=0;a.status=0;a.score=0;
    applies.push_back(a);
    cout<<"提交成功。申请ID="<<a.aid<<"\n";
}
void submitFund(){
    Apply a;a.aid=nextApplyId();a.type=3;a.uid=cur_uid;
    cout<<"年份：";cin>>a.year;
    cout<<"经费金额（元）：";cin>>a.amount;
    a.ord=0;a.status=0;a.score=0;
    applies.push_back(a);
    cout<<"提交成功。申请ID="<<a.aid<<"\n";
}

//管理员审核
void reviewOne(){
    ll aid;cout<<"要审核的申请ID：";cin>>aid;
    int idx=findApplyIdx(aid);
    if(idx==-1){cout<<"未找到该申请。\n";return;}
    Apply&a=applies[idx];
    if(a.status!=0){cout<<"该申请已审核过。\n";return;}
    line();
    cout<<"申请ID："<<a.aid<<" 类型："<<(a.type==1?"论文":(a.type==2?"项目":"经费"))
        <<" 教师ID："<<a.uid<<" 年份："<<a.year<<"\n";
    if(a.type!=3)cout<<"标题："<<a.title<<" 级别："<<a.level<<" 顺序："<<a.ord<<"\n";
    else cout<<"金额："<<a.amount<<"\n";
    double autoScore=calcScore(a);
    cout<<"自动计算分数："<<fixed<<setprecision(2)<<autoScore<<"\n";
    line();
    cout<<"是否通过？（1=通过，2=驳回）：";
    int st;cin>>st;
    if(st!=1&&st!=2){cout<<"输入无效。\n";return;}
    a.status=st;
    if(st==1){
        cout<<"输入最终分数（输入-1使用自动分数）：";
        double x;cin>>x;
        cout.unsetf(ios::floatfield);
        if(x<-0.5)a.score=autoScore;
        else a.score=x;
    }else a.score=0;
    cout<<"反馈意见：";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,a.feedback);a.feedback=trim(a.feedback);
    cout<<"审核完成。\n";
}

//统计教师
void statsTeacher(){
    unordered_map<ll,double>tscore;
    for(auto&a:applies)if(a.status==1)tscore[a.uid]+=a.score;
    struct Row{ll uid;string name;double sum;};
    vector<Row>rows;
    for(auto&u:users){
        if(u.role!=0)continue;
        Row r{u.uid,u.name,tscore[u.uid]};
        rows.push_back(r);
    }
    sort(rows.begin(),rows.end(),[](const Row&a,const Row&b){
        if(a.sum!=b.sum)return a.sum>b.sum;
        return a.uid<b.uid;
    });
    line();
    cout<<left<<setw(10)<<"UID"<<setw(20)<<"Name"<<"TotalScore\n";
    line();
    for(auto&r:rows)cout<<left<<setw(10)<<r.uid<<setw(20)<<r.name<<fixed<<setprecision(2)<<r.sum<<"\n";
    line();
}

//统计学院
void statsCollege(){
    unordered_map<ll,double>tscore;
    for(auto&a:applies)if(a.status==1)tscore[a.uid]+=a.score;
    unordered_map<ll,double>csum;
    for(auto&u:users){if(u.role!=0)continue;csum[u.cid]+=tscore[u.uid];}
    struct Row{ll cid;string name;double sum;};
    vector<Row>rows;
    for(auto&c:colleges){Row r{c.cid,c.name,csum[c.cid]};rows.push_back(r);}
    sort(rows.begin(),rows.end(),[](const Row&a,const Row&b){
        if(a.sum!=b.sum)return a.sum>b.sum;
        return a.cid<b.cid;
    });
    line();
    cout<<left<<setw(8)<<"CID"<<setw(20)<<"College"<<"TotalScore\n";
    line();
    for(auto&r:rows)cout<<left<<setw(8)<<r.cid<<setw(20)<<r.name<<fixed<<setprecision(2)<<r.sum<<"\n";
    line();
}

//菜单
void menuTeacher(){
    cout<<"\n=== 教师菜单 ===\n";
    cout<<"1.提交论文申请\n2.提交项目申请\n3.提交经费申请\n";
    cout<<"4.查看我的所有申请\n5.查看我的已通过申请\n";
    cout<<"s.保存数据\n0.退出登录\n请选择：";
}
void menuAdmin(){
    cout<<"\n=== 管理员菜单 ===\n";
    cout<<"1.显示所有学院\n2.添加学院\n3.删除学院\n4.编辑学院\n";
    cout<<"5.显示所有用户\n6.添加教师\n7.编辑教师信息\n";
    cout<<"8.显示所有申请\n9.显示待审核申请\n10.审核单个申请\n";
    cout<<"11.按教师统计\n12.按学院统计\n";
    cout<<"s.保存数据\n0.退出登录\n请选择：";
}

//主程序
int main(){
    loadAll();
    while(1){
        cout<<"\n=== 教师科研工作量管理系统 ===\n1.登录\n0.退出系统\n请选择：";
        int op;cin>>op;
        if(op==0)break;
        if(op!=1)continue;
        if(!login())continue;
        if(cur_role==0){//教师
            while(1){
                menuTeacher();
                string input;cin>>input;
                if(input=="0"){logout();break;}
                if(input=="s"||input=="S"){saveAll();cout<<"数据已保存。\n";continue;}
                int x=(input.size()==1&&input[0]>='0'&&input[0]<='9')?(input[0]-'0'):-1;
                if(x==1)submitPaper();
                else if(x==2)submitProject();
                else if(x==3)submitFund();
                else if(x==4)showAppliesFiltered([](const Apply&a){return a.uid==cur_uid;});
                else if(x==5)showAppliesFiltered([](const Apply&a){return a.uid==cur_uid&&a.status==1;});
                else cout<<"输入无效。\n";
            }
        }else{//管理员
            while(1){
                menuAdmin();
                string input;cin>>input;
                if(input=="0"){logout();break;}
                if(input=="s"||input=="S"){saveAll();cout<<"数据已保存。\n";continue;}
                int x=-1;
                if(input=="10")x=10;
                else if(input=="11")x=11;
                else if(input=="12")x=12;
                else if(input.size()==1&&input[0]>='0'&&input[0]<='9')x=input[0]-'0';
                if(x==1)showColleges();
                else if(x==2)addCollege();
                else if(x==3)delCollege();
                else if(x==4)editCollege();
                else if(x==5)showUsers();
                else if(x==6)addTeacherUser();
                else if(x==7)editTeacherUser();
                else if(x==8)showAppliesFiltered([](const Apply&){return true;});
                else if(x==9)showAppliesFiltered([](const Apply&a){return a.status==0;});
                else if(x==10)reviewOne();
                else if(x==11)statsTeacher();
                else if(x==12)statsCollege();
                else cout<<"输入无效。\n";
            }
        }
    }
    return 0;
}
