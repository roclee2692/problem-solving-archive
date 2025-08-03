#include <iostream>
#include <vector>
#include <cstdlib>  // 用于 `rand()`
using namespace std;

class Solution {
public:
    int quickSelect(vector<int>& nums, int left, int right, int k) {
        int pivotIndex = partition(nums, left, right);
        
        if (pivotIndex == k) {
            return nums[pivotIndex];  // 找到目标元素
        } else if (pivotIndex > k) {
            return quickSelect(nums, left, pivotIndex - 1, k);  // 在左侧查找
        } else {
            return quickSelect(nums, pivotIndex + 1, right, k);  // 在右侧查找
        }
    }

    int partition(vector<int>& nums, int left, int right) {
        int pivotIndex = left + rand() % (right - left + 1);  // 随机选择 pivot
        int pivot = nums[pivotIndex];
        swap(nums[pivotIndex], nums[right]);  // 把 pivot 移到末尾

        int storeIndex = left;
        for (int i = left; i < right; i++) {
            if (nums[i] > pivot) {  // 降序排列
                swap(nums[i], nums[storeIndex]);
                storeIndex++;
            }
        }
        swap(nums[storeIndex], nums[right]);  // 交换 pivot 到最终位置
        return storeIndex;
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size() - 1, k - 1);
    }
};

// 测试
int main() {
    Solution sol;
    vector<int> nums1 = {3,2,1,5,6,4};
    cout << sol.findKthLargest(nums1, 2) << endl;  // 输出 5

    vector<int> nums2 = {3,2,3,1,2,4,5,5,6};
    cout << sol.findKthLargest(nums2, 4) << endl;  // 输出 4

    return 0;
}
