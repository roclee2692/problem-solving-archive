#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 结构体表示活动
struct Activity {
    int start, end;
};

// 按结束时间排序
bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

// 活动选择问题的贪心算法
void activitySelection(vector<Activity> &activities) {
    // 按结束时间排序
    sort(activities.begin(), activities.end(), compare);

    cout << "选择的活动序列：" << endl;
    int lastEndTime = 0; // 记录上一个活动的结束时间

    for (const auto &activity : activities) {
        if (activity.start >= lastEndTime) {
            cout << "活动 (" << activity.start << ", " << activity.end << ")" << endl;
            lastEndTime = activity.end; // 更新结束时间
        }
    }
}

int main() {
    vector<Activity> activities = {{1, 3}, {2, 5}, {3, 9}, {6, 8}, {5, 7}, {8, 9}};
    
    activitySelection(activities);

    return 0;
}
