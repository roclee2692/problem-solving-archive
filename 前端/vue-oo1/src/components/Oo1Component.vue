<template>
    <div>
      <ul class="menu-tab">
        <!-- 
          v-for="(item, index) in menuList" :key="item"
            - 遍历 data 中的 menuList 数组，item 是内容，index 是索引
            - :key 给每个列表项一个唯一标识，一般可用索引或唯一 ID
          :class="['menu-item', activeIndex === index ? 'active' : '']"
            - 动态绑定class
            - 如果当前索引 === activeIndex，就额外加上 'active' 类，否则为空
          @click="activeIndex = index"
            - 点击时更新 activeIndex 为当前索引
         -->
        <li
          class="menu-item"
          :class="['menu-item', activeIndex === index ? 'active' : '']"
          v-for="(item, index) in menuList"
          :key="item"
          @click="activeIndex = index"
        >
          {{ item }}
        </li>
      </ul>
    </div>
  </template>
  
  <script>
  export default {
    data() {
      return {
        // menuList 存放菜单的条目
        menuList: [
          "商品介绍",
          "规格与包装",
          "售后保障",
          "商品评价（100万+）",
          "手机社区",
        ],
        // 默认选中第 0 个（第一个）条目
        activeIndex: 0,
      };
    },
  };
  </script>
  
  <style scoped>
  /* 去掉li前面的默认小圆点 */
  li {
    list-style: none;
  }
  
  /*
    .menu-tab 容器
      - display:flex 实现水平布局
      - justify-content: space-between 子元素在主轴上均分空间
      - width:700px; height:40px; 设置固定大小
      - 边框、背景色
  */
  .menu-tab {
    display: flex;
    justify-content: space-between;
    margin: 50px auto;
    width: 700px;
    height: 40px;
    border: 1px solid #eee;
    background-color: #f7f7f7;
    border-bottom: 1px solid #ea3737;
    user-select: none; /* 禁止用户选中文本，可选 */
  }
  
  /*
    .menu-item
      - flex:1 让每个子项平分父容器的剩余空间
      - 水平&垂直居中
      - 字体大小、鼠标手势
  */
  .menu-item {
    flex: 1;
    display: flex;
    justify-content: center;
    align-items: center;
    font-size: 14px;
    color: #666;
    cursor: pointer;
  }
  
  /* 鼠标悬停时，文字高亮为红色 */
  .menu-item:hover {
    color: #ea3737;
  }
  
  /* 当某个 .menu-item.active 时，文字变白，背景变红色 */
  .menu-tab > .menu-item.active {
    color: #fff;
    background-color: #ea3737;
  }
  </style>
  