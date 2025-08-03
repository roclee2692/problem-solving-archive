#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstring>  // 用于 memcpy
using namespace std;

const int SIZE = 9;

// 判断在 (row, col) 放入 num 是否安全（不违反数独规则）
bool isSafe(int board[SIZE][SIZE], int row, int col, int num) {
    // 检查行
    for (int j = 0; j < SIZE; j++) {
        if (board[row][j] == num)
            return false;
    }
    // 检查列
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num)
            return false;
    }
    // 检查所属的 3×3 小宫
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (board[i][j] == num)
                return false;
        }
    }
    return true;
}

// 利用回溯法填充整个棋盘，生成一个完整的数独解
bool fillBoard(int board[SIZE][SIZE]) {
    // 寻找空格（用 0 表示空）
    int row = -1, col = -1;
    bool emptyFound = false;
    for (int i = 0; i < SIZE && !emptyFound; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                row = i;
                col = j;
                emptyFound = true;
                break;
            }
        }
    }
    // 若没有空格，则填充完成
    if (!emptyFound)
        return true;
    
    // 生成 1~9 的随机排列，增加生成时的随机性
    vector<int> nums;
    for (int i = 1; i <= SIZE; i++) {
        nums.push_back(i);
    }
    // 随机洗牌
    static mt19937 rng((unsigned)time(0));
    shuffle(nums.begin(), nums.end(), rng);
    
    // 尝试每个数字
    for (int num : nums) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (fillBoard(board))
                return true;
            board[row][col] = 0;  // 回溯
        }
    }
    return false;
}

// 辅助函数：寻找棋盘中第一个空格（值为 0 的位置）
// 若找到则设置 row, col 并返回 true，否则返回 false
bool findEmpty(int board[SIZE][SIZE], int &row, int &col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (board[row][col] == 0)
                return true;
        }
    }
    return false;
}

// 递归计数解的个数，若解超过 1 个则可以提前结束（用于验证唯一性）
void countSolutions(int board[SIZE][SIZE], int &count) {
    // 如果已经找到多个解，则无需继续
    if (count > 1)
        return;
    int row, col;
    if (!findEmpty(board, row, col)) {
        count++;
        return;
    }
    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            countSolutions(board, count);
            board[row][col] = 0;
        }
        if (count > 1)
            return;
    }
}

// 检查当前棋盘是否只有唯一解
bool hasUniqueSolution(int board[SIZE][SIZE]) {
    int count = 0;
    countSolutions(board, count);
    return (count == 1);
}

// 打印数独棋盘，空格以 '.' 显示，并加上分隔线
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------" << endl;
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (board[i][j] == 0)
                cout << ". ";
            else
                cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int board[SIZE][SIZE] = {0};
    
    // 先生成一个完整的数独解
    if (!fillBoard(board)) {
        cout << "生成完整棋盘失败！" << endl;
        return 1;
    }
    
    // 用户输入想保留的已知数字个数（提示数字越少，难度越高，最少 17 个已知数字）
    int clues;
    cout << "请输入生成题目中要保留的已知数字数量（建议不少于 17 个）：";
    cin >> clues;
    if (clues < 17 || clues > SIZE * SIZE) {
        cout << "输入数量不合理，程序退出。" << endl;
        return 1;
    }
    
    // 备份完整解，以便后续挖空后无法满足条件时重新恢复
    int fullSolution[SIZE][SIZE];
    memcpy(fullSolution, board, sizeof(board));
    
    // 构造所有格子的坐标列表，并随机打乱顺序
    vector<pair<int, int>> positions;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            positions.push_back({i, j});
        }
    }
    random_device rd;
    mt19937 gen(rd());
    shuffle(positions.begin(), positions.end(), gen);
    
    // 开始挖空（删除数字），挖空后始终保证谜题唯一解
    for (auto pos : positions) {
        int row = pos.first, col = pos.second;
        int backup = board[row][col];
        board[row][col] = 0;  // 尝试挖空此格
        
        // 检查挖空后谜题是否只有唯一解
        int boardCopy[SIZE][SIZE];
        memcpy(boardCopy, board, sizeof(boardCopy));
        if (!hasUniqueSolution(boardCopy)) {
            // 如果不唯一，则还原该位置
            board[row][col] = backup;
        }
        // 检查当前剩余的提示数字个数
        int countClues = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] != 0)
                    countClues++;
            }
        }
        // 当提示数字数目达到用户要求时停止挖空
        if (countClues <= clues)
            break;
    }
    
    cout << "\n生成的数独谜题如下（空格以 '.' 表示）：\n" << endl;
    printBoard(board);
    
    return 0;
}
