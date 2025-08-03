<template>
  <!-- 点击时 count 自增 -->
  <div @click="count++">{{ count }}</div>
</template>

<script>
export default {
  data() {
    return {
      count: 100,
    };
  },
  beforeCreate() {
    console.log("beforeCreate");
    console.log(this.$data); // 在此阶段还未初始化 data
  },
  created() {
    console.log("created");
    console.log(this.$data); // 现在能访问到 data 里的 count:100
  },
  beforeMount() {
    console.log("beforeMount");
    console.log(this.$el); // undefined或挂载点模板
  },
  mounted() {
    console.log("mounted");
    console.log(this.$el);
  },
  beforeUpdate() {
    console.log("beforeUpdate");
    console.log(this.$data.count);
    console.log(this.$el.innerHTML); // 旧的DOM内容
  },
  updated() {
    console.log("updated");
    console.log(this.$data.count);
    console.log(this.$el.innerHTML); // 新的DOM内容
  },
  beforeUnmount() {
    console.log("beforeUnmount");
  },
  unmounted() {
    console.log("unmounted");
  },
};
</script>
