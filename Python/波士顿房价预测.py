# 导入线性回归模型类
from sklearn.linear_model import LinearRegression
# 导入matplotlib绘图库
import matplotlib.pyplot as plt 

# 定义数据文件路径
datafile = '/home/aistudio/data/data295714/boston.csv'

# 读取CSV文件
# 使用numpy的genfromtxt函数读取CSV文件，delimiter指定分隔符为逗号，names=True表示第一行作为列名
data = np.genfromtxt(datafile, delimiter=',', names=True)
# 提取特征变量：房间数量（rm - rooms per dwelling）
x = data['rm']
# 提取目标变量：房价中位数（medv - median value）
y = data['medv']

# 将一维数组转换为二维数组，因为sklearn要求输入为二维数组格式
x1 = x.reshape(-1, 1)
# 将目标变量也转换为二维数组格式
y1 = y.reshape(-1, 1)

# 创建线性回归模型实例
clf = LinearRegression()
# 使用训练数据拟合模型，建立房间数和房价之间的线性关系
clf.fit(x1, y1)#模型训练
# 获取回归系数，表示房间数对房价的影响程度
clf.coef_    # 回归系数
# 使用训练好的模型进行预测
y_pre = clf.predict(x1)#模型输出值
#样本实际分布
# 绘制实际数据点的散点图，显示房间数与房价的真实分布关系
plt.scatter(x, y)
# 绘制线性回归拟合直线，红色表示预测的房价趋势
plt.plot(x, y_pre, color='red')#绘制拟合曲线
# 显示图形
plt.show()