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

let [fisrt, second, third] = data;

objTest4.textContent = fisrt;
objTest5.textContent = second;
objTest6.textContent = third;

let userUp = {
	"name": "Mika",
	"age": 34,
	"city": "Paris",
	other: {adress: "44 rue saint lazare"}
}

let {name: newName, age: newAge, city: newCity, other: {adress}} = userUp;

console.log(`Destructuring of object with ${newName} live in ${newCity}, ${adress}`);

let [one, ,three] = data;

console.log(`Destructuring of Array. One: ${one}, three: ${three}`);

let [newFirst, ...array]= data;
console.log(`Destructuring with array. NewFirst: ${newFirst}, in array: ${array}`);


let dataUp = [
	{user: "Mika", age: 34},
	{user: "Alizée", age: 32}
];

let [{user: user1, age: ageUser1}, {user: user2, age: ageUser2}] = dataUp;

console.log(`Destructuring of array with objects. First user: ${user1}, ${ageUser1}. Second user: ${user2}, ${ageUser2}`);

let newMap = new Map([
	["a", 21],
	["b", 42]
]);

console.log("\nDestructuring of Map. Use forEach");
newMap.forEach((value, key) => console.log(key, ":", value));

console.log("Destructuring of Map. Use for of");
for (let [key, value] of newMap)
	console.log(key, ":", value)

console.log("Destructuring of Map. Use map");
let arrayMap = [...newMap].map(([key, value]) => value * 2);
arrayMap.forEach((value) => console.log(value));

console.log("Destructuring of Array with object. Use map");
dataUp.map(({user}) => console.log(user));

console.log("\nUse destructuring in function");
console.log("\nDisplay value of array from arguments in fuction");

function getData([firstArg, secondArg, thirdArg] = [0,0,0])
{
	console.log(`Function getData.Fisrt value: ${firstArg}, second value: ${secondArg}, third value: ${thirdArg}`);
}
console.log("Function with args");
getData(data);
console.log("Function without args");
getData();



console.log("\nDisplay value of object from arguments in fuction");
function simpleUser({name: nameUser, age: ageUser, city: cityUser} = {})
{
	console.log(`Function simpleUser : Name: ${nameUser}, age: ${ageUser}, city: ${cityUser}`);
}

console.log("Function with args");
simpleUser(user);
console.log("Function without args");
simpleUser();


function hardUser({name = "Anonymous", age = 99, city = "Unknown", other: {adress = "Unknown Adress"} = {}} = {})
{
	console.log(`Function hardUser: Name: ${name}, age: ${age}, city: ${city}, other: ${adress}`);
}
console.log("\nFunction with args");
hardUser(userUp);
console.log("Function without args");
hardUser();

console.log("\nDisplay value of array with objects from arguments in fuction");
function displayDataUp([{user: firstUser = "Anonimus", age: firstUserAge = "Unknowe"} = {}, {user: secondUser = "Anonimus", age: secondUserAge = "Unknowe"} = {}] = [])
{
	console.log(`Display from displayDataUp.\nFirst user: ${firstUser}, age ${firstUserAge}.\nSecond user: ${secondUser}, age ${secondUserAge}`)
}
console.log("Function with args");
displayDataUp(dataUp);
console.log("Function without args");
displayDataUp();