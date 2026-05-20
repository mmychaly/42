"use strict";

let otherData = {
	email: "Unknow",
	allRule: false,
	sayHi: function () {console.log(`Hi, i am ${this.name}`)},
	
	
};

// Users.prototype = Object.create(otherData);//constuctor herite de object otherData
// Users.prototype.constructor = Users;

function Users(name, age)
{
	this.name = name;
	this.age = age;
}
Users.prototype.__proto__ = otherData;//Second technique pour que constuctor herite de object otherData

Users.prototype.getUser = function () {console.log(this.name, this.age)},
Users.prototype.getUserOtherData = function () {console.log("Email: " , this.email, "\nRules :", this.allRule)}

let user1 = new Users("Mika", 34);
let user2 = new Users("ALizée", 32);

console.log("First user");
user1.getUser();
user1.getUserOtherData();
user1.sayHi();

console.log("\nSecond user");
user2.getUser();
user2.getUserOtherData();
user2.sayHi();

