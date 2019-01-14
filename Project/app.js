//jshint esversion:6
const express = require("express");
const bodyParser = require("body-parser");
const mongoose = require("mongoose");
const passport = require('passport');
const flash = require('connect-flash');
const session = require('express-session');
const app = express();
app.set('view engine', 'ejs');
app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(express.static(__dirname));
mongoose.connect("mongodb://localhost:27017/college", {
  useNewUrlParser: true
});
mongoose.set('useCreateIndex', true);

const UserSchema = {
  name: {
    type: String,
    required: true,
  },
  username: {
    type: String,
    unique: true,
    required: true
  },
  email: {
    type: String,
    unique: true,
    required: true
  },
  password: {
    type: String,
    required: true,
  },
  cpassword: {
    type: String,
    required: true,
  }
};
const User = mongoose.model('User', UserSchema);
const revSchema = {
  cname: String,
  batch: Number,
  rating: Number,
  title: String,
  review: String
};
const Review = mongoose.model("Review", revSchema);
const collegeSchema = {
  cname: String,
  location: String,
  course: String,
  designation: String,
  about: String
}
const College =mongoose.model("College",collegeSchema);
app.get("/", function(req, res) {
  res.render("home");
});
app.get("/home", function(req, res) {
  res.render("home");
});
app.get("/login", function(req, res) {
  res.render("login");
});
app.get("/signup", function(req, res) {
  res.render("signup");
});
app.get("/add_college",function(req,res){
  res.render("addcollege");
});
app.get("/review", function(req, res) {
  Review.find({}, function(err, found) {
    res.render("review", {
      found: found
    });
  });
});
app.get("/write_review", function(req, res) {
  res.render("wreview");
});
app.post("/signup", function(req, res) {
  const password = req.body.password;
  const cpassword = req.body.cpassword;
  const user = new User({
    name: req.body.name,
    username: req.body.username,
    email: req.body.email,
    password: password,
    cpassword: cpassword
  });
  user.save();
  res.redirect("login");
});
app.post("/write_review", function(req, res) {
  const review = new Review({
    cname: req.body.cname,
    batch: req.body.batch,
    rating: req.body.rating,
    title: req.body.title,
    review: req.body.review
  });
  review.save();
  res.redirect("review");
});
app.post("/add_college", function(req, res) {
  const college = new College({
    cname: req.body.cname,
    location: req.body.location,
    course: req.body.course,
    designation: req.body.designation,
    about: req.body.about
  });
  college.save();
});
app.post("/login", function(req, res) {
  var username = req.body.username;
  var password = req.body.password;
  User.findOne({
    username: username,
    password: password
  }, function(err, user) {
    if (err) {
      return res.status(500).send();
    }
    if (!user) {
      return res.redirect("/signup");
    }
    return res.redirect("/write_review");
  });
});

app.listen(3000, function() {
  console.log("server started at port 3000");
});
