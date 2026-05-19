"use strict";

const testObj = document.getElementById("test1");
testObj.textContent = "salut";

function User(name, age, email)//Object Constructor
{
	this.name = name;
	this.age = age;
	this.email = email;
}

User.prototype.getUser = function () {console.log(this.name, this.age, this.email)};//Constructor prototype

let user1 = new User("Mika", 34, "mmych@gmail.com");//We can use this in constuctor 
let user2 = new User("Alizée", 32, "a_alize@gmail.com");

user1.getUser();//Object 1 and 2 use the same methode
user2.getUser();

user2.sayHi = function () {console.log("Hello!")};

user2.sayHi();//We can use this befor object methodes