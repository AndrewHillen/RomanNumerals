<template>
  <div>
  <h1>Convert a numer to a Roman Numeral or Vice-Versa</h1>
  <input placeholder="XIV or 14, etc." v-model="number">
  <button type="submit" class="pure-button" @click.prevent="translate">Enter</button>
  <p>{{this.returnVal}}</p>
</div>
</template>

<script>
import axios from 'axios';
export default {
  name: 'Translator',
  data() {
    return {
      number: '',
      returnVal: ''
    }
  },

  methods: {
    async translate(){
      let response = await axios.post('/api', {
        number: this.number
      });
      this.returnVal = response.data.returnVal;
    }
  }
}

</script>


<style scoped>

</style>
