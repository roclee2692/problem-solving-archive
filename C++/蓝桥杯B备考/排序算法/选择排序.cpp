#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;
#include <vector>
#include <algorithm>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // 记录未排序部分中最小元素的索引
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        // 将找到的最小元素交换到当前正确位置
        if (minIndex != i)
            swap(arr[i], arr[minIndex]);
    }
}

    
  
int main(){
     vector<int> arr={1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    selectionSort(arr);
    for(auto& a:arr){
        cout<<a<<" ";
    }
    return 0;
    }