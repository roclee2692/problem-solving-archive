#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    stack<string> st;
    string line;
    bool ok=1;
    string error="";//error 初始为 " "，永远不为空
    while(getline(cin,line)){//从标准输入 cin 中读取一整行，直到遇到换行符 \n 为止；换行符不会被包含，只把前面的内容读进字符串。
        if(line==".") break;
        for(size_t i=0;i<line.size();i++){
            char c1=line[i];
            char c2 = (i + 1 < line.size()) ? line[i + 1] : '\0'; // ? 安全
            if(c1=='/'&&i+1<line.size()&&c2=='*'){
                st.push("/*");
                i++;// 跳过 *
            }else if(c1=='*'&&i+1<line.size()&&c2=='/'){// 读到 “*/”
                if(!st.empty()&&st.top()=="/*") //直接整个字符串判断即可，无需用数列
              //从栈中取元素之前先判断栈是否为空
                st.pop();  // 正常匹配
                else { // 不匹配 此时有多种情况 栈空 少左边 栈不空 优先处理栈中括号的错误 少右边
                  if (!st.empty())  // 栈非空 ? 缺少右符号
                      error = st.top() + "-?";
                  else  error = "?-*/"; // 栈空   ? 缺少左符号
                    ok=false;
                    goto END;
                }
                i++;//跳过*
            }
            else if(c1=='('||c1=='['||c1=='{') st.push(string(1,c1));//将c1类型强制转化为string 才能入栈
            else if(c1==')'||c1==']'||c1=='}'){
                if(!st.empty()&&//这里要是正常情况下的结果 匹配右括号时逻辑写错成了“或” 只要栈非空就会走 pop，即使栈顶符号根本不匹配也会被弹出。
                   (
                  (c1==')'&&st.top()=="(")||
                  (c1==']'&&st.top()=="[")||
                  (c1=='}'&&st.top()=="{")
                   )//分清是否是中文的括号
                    )st.pop();//处理所有正确的情况
                else{
                      // -------- 核心修正开始 --------
                    if (!st.empty()) {    // 情况 B：栈非空但顶元素不匹配 → 缺少右符号
                     error = st.top() + "-?";
                    } 
                    else {      // 情况 C：栈为空 → 缺少左符号
                    error = "?-" + string(1, c1);
                    }
                    ok = false;
                    goto END;
        // -------- 核心修正结束 --------
                }
            }
        }
    }
END:
    if(ok&&st.empty()){
         cout << "YES" << endl;
    }else{
         cout << "NO" << endl;
      
            if(!error.empty()){   // 情况①：运行时主动发现错误
            cout << error << endl;
            } else if(!st.empty()){ // 情况②：没有主动报错，但栈中还有未闭合的符号
                  cout << st.top() << "-?" << endl;
            }
       
 }
    return 0;
}