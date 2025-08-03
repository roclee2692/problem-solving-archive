<template>
  <div id="app">
    <!-- 渲染 CardComponent 组件 -->
    <CardComponent />
  </div>
</template>

<script>
// 引入 CardComponent 组件
import CardComponent from './components/CardComponent.vue';

export default {
  name: 'App',
  components: {
    CardComponent, // 注册组件
  },
};
</script>

<style>
/* 可在此添加全局样式 */
</style>
