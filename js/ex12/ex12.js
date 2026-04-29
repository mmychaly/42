"use strict";

const testObj = document.getElementById("test1");

const objTest2 = document.getElementById("test2");
const objTest3 = document.getElementById("test3");
const objTest4 = document.getElementById("test4");
const objTest5 = document.getElementById("test5");
const objTest6 = document.getElementById("test6");
const objTest7 = document.getElementById("test7");
const objTest8 = document.getElementById("test8");
const objTest9 = document.getElementById("test9");
const objTest10 = document.getElementById("test10");

function counter()
{
	return counter.value++;
}

counter.value = 0;
counter.getValue = function() {
	console.log(counter.value);
};

console.log("Launch function counter");
console.log(counter());
console.log(counter());
console.log(counter());
console.log("Launch method counter");
counter.getValue();

testObj.textContent = `Value in func propertie: ${counter.value}`;

//Nativ properies and methodes
objTest2.textContent = `Propertie .name: ${counter.name}`;
objTest3.textContent = `Propertie .length: ${counter.length}`;


const user_1 = {
	name: "Mika",
	age: 34
};

const user_2 = {
	name: "Alizée",
	age: 32
};

function displayUser(msg)
{
	return `${msg}: ${this.name} ${this.age}`;
}

//call

objTest4.textContent = displayUser.call(user_1, "First user");
objTest5.textContent = displayUser.call(user_2, "Second user");

//apply

let args = ["Msg from array. ", "User"];
function displayUserArray(msg)
{
	return `${msg}: ${this.name} ${this.age}`;
}
objTest6.textContent = displayUserArray.apply(user_1, [args]);
objTest7.textContent = displayUserArray.apply(user_2, ["Other msg from array. User"]);

//bind

let func_1 = displayUser.bind(user_1, "Launch func_1 with bind. User");
let func_2 = displayUser.bind(user_2, "Launch func_2 with bind. User");

console.log("\nLaunch func with bind");
console.log(func_1());
console.log(func_2());
console.log(func_1());
console.log(func_2());