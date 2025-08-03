// sum_1e8.cpp
#include <iostream>
#include <chrono>
using namespace std;

int main() {
    long long total = 0;
    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i <= 100000000; ++i) {
        total += i;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "Sum: " << total << endl;
    cout << "Time: " << duration.count() << " seconds" << endl;
    return 0;
}
