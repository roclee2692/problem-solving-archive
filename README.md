# problem-solving-archive

[English](#english) | [中文](#中文)

---

# English

A comprehensive coding problem-solving archive with detailed solutions, competitive programming templates, and well-commented algorithms.

## 📚 Latest Updates

### 🔥 2026.02.01 - Template Library Optimization

**CDQ Divide & Conquer Template Rewritten**
- ✅ Added detailed line-by-line comments explaining every function
- ✅ Binary Indexed Tree (BIT) with complete workflow demonstration
- ✅ CDQ divide & conquer core principles explained (divide, merge, query)
- ✅ Real code examples with calculation process
- ✅ Common mistakes and debugging tips
- ✅ Complexity analysis and comparison with other algorithms
- 📍 Now you can fully understand the algorithm just by reading the comments

**Key Files**
- `C++/templates/06_dynamic_programming/cdq_divide_conquer.cpp` - Detailed version (recommended for learning)
- `C++/实战模板库/分治与偏序统计/CDQ分治三维偏序.cpp` - Competition version (concise code)

## 📁 Project Structure

```
coding-practice-archive/
├── C++/
│   ├── 蓝桥杯B备考/          # Lanqiao Cup competition problems
│   ├── 洛谷/                # Luogu platform problems
│   ├── 实战模板库/          # Competition algorithm templates
│   │   ├── 数据结构/        # Data Structures
│   │   ├── 树上高级数据结构/ # Advanced Tree Structures
│   │   ├── 数论/            # Number Theory
│   │   ├── 分治与偏序统计/  # ⭐ Divide & Conquer
│   │   ├── 计算几何/        # Computational Geometry
│   │   └── ...
│   └── templates/           # Detailed commented versions
│       ├── 01_graph_basic/
│       ├── 02_string/
│       ├── 03_data_structure/
│       ├── 04_number_theory/
│       ├── 05_graph_advanced/
│       └── 06_dynamic_programming/  # ⭐ CDQ Divide & Conquer
├── Python/
├── 前端/                    # Frontend projects
└── 其它/                    # Others
```

## 🎯 Template Features

1. **Detailed Comments** - Every algorithm has Chinese comments for understanding
2. **Two Versions** - Competition version (concise) and Learning version (detailed)
3. **Battle-tested** - All code has been tested and verified
4. **Complexity Analysis** - Time and space complexity clearly marked
5. **Recommended Problems** - Each template comes with practice problems

## 💡 CDQ Divide & Conquer - 3D Partial Order

### Core Concept
- **Problem**: Given n 3D points, count how many points are dominated by each point
- **Brute Force**: O(n²) - Too slow
- **CDQ Divide & Conquer**: O(n log² n) - 275x faster!

### Key Techniques
- 1st dimension: Sorting (preprocessing)
- 2nd dimension: Merge sort during divide & conquer
- 3rd dimension: BIT for prefix sum queries

### Learning Path
1. Understand BIT's four functions: `init`, `lowbit`, `add`, `query`
2. Understand that each position in BIT stores a range sum
3. Understand CDQ's three steps: Divide → Count → Merge
4. Manually simulate small data (n=5) through the complete process

### Recommended Problems
- Luogu P3810 - 3D Partial Order (Template Problem)
- Luogu P1975 - Dynamic Inversion Pairs
- BZOJ 3262 - Enhanced Version

## 🚀 Quick Start

### View Detailed Version (Recommended for Learning)
```bash
C++/templates/06_dynamic_programming/cdq_divide_conquer.cpp
```

### View Competition Version (Concise Code)
```bash
C++/实战模板库/分治与偏序统计/CDQ分治三维偏序.cpp
```

## 📊 Content Statistics

- **C++ Competition Templates**: 150+ files
- **Python Data Analysis**: 10+ practical projects
- **Frontend Projects**: Vue/HTML showcase pages
- **Detailed Comments**: 10,000+ lines of commented code

## ⭐ Features

- ✅ **Dimension-by-dimension Processing** - Core of CDQ divide & conquer
- ✅ **BIT Optimization** - O(log n) operations
- ✅ **Deduplication Optimization** - Merge identical points
- ✅ **Detailed Derivation** - Every step with examples
- ✅ **Visual Demonstration** - Array changes visualization

## 🤝 Contributors

- roclee2692 (Main Maintainer)

## ⚖️ License

MIT License

---

# 中文

一个全面的编程问题解决方案归档库，包含详细的解题思路、竞赛编程模板和注释完善的算法。

## 📚 更新说明

### 🔥 2026.02.01 - 模板库优化升级

**CDQ 分治模板完全重写**
- ✅ 添加详细的逐行注释，每个函数都有完整的解释
- ✅ 树状数组(BIT)所有方法都有具体工作流程演示
- ✅ CDQ分治核心原理详细讲解（分治、归并、查询）
- ✅ 实际代码示例和计算过程演示
- ✅ 常见错误及调试技巧汇总
- ✅ 复杂度分析和与其他算法的对比
- 📍 现在阅读注释就能完全理解整个算法逻辑

**主要文件**
- `C++/templates/06_dynamic_programming/cdq_divide_conquer.cpp` - 详细版本（推荐学习）
- `C++/实战模板库/分治与偏序统计/CDQ分治三维偏序.cpp` - 竞赛版本（代码精简）

## 📁 项目结构

```
coding-practice-archive/
├── C++/
│   ├── 蓝桥杯B备考/          # 蓝桥杯竞赛题
│   ├── 洛谷/                # Luogu 平台题目
│   ├── 实战模板库/          # 竞赛算法模板库
│   │   ├── 数据结构/
│   │   ├── 树上高级数据结构/
│   │   ├── 数论/
│   │   ├── 分治与偏序统计/  # ⭐ 新增
│   │   ├── 计算几何/
│   │   └── ...
│   └── templates/           # 详细注释版本
│       ├── 01_graph_basic/
│       ├── 02_string/
│       ├── 03_data_structure/
│       ├── 04_number_theory/
│       ├── 05_graph_advanced/
│       └── 06_dynamic_programming/  # ⭐ CDQ 分治
├── Python/
├── 前端/
└── 其它/
```

## 🎯 算法模板特点

1. **详细注释** - 每个算法都有中文注释解释，可以通过阅读注释理解算法
2. **两个版本** - 竞赛版(简洁)和学习版(详细)
3. **实战验证** - 所有代码都经过测试和实战验证
4. **复杂度分析** - 明确标注时间空间复杂度
5. **推荐题目** - 每个模板都有配套的力扣/洛谷题目

## 💡 CDQ 分治 - 三维偏序详解

### 核心概念
- **问题**：给定 n 个三维点，对每个点统计有多少个点在三维上都≤它
- **暴力**：O(n²) - 太慢
- **CDQ分治**：O(n log² n) - 快 275 倍！

### 关键技术
- 第一维：排序（预处理）
- 第二维：分治过程中的归并排序
- 第三维：树状数组维护前缀和

### 学习路径
1. 理解树状数组的四个函数：`init`, `lowbit`, `add`, `query`
2. 理解树状数组中每个位置存储的是一个范围的和
3. 理解CDQ分治的三步骤：分治→统计→合并
4. 手动模拟小数据（n=5）的完整分治过程

### 推荐题目
- 洛谷 P3810 - 陌上花开（三维偏序模板题）
- 洛谷 P1975 - 动态逆序对
- BZOJ 3262 - 陌上花开（加强版）

## 🚀 快速开始

### 查看详细版本（推荐学习）
```bash
C++/templates/06_dynamic_programming/cdq_divide_conquer.cpp
```

### 查看竞赛版本（代码简洁）
```bash
C++/实战模板库/分治与偏序统计/CDQ分治三维偏序.cpp
```

## 📊 内容统计

- **C++ 竞赛模板**：150+ 文件
- **Python 数据分析**：10+ 实战项目
- **前端项目**：Vue/HTML 展示页面
- **详细注释**：超 10000 行注释代码

## ⭐ 特色功能

- ✅ **逐维度分治处理** - CDQ 分治的核心
- ✅ **树状数组优化** - O(log n) 操作
- ✅ **去重优化** - 相同点合并，常数优化
- ✅ **详细推导** - 每步计算都有示例
- ✅ **图解演示** - 数组变化过程可视化

## 📝 更新日志

### 2026.02.01
- CDQ 分治模板大幅优化（从原始版本 → 详细学习版本）
- 新增树状数组详细讲解
- 新增分治与偏序统计专项

### 之前的版本
- 蓝桥杯备考题库
- 各类数据结构模板
- 图论和动态规划模板

## 🤝 贡献者

- roclee2692 (主要维护者)

## ⚖️ License

MIT License
