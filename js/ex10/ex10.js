"use strict";

const objTest = document.getElementById("test1");
const objTest2 = document.getElementById("test2");
const objTest3 = document.getElementById("test3");
const objTest4 = document.getElementById("test4");
const objTest5 = document.getElementById("test5");
const objTest6 = document.getElementById("test6");
const objTest7 = document.getElementById("test7");
const objTest8 = document.getElementById("test8");
const objTest9 = document.getElementById("test9");
const objTest10 = document.getElementById("test10");


let user = {
	"name": "Mika",
	"age": 34,
	"city": "Paris"
}

let {name, age, city} = user;

objTest.textContent = name;
objTest2.textContent = age;
objTest3.textContent = city;

let data = ["Hksdi", "Odskd", "ipIOppo"];

let [fisrt, seconde, third] = data;

objTest4.textContent = fisrt;
objTest5.textContent = seconde;
objTest6.textContent = third;

let userUp = {
	"name": "Mika",
	"age": 34,
	"city": "Paris",
	other: {adress: "44 rue saint lazare"}
}

let {name: newName, age: newAge, city: newCity, other: {adress}} = userUp;

console.log(`${newName} live in ${newCity}, ${adress}`);

let [one, ,three] = data;

console.log(`Array. one: ${one}, three: ${three}`);

let [newFirst, ...array]= data;
console.log(`in newFirst: ${newFirst}, in array: ${array}`);


