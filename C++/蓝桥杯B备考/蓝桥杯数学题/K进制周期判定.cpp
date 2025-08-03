#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 转换N为K进制
string to_base_k(int N, int K) {
    string result = "";
    while (N > 0) {
        result = to_string(N % K) + result;  // 取余数并拼接
        N /= K;
    }
    return result.empty() ? "0" : result;
}

// 判断是否存在周期
bool has_periodicity(const string& s) {
    int len = s.size();
    
    // 检查每个可能的周期长度
    for (int i = 1; i <= len / 2; i++) {
        if (len % i == 0) {
            string sub = s.substr(0, i);//i表示向后读取的长度
            bool valid = true;
            for (int j = i; j < len; j += i) {
                if (s.substr(j, i) != sub) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }
    }
    return false;
}

int main() {
    int N, K;
    cout << "请输入 N 和 K：";
    cin >> N >> K;
    
    // 获取 N 在 K 进制下的表示
    string base_k_rep = to_base_k(N, K);
    
    // 判断是否存在周期性
    if (has_periodicity(base_k_rep)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}
