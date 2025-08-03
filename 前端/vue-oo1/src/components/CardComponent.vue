<template>
    <!-- 卡片的主容器 -->
    <div class="card">
      <!-- 头部区域 -->
      <div class="header">
        <!-- 命名插槽，用于自定义头部内容 -->
        <slot name="header">
          <!-- 默认头部内容 -->
          <h1>header</h1>
        </slot>
        
        <!-- 头部额外区域（如操作按钮） -->
        <div class="extra">
          <!-- 命名插槽，允许外部定义额外内容 -->
          <slot name="extra">操作按钮</slot>
        </div>
      </div>
  
      <!-- 主体内容区域 -->
      <div class="content">
        <!-- 默认插槽，用于卡片的主要内容 -->
        <slot></slot>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    // 组件中不包含任何动态数据
    data() {
      return {};
    },
  };
  </script>
  
  <style scoped>
  /* 卡片容器的样式 */
  .card {
    width: 400px; /* 固定卡片宽度 */
    height: 300px; /* 固定卡片高度 */
    border: 1px solid #ccc; /* 边框颜色为浅灰色 */
    box-shadow: 0px 0px 10px #ccc; /* 添加阴影效果 */
    border-radius: 4px; /* 圆角样式 */
  }
  
  /* 头部区域的样式 */
  .header {
    width: 100%; /* 占据整个卡片宽度 */
    height: 50px; /* 固定头部高度 */
    border-bottom: 1px solid #ddd; /* 添加底部分割线 */
    display: flex; /* 使用Flex布局 */
    justify-content: space-between; /* 子项左右对齐 */
    align-items: center; /* 垂直居中 */
    padding: 10px; /* 内边距 */
  }
  
  /* 头部额外内容区域的样式 */
  .extra {
    max-width: 150px; /* 最大宽度限制 */
    overflow: hidden; /* 超出部分隐藏 */
    color: blue; /* 文字颜色为蓝色 */
  }
  
  /* 主体内容区域样式 */
  .content {
    padding: 10px; /* 内容的内边距 */
  }
  </style>
  