#include <iostream>
#include <vector>

using namespace std;

// 分区函数：以最后一个元素作为基准
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;  // i 代表小于 pivot 的区域的最后一个索引

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;  // 先扩大小于 pivot 的区域
            swap(arr[i], arr[j]);  // 交换当前元素到正确位置
        }
    }
    swap(arr[i + 1], arr[high]);  // 最后将 pivot 放到正确位置
    return i + 1;  // 返回 pivot 的最终位置
}

// 快速排序函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);  // 分区
        quickSort(arr, low, pivotIndex - 1);  // 递归排序左半部分
        quickSort(arr, pivotIndex + 1, high); // 递归排序右半部分
    }}

// 主函数，测试快速排序
int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5,1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};  // 测试数据
    quickSort(arr, 0, arr.size() - 1);

    // 输出排序后的数组
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}
