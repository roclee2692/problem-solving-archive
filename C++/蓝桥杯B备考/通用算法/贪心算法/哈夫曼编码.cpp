#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// 定义霍夫曼树节点
struct Node {
    char character;
    int frequency;
    Node* left;
    Node* right;
    
    Node(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

// 比较节点的频率，用于优先队列（最小堆）
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency; // 小的优先
    }
};

// 递归构建霍夫曼编码
void generateHuffmanCodes(Node* root, const string& str, unordered_map<char, string>& codes) {
    if (!root) return;
    
    // 如果是叶子节点，保存编码
    if (!root->left && !root->right) {
        codes[root->character] = str;
    }
    
    // 递归左子树（加“0”）
    generateHuffmanCodes(root->left, str + "0", codes);
    
    // 递归右子树（加“1”）
    generateHuffmanCodes(root->right, str + "1", codes);
}

// 打印霍夫曼编码
void printHuffmanCodes(const unordered_map<char, string>& codes) {
    for (const auto& pair : codes) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

// 主函数：构建霍夫曼树并生成编码
void huffmanCoding(const string& text) {
    // 统计字符频率
    unordered_map<char, int> frequency;
    for (char c : text) {
        frequency[c]++;
    }

    // 构建最小堆
    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for (const auto& pair : frequency) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    // 构建霍夫曼树
    while (minHeap.size() > 1) {
        Node* left = minHeap.top(); minHeap.pop();
        Node* right = minHeap.top(); minHeap.pop();
        
        Node* newNode = new Node('$', left->frequency + right->frequency); // '$'是内部节点的字符
        newNode->left = left;
        newNode->right = right;
        
        minHeap.push(newNode);
    }

    // 获取霍夫曼树的根节点
    Node* root = minHeap.top();

    // 生成霍夫曼编码
    unordered_map<char, string> codes;
    generateHuffmanCodes(root, "", codes);

    // 打印霍夫曼编码
    printHuffmanCodes(codes);
}

int main() {
    string text = "this is an example for huffman encoding";
    
    cout << "霍夫曼编码：\n";
    huffmanCoding(text);
    
    return 0;
}
