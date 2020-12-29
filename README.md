# RomanNumerals

The absolute easiest way to test this app is to navigate over to https://numerals.andrewhillen.com/

I was in a pretty big hurry for the vue section of this project, so the style and whatnot is pretty non-existent. I used Node's child_process to send input and receive output
straight from the executable built in C++. This was pretty neat since I was able to reuse a large portion of my original code (this is not my first time doing this challenge
for you guys) and build a nice little web application with it.

The extra stuff was built with NodeJS and vue-cli, so if you have those on your computer:

In the back-end folder, in the terminal:

```
npm install
node index.js
```

In the front-end folder, in the terminal:

```
npm install
npm run serve
```

If you don't have NodeJS/vue installed

You can get Node at https://nodejs.org/en/download/

and once you have Node installed 

```
npm install -g @vue/cli
```
to get Vue
After that, you can do the steps above to run the app, and navigate over to localhost to see it run.

Alternatively, you can just run NumeralTranslator.exe (I included both versions of the executable since my website runs on linux)
It runs in the command line and takes either Numerals (III, IV, etc. No spaces between numerals), or numbers (1, 2, 3, etc.)

I spent around 2 1/2 hours fine-tuning the Numeral->Number translation, and then the rest of the time wrapping it in the web app and then getting it up on my website. 
I used just about the full 4 hours.
