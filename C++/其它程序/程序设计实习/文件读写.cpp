#include <fstream>   // 文件流：ifstream(读) ofstream(写) fstream(读写)
#include <iomanip>   // 输出格式控制：setprecision fixed setw setfill
#include <iostream>  // 标准输入输出：cin cout cerr
#include <string>    // 字符串类 string 及相关操作
#include <vector>    // 动态数组容器 vector
#include <direct.h>  // Windows 目录操作：_getcwd _chdir _mkdir (MinGW 8.1 兼容)
//注：<filesystem> 需要 C++17，MinGW 8.1 支持不好，故用 <direct.h>
using namespace std;

struct Student {
    string id;
    string name;
    float s1,s2,s3;
    float sum;
};

const int N=5;// 学生人数

int main(){
    // 交互式程序不要用 sync(0) 和 tie(0)，否则提示语会延迟显示
    // ios::sync_with_stdio(0);
    // cin.tie(0);

    vector<Student> a(N);
    // 输入学生信息
    //姓名如果可能有空格，用 getline；这里按一般无空格处理
    for(int i=0;i<N;i++){
        cout<<"输入学生 "<<i+1<<" id name score1 score2 score3:\n";
        cin>>a[i].id>>a[i].name>>a[i].s1>>a[i].s2>>a[i].s3;
        a[i].sum = a[i].s1 + a[i].s2 + a[i].s3;
    }

    // 写入文件
    ofstream fout("stu.txt");//fout 变量 持有一个文件流对象
    if(!fout){
        cerr<<"无法打开文件进行写入\n";//无缓冲 报错输出
        return 1;
    }
    fout<<"ID Name Score1 Score2 Score3 Sum\n";  // 表头
    fout<<fixed<<setprecision(2);//setw 每次都要写一遍；fixed/setprecision/left/setfill 通常设置一次就持续生效。

    for(int i=0;i<N;i++ ){
        fout<<a[i].id<<' '
            <<a[i].name<<' '
            <<a[i].s1<<' '
            <<a[i].s2<<' '
            <<a[i].s3<<' '
            <<a[i].sum<<'\n';
    }
    fout.close();
    
    // 显示文件完整路径（文件保存为 UTF-8 即可正常显示中文）
    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    cout<<"\n文件已写入: "<<cwd<<"\\stu.txt\n";

    //从文件读出并输出
    ifstream fin("stu.txt");
    if(!fin.is_open()){
        cerr<<"无法打开文件进行读出\n";
        return 1;
    }

    cout<<"\n===== Content of stu.txt =====\n";
    // 直接整行输出  避免格式变动读崩
    string line;
    while(getline(fin,line)){
        cout<<line<<'\n';
    }
    fin.close();
    
    cout<<"\n当前工作目录: "<<cwd<<"\n";
    return 0;
}