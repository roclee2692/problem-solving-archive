#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        unordered_map<int, int> freq;  // 哈希表用于记录元素出现的频次
        int sum = 0;

        // 统计每个元素的出现次数
        for (int num : nums) {
            freq[num]++;
        }

        // 计算唯一元素的和
        for (auto& entry : freq) {
            if (entry.second == 1) {  // 如果元素只出现一次
                sum += entry.first;
            }
        }

        return sum;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 3, 2};
    cout << solution.sumOfUnique(nums) << endl;  // 输出 4

    return 0;
}
