<template>
  <div class="home">
    <Translator/>
  </div>
</template>

<script>
// @ is an alias to /src
import Translator from '@/components/Translator.vue'

export default {
  name: 'Home',
  components: {
    Translator
  }
}
</script>
