#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

 int partition(vector<int>& arr,int low,int high){
    int pivot=arr[low];
    while(low<high){
        while(low<high&&arr[high]>=pivot){
             --high;
        }
          if (low < high) {
            arr[low] = arr[high];  // 交换到左??
        }
 
         while (low < high && arr[low] <= pivot) {
            ++low;
        }
        if (low < high) {
            arr[high] = arr[low];  // 交换到右??
        }
     
    }
    arr[low] = pivot;  // 将基准元素放入最终位??
    return low;  // 返回基准的索??
 }
 int quicksort(vector<int>& arr,int low,int high) {
     if (low < high) {
        int pivotIndex = partition(arr, low, high);  // 分区
        quicksort(arr, low, pivotIndex - 1);  // 递归排序左半部分
        quicksort(arr, pivotIndex + 1, high); // 递归排序右半部分
    }

 }
    int main(){
     vector<int> arr={1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    int n=arr.size();
    quicksort(arr,0,n-1);
    for(auto& a:arr){
        cout<<a<<" ";
    }
    return 0;
    }