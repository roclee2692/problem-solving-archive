#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

void bubblesort(vector<int>& arr){
    int n=arr.size();
    for(int i=0;i<n-1;i++){
        bool swapped=false;
        for(int j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
            //外层循环控制排序的轮数。
// 内层循环遍历数组，并将相邻两个数比较，
// 如果前一个大于后一个，则交换。
// 使用 swapped 标志来判断本轮是否发生交换，
// 若没有交换，说明数组已排序，直接结束循环，可以提高效率。
                swap(arr[j],arr[j+1]);
                swapped=true;
            }
        }
        if(!swapped) break; 
    }
}

int main(){
    vector<int> arr={1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    bubblesort(arr);
    for(auto& a:arr){
        cout<<a<<" ";
    }
    return 0;
    }