#销量数据的综合可视化图表
#显示不同产品在各地区的销量柱状图 + 平均销量折线图 + 图例 + 标注 + 双轴支持
from itertools import product
import matplotlib.pyplot as plt
import numpy as np
plt.rcParams['font.sans-serif'] = ['SimHei']  # 设置中文黑体
plt.rcParams['axes.unicode_minus'] = False    # 正常显示负号
# 假设有 3 个产品，4 个地区的销量
products=["A", "B", "C"]
regions=["North", "South", "East", "West"]
# 生成随机销量数据
data = {prod: np.random.randint(80, 200, size=len(regions)) for prod in products}
#遍历 products 列表，例如：["A", "B", "C"] 每次迭代取一个产品名作为键（key）    
# data 是一个字典，键是产品名，值是对应地区的销量数组   从区间 [80, 200) 中随机生成整数
#size=len(regions) 表示生成的数量和地区数一致（例如 4 个）
#返回一个 NumPy 数组，例如 array([123, 150, 98, 174])
#{key: value for ...}    字典推导式
#把每个产品对应的随机数组生成一条键值对
# 计算平均销量
#x= np.arange(len(regions))  # x是一个列表 x 轴位置 np.arange = array + range 的组合词，意思是“像 Python 的 range 一样生成一组等间隔数，但返回的是数组”。
#width = 0.2  # 柱状图宽度 
# 绘制柱状图

x = np.arange(len(regions))  # x轴坐标位置
bar_width = 0.25

fig, ax1 = plt.subplots(figsize=(10, 6))

# 多产品分组柱状图
for i, prod in enumerate(products):
    offset = i * bar_width
    ax1.bar(x + offset, data[prod], width=bar_width, label=prod)

# 平均销量折线（右轴）
avg_sales = np.mean([data[p] for p in products], axis=0)
ax2 = ax1.twinx()
ax2.plot(x + bar_width, avg_sales, color="pink", linestyle="--", marker="o", label="Avg", linewidth=2)

# 坐标轴 & 图例
ax1.set_xticks(x + bar_width)
ax1.set_xticklabels(regions)
ax1.set_ylabel("销量")
ax2.set_ylabel("平均销量")
ax1.set_title("各地区产品销量图")

# 添加图例（支持两个 y 轴）
lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels1 + labels2, loc="upper left")

# 标注最大值
for i, y in enumerate(avg_sales):
    ax2.text(x[i] + bar_width, y +1.5, f"{y:.1f}", ha='center', fontsize=10, color="black")

plt.tight_layout()
plt.savefig("sales_chart.png", dpi=300)
plt.show()