#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> generateFibonacci(int n) {
    vector<int> fib(n);
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < n; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    return fib;
}

int main() {
    int n = 15;
    vector<int> fib = generateFibonacci(n);

    cout << "Original Fibonacci numbers:\n";
    for (int num : fib) cout << num << ' ';
    cout << "\n\nSorted in descending order:\n";

    sort(fib.begin(), fib.end(), greater<int>());
    for (int num : fib) cout << num << ' ';
    cout << endl;
    cout<<"你好呀！";
    return 0;
}
