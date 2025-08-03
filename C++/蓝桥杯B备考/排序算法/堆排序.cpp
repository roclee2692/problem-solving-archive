#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;


// 堆调整（Heapify）：保证以 root 为根的子树满足最大堆性质
void heapify(vector<int>& arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;  // 左子节点
    int right = 2 * root + 2; // 右子节点

    // 比较左右子节点，找到最大的
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 交换并递归调整
    if (largest != root) {
        swap(arr[root], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序函数
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 1. 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. 取出堆顶元素，并重新堆化
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // 交换最大值到数组末尾
        heapify(arr, i, 0);  // 重新调整堆
    }
}


int main(){
    vector<int> arr={1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    heapSort(arr);
    for(auto& a:arr){
        cout<<a<<" ";
    }
    return 0;
    }