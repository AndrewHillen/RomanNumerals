const express = require('express');
const bodyParser = require("body-parser");

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false}));

app.use(express.static('public'));

app.post('/api', function(req, res) {
  var execFile = require('child_process').execFile;
  //For Linux
  var program = "../NumeralTranslator";

  //For windows
  //var program = "../NumeralTranslator.exe";

  var input = req.body.number;
  var child = execFile(program, [input],
    function(error, stdout, stderr) {
      var output = stdout;
      res.setHeader('Content-Type', 'application/json');
      res.end(JSON.stringify({
        returnVal: output
      }));
    });
});

app.listen(3003, () => console.log("Server listening on 3003"));
