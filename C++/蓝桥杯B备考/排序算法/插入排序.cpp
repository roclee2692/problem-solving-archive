#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;
 void insertionsort(vector<int>& arr){
    int n=arr.size();
    for(int i=1;i<n;i++){
        int key=arr[i];
        int j=i-1;
        while(j>=0&&arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        } 
        arr[j+1]=key;
    }
 }
    int main(){
     vector<int> arr={1,25,6,4,7,658,696,9,9,86,9,5,7,4,63,2,52,6,3586,5796,3,148,658,7,5645,1,432,52,357,65,856,35,57,4,6,357,46,864,74};
    insertionsort(arr);
    for(auto& a:arr){
        cout<<a<<" ";
    }
    return 0;
    }