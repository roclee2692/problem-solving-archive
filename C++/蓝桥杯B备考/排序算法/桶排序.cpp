#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 桶排序（支持 1.2444, 0.1344, 46.244 这种复杂小数 & 整数）
void bucketSort(vector<float>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    // 1. 找到最小值 & 最大值
    float minVal = *min_element(arr.begin(), arr.end());
    float maxVal = *max_element(arr.begin(), arr.end());

    // 避免除零错误
    if (maxVal == minVal) return;

    // 2. 创建 n 个桶（每个桶存储浮点数）
    vector<vector<float>> buckets(n);

    // 3. 归一化并分配元素到桶
    for (float num : arr) {
        int index = (num - minVal) / (maxVal - minVal) * (n - 1);  // 计算桶索引
        buckets[index].push_back(num);
    }

    // 4. 对每个桶内部排序
    for (auto& bucket : buckets) {
        sort(bucket.begin(), bucket.end());
    }

    // 5. 合并所有桶的元素回 arr
    int index = 0;
    for (const auto& bucket : buckets) {
        for (float num : bucket) {
            arr[index++] = num;
        }
    }
}

// 测试桶排序
int main() {
    vector<float> arr = {1.2444, 0.1344, 46.244, 10.23, 2.45, 0.99, 5.67, 33.5, 12.12, 19.8,1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    
    bucketSort(arr);

    cout << "桶排序后: ";
    for (float num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
