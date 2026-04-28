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



