#include <iostream>
#include <vector>
#include <cstdlib>  // 用于随机数生成
#include <ctime>

using namespace std;

// Hoare 分区法
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];  // 选择最左边的元素作为基准
    int left = low - 1, right = high + 1;

    while (true) {
        // 从右往左找到第一个小于 pivot 的元素
        do {
            right--;
        } while (arr[right] > pivot);

        // 从左往右找到第一个大于 pivot 的元素
        do {
            left++;
        } while (arr[left] < pivot);

        // 如果左右指针交错，返回当前右指针位置
        if (left >= right)
            return right;

        swap(arr[left], arr[right]);
    }
}

// 随机化分区，减少最坏情况发生的概率
int randomized_partition(vector<int>& arr, int low, int high) {
    int random_idx = low + rand() % (high - low + 1);
    swap(arr[low], arr[random_idx]); // 交换基准元素
    return partition(arr, low, high);
}

// 快速排序函数
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = randomized_partition(arr, low, high);
        quickSort(arr, low, pivotIndex);   // 递归左半部分
        quickSort(arr, pivotIndex + 1, high); // 递归右半部分
    }
}

// 测试快速排序
int main() {
    srand(time(0)); // 随机种子，保证不同运行时基准随机

    vector<int> arr = {34, 7, 23, 32, 5, 62, 32, 19};
    cout << "原数组: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    quickSort(arr, 0, arr.size() - 1);

    cout << "排序后: ";
    for (int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
