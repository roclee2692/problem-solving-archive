#include<bits/stdc++.h>
using namespace std;
typedef struct Book{
	int NO;
	string bookname;
	string name;
	int class_number;
	string publicer;
	string time;
	int price;
}Book;//定义结构体

vector<Book> books;//使用vector来存储结构体

void loadBooksFromFile() {//将现存的所有书籍都存到向量books中
	ifstream file("D:\\VS新项目位置\\book\\books.dat", ios::binary);
	if (file.is_open()) {
		Book temp;
		while (file.read(reinterpret_cast<char*>(&temp), sizeof(Book))) {
			books.push_back(temp);
		}
		file.close();
	}
	else {
		cout << "打开文件失败！" << endl;
		exit(0);
	}
}

bool cmp(Book x,Book y) {
	return x.NO < y.NO;
}

void saveBooksToFile() {
	// 修改文件路径的转义字符表示
	ofstream file("D:\\VS新项目位置\\book\\books.dat", ios::binary | ios::trunc);
	if (!file.is_open()) {
		cerr << "无法打开文件进行写入，可能原因：文件路径不存在、权限不足等，请检查。" << endl;
		return;
	}
	for (Book& res : books) {
		file.write(reinterpret_cast<char*>(&res), sizeof(Book));
	}
	file.close();
}

void add_book() {//用于录用信息
	Book newbook;
	cout << "请输入登录号：" << endl;
	cin>>newbook.NO;
	cout << "请输入书名：" << endl;
	cin >> newbook.bookname;
	cout << "请输入作者名字：" << endl;
	cin >> newbook.name;
	cout << "请输入分类号：" << endl;
	cin >> newbook.class_number;
	cout << "请输出出版单位：" << endl;
	cin >> newbook.publicer;
	cout << "请输出出版时间（按20010101格式）："<<endl;
	while (cin >> newbook.time) {
		if (newbook.time.size() != 8) {
			cout << "格式有误，请再次输入：" << endl;
		}
		else {
			break;
		}
	}
	cout << "请输入出版价格：" << endl;
	cin >> newbook.price;
	books.push_back(newbook);
	saveBooksToFile();
	cout << "书籍信息录入完成！";
}
void out_all_information() {//用于输出所有的图书的信息
	cout << "登录号\t" << "书名\t" << "作者名\t" << "分类号\t" << "出版单位\t" << "出版时间\t" << "价格\t" << endl;
	for (size_t i = 0; i < books.size(); i++) {
		cout << books[i].NO << "\t" << books[i].bookname << "\t" << books[i].name << "\t" << books[i].class_number << "\t" <<
			books[i].publicer << "\t" << books[i].time << "\t" << books[i].price << "\t" << endl;
	}
}
void search_book() {//用于实现查询功能

}
void delete_book() {//用于删除书籍

}
int main() {
	loadBooksFromFile();
	printf("请选择你要进行的操作(输入对应数字即可）：\n");
	printf("1.添加书籍\n");
	printf("2.图书信息浏览\n");
	printf("3.图书信息查询\n");
	cout << "4.删除书籍" << endl;
	cout << "5.退出系统" << endl;
	int n;
	while (scanf("%d", &n)) {
		if (n == 1) {
			add_book();
		}
		else if (n == 2) {
			out_all_information();
		}
		else if (n == 3) {
			search_book();
		}
		else if (n == 4) {
			delete_book();
		}
		else if (n == 5) {
			cout << "已成功退出系统" << endl;
			return 0;
		}
		else {
			printf("无效操作，请再次输入有效的数字：");
		}
		sort(books.begin(), books.end(), cmp);
	}
	
}