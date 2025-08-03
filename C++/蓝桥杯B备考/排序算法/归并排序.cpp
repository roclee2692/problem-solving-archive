#include <iostream>
#include <vector>

using namespace std;

// 归并函数：合并两个有序数组
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp; // 临时数组
    int i = left, j = mid + 1;

    // 归并两个有序部分
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            temp.push_back(arr[j++]);
        }
    }

    // 复制剩余元素（如果有）
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);

    // 复制回原数组
    for (int k = 0; k < temp.size(); k++) {
        arr[left + k] = temp[k];
    }
}

// 归并排序（递归）
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return; // 递归终止条件

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);       // 排序左半部分
    mergeSort(arr, mid + 1, right);  // 排序右半部分
    merge(arr, left, mid, right);    // 合并左右两部分
}

// 测试归并排序
int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5, 6, 4, 3, 2};
    
    cout << "原数组: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    mergeSort(arr, 0, arr.size() - 1);

    cout << "排序后: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
