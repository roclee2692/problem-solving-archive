#include <vector>
#include <iostream>

struct Data {
    int x, y;
    Data(int a, int b) : x(a), y(b) {
        std::cout << "Constructed Data(" << x << ", " << y << ")\n";
    }
};

int main() { 
    std::vector<Data> vec;

    std::cout << "Using push_back:\n";
    vec.push_back(Data(1, 2)); // 需要构造临时 Data(1,2)，然后移动到 vector 中

    std::cout << "\nUsing emplace_back:\n";
    vec.emplace_back(3, 4); // 直接在 vector 内部构造 Data(3,4)，避免临时对象创建

    return 0;
}
