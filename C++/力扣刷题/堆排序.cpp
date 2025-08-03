class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
private:
     // 在 [start, end] 区间内，对 nums 做下沉操作，构建大根堆
     void shiftDown(vector<int> &nums,int s,int e){
        int root=s;
        while(true){  // 左儿子索引
            int l=2*root+1;//based从0开始 
            int r=l+1;
            if(l>e) break;
            if(r<=e&&nums[r]>nums[l]) l=r;
            // 如果子节点更大，则交换，并继续向下
            if(nums[l]>nums[root]){
                swap(nums[l],nums[root]);
                root=l;
            }else break;

        }
     }
 
     void heapSort(vector<int> &nums){
        int n=nums.size();
         // 1. 建堆：从最后一个非叶子节点开始
        for(int s=(n-2)/2;s>=0;s--){//n-1=i为索引 i-1才是最后叶结点的父节点         
        shiftDown(nums,s,n-1);
        }
  // 2. 排序：将堆顶与末尾交换，缩小堆范围，下沉堆顶
        for(int e=n-1;e>0;e--){
            swap(nums[0],nums[e]);
            shiftDown(nums,0,e-1);
        }
     }
};