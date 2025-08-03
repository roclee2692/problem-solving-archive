#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countingSortWithNegative(vector<int>& arr) {
    if (arr.empty()) return;

    // 找到最大值和最小值
    int minVal = *min_element(arr.begin(), arr.end());
    int maxVal = *max_element(arr.begin(), arr.end());

    // 偏移量（使所有元素非负）
    int offset = abs(minVal);
    vector<int> count(maxVal + offset + 1, 0);
    vector<int> output(arr.size());

    // 统计元素出现次数
    for (int num : arr) {
        count[num + offset]++;
    }

    // 累加前缀和
    for (int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }

    // 反向遍历，保证稳定性
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] + offset] - 1] = arr[i];
        count[arr[i] + offset]--;
    }

    // 复制回原数组
    arr = output;
}

// 测试代码
int main() {
    vector<int> arr = {4, -2, 2, -8, 3, 3, -1, 6, 5, -9};
    countingSortWithNegative(arr);

    for (int num : arr) {
        cout << num << " ";
    }
    return 0;
}
