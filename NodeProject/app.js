var express = require("express");
var app = express();
var port = 3000;
var bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

var mongoose = require("mongoose");
mongoose.Promise = global.Promise;
mongoose.connect("mongodb://localhost:27017/node-demo");

var nameSchema = new mongoose.Schema({
    RFIDtag: String
});
var Tags = mongoose.model("Tags", nameSchema);

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/index.html");
});

app.get("/tag/:id", function(req, res){
    Tags.findById(req.params.id, function(err, result) {
    if (err) {
      res.send(err);
    } else {
      res.json(result);
    }
  });
});

app.get("/alltags", (req, res) => {
    Tags.find({}, function(err, tags){
        res.json(tags);
    });
});

app.post("/saveTag", (req, res) => {
  var myData = new Tags(req.body);
  myData.save(function(err, IDtag) {
    if(err){
      res.status(400).send("unable to save to database");
    }
    console.log(IDtag.id)
    res.send("http://localhost:3000/tag/" + IDtag.id);
  })
});

app.listen(port, () => {
  console.log("Server listening on port " + port);
});