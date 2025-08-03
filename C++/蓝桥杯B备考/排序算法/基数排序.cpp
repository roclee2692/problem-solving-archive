#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 获取最大数的位数
int getMaxDigit(const vector<int>& arr) {
    int maxNum = *max_element(arr.begin(), arr.end());
    int digits = 0;
    while (maxNum > 0) {
        maxNum /= 10;
        digits++;
    }
    return digits;
}

// 基数排序（LSD 方式，从最低位到最高位）
void radixSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    int maxDigit = getMaxDigit(arr);  // 获取最大数的位数
    int place = 1;  // 1, 10, 100, ...

    // 逐位排序
    for (int d = 0; d < maxDigit; d++) {
        vector<vector<int>> buckets(10);  // 0-9 号桶

        // 分配到桶
        for (int num : arr) {
            int digit = (num / place) % 10;  // 取当前位数
            buckets[digit].push_back(num);
        }

        // 合并回原数组
        int index = 0;
        for (int i = 0; i < 10; i++) {
            for (int num : buckets[i]) {
                arr[index++] = num;
            }
        }

        place *= 10;  // 进入更高一位
    }
}

// 测试基数排序
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66,1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    radixSort(arr);

    cout << "基数排序后: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
