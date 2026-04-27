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






console.log("\nUse destructuring in function");
console.log("\nDisplay value of array from arguments of fuction");
function getData([firstArg, secondeArg, thirdArg] = [0,0,0])
{
	console.log(`Fisrt value: ${firstArg}, seconde value: ${secondeArg}, third value: ${thirdArg}`);
}
getData(data);
getData();




console.log("\nDisplay value of object from arguments of fuction");
function simpleUser({name: nameUser, age: ageUser, city: cityUser} = {})
{
	console.log(`FUnction simpleUser : Name: ${nameUser}, age: ${ageUser}, city: ${cityUser}`);
}

simpleUser(user);
simpleUser();


function hardUser({name = "Anonymous", age = 99, city = "Unknown", other: {adress = "Unknown Adress"} = {}} = {})
{
	console.log(`Function hardUser: Name: ${name}, age: ${age}, city: ${city}, other: ${adress}`);
}
hardUser(userUp);
hardUser();