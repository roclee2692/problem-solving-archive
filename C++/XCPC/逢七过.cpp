#include <iostream>
#include <string>
using namespace std;
bool pass(string s,int l){
    for(int i=0;i<l;i++){
        if(s[i]=='7') return true;
    }
    return false;
}
int main(){
int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        bool ok=false;
        string s=to_string(n);
        int l=s.size();
        if(pass(s,l)) cout<<"Pass"<<endl;
        else {
          for(int i=1;i<20;i++){
            if(n==7*i) {
                cout<<"Pass"<<endl;
              ok=true;//为了跳出两层循环必须有一个标记
              break;}//这里的if后的括号不能少，要将后的代码都写入，只有一横代码才能不用{}平时尽量还是写
          }  if(!ok) cout<<n<<endl;
        }
    }
    return 0;
}