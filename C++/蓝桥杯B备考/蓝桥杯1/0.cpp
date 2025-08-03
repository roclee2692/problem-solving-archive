#include <stdio.h>

int main() {
    int score1, score2, totalScore;
    char grade;

    // 输入两门课成绩
    printf("请输入第一门课成绩（百分制）：");
    scanf("%d", &score1);

    printf("请输入第二门课成绩（百分制）：");
    scanf("%d", &score2);

    // 判断成绩是否有效（是否为百分制成绩）
    if ((score1 < 0 || score1 > 100) || (score2 < 0 || score2 > 100)) {
        printf("输入的成绩不是有效的百分制成绩，程序结束。\n");
        return 0;  // 若成绩无效，则退出程序
    }

    // 计算总分
    totalScore = score1 + score2;

    // 使用 switch 语句判断总分对应的等级
    switch (totalScore / 10) {
        case 18:
        case 19:
        case 20:
            grade = 'A';  // 总分180及以上
            break;
        case 16:
        case 17:
            grade = 'B';  // 总分160到179
            break;
        case 14:
        case 15:
            grade = 'C';  // 总分140到159
            break;
        case 12:
        case 13:
            grade = 'D';  // 总分120到139
            break;
        default:
            grade = 'E';  // 总分120以下
            break;
    }

    // 输出结果
    printf("总分：%d ----〉等级：%c\n", totalScore, grade);

    return 0;
}
