#include <bits/stdc++.h>
using namespace std;

struct Student {
    int num;
    string name;
    string sex;
    double s;
};
//PowerShell 中括号 () 有特殊含义（函数调用、子表达式）
void caidan() {
    cout << "\n========= 学生信息管理系统 =========\n";
    cout << "1. 输入n个学生信息(学号 姓名 性别 成绩)\n";
    cout << "2. 输出所有学生信息(按成绩排序)\n";
    cout << "3. 输出成绩最高的学生信息\n";
    cout << "4. 查询(按学号或姓名)\n";
    cout << "5. 退出\n";
    cout << "===================================\n";
    cout << "请选择: ";
}

void input(vector<Student> &stu, int &m) {
    cout << "请输入学生个数 n(<=20): ";
    cin >> m;
    if (m < 0) m = 0;
    if (m > 20) m = 20;

    stu.resize(m);

    cout << "按行输入: 学号 姓名 性别 成绩\n";
    for (int i = 0; i < m; i++) {
        cin >> stu[i].num >> stu[i].name >> stu[i].sex >> stu[i].s;
    }
    cout << "录入完成。\n";
}

void output(vector<Student> &stu, int m) {
    if (m <= 0) { cout << "还没有数据，请先录入。\n"; return; }

    int p;
    cout << "请选择排序方式: 1-降序 2-升序: ";
    cin >> p;

    // 冒泡排序（模仿老师写法）
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            bool needSwap = false;
            if (p == 2) { // 升序
                if (stu[j].s > stu[j + 1].s) needSwap = true;
            } else {      // 默认降序
                if (stu[j].s < stu[j + 1].s) needSwap = true;
            }
            if (needSwap) swap(stu[j], stu[j + 1]);
        }
    }

    cout << "\n学号\t姓名\t性别\t成绩\n";
    for (int i = 0; i < m; i++) {
        cout << stu[i].num << "\t" << stu[i].name << "\t"
             << stu[i].sex << "\t" << fixed << setprecision(1) << stu[i].s << "\n";
    }
}

void hp(const vector<Student> &stu, int m) {
    if (m <= 0) { cout << "还没有数据，请先录入。\n"; return; }

    int q = 0;
    for (int i = 1; i < m; i++) {
        if (stu[i].s > stu[q].s) q = i;
    }

    cout << "\n最高分学生:\n";
    cout << "学号\t姓名\t性别\t成绩\n";
    cout << stu[q].num << "\t" << stu[q].name << "\t"
         << stu[q].sex << "\t" << fixed << setprecision(1) << stu[q].s << "\n";
}

void chaxun(const vector<Student> &stu, int m) {
    if (m <= 0) { cout << "还没有数据，请先录入。\n"; return; }

    int a;
    cout << "1-按姓名查  2-按学号查: ";
    cin >> a;

    bool found = false;

    if (a == 1) {
        string key;
        cout << "请输入姓名: ";
        cin >> key;

        for (int i = 0; i < m; i++) {
            if (stu[i].name == key) {
                if (!found) cout << "学号\t姓名\t性别\t成绩\n";
                cout << stu[i].num << "\t" << stu[i].name << "\t"
                     << stu[i].sex << "\t" << fixed << setprecision(1) << stu[i].s << "\n";
                found = true;
            }
        }
    } else {
        int key;
        cout << "请输入学号: ";
        cin >> key;

        for (int i = 0; i < m; i++) {
            if (stu[i].num == key) {
                cout << "学号\t姓名\t性别\t成绩\n";
                cout << stu[i].num << "\t" << stu[i].name << "\t"
                     << stu[i].sex << "\t" << fixed << setprecision(1) << stu[i].s << "\n";
                found = true;
                break;
            }
        }
    }

    if (!found) cout << "未找到。\n";
}

int main() {
    vector<Student> stu;
    int m = 0;
    int choose;

    while (1) {
        caidan();
        cin >> choose;

        switch (choose) {
            case 1: input(stu, m); break;
            case 2: output(stu, m); break;
            case 3: hp(stu, m); break;
            case 4: chaxun(stu, m); break;
            case 5: cout << "谢谢使用，再见！\n"; return 0;
            default: cout << "输入无效，请重试。\n"; break;
        }
    }
}
