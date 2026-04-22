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

let newMap = new Map();
let obj = {
	User1: "Mika",
	User2: "Alizée"
}

newMap.set("string", "Hello world");//key string
newMap.set(2, 42);//key string
newMap.set(obj, 2);

objTest.textContent = newMap.get("string");
objTest2.textContent = newMap.get(2);
objTest3.textContent = newMap.get(obj);

console.log(newMap.size);//Check the size
console.log(newMap.has(obj));//Check item
newMap.delete(2);//Delete one item
console.log(newMap.has(2));
newMap.set("NewString", "Salut");

console.log("\nBrowse with forEach");
newMap.forEach((value, key) => {
	if (typeof key === "object")
	{
		for (let prop in key)
			console.log(prop, " :", key[prop]);
	}
	else
		console.log(key, " :", value);
});

console.log("\nBrowse with for of");

for (let [key, value] of newMap)
{
	console.log(key, " :", value);
}

console.log("\nConversion map to array");
let array = [...newMap];
array.forEach((item, index) => 
{
	if (typeof item[0] === "object")
	{
		console.log("index", index, " : key == ", item[0], " // value == ", item[1]);
		console.log("Content of object :")
		for (let key in item[0])
		 	console.log(key, ": ", item[0][key]);
	}
	else
		console.log("index", index, " : key == ", item[0], " // value == ", item[1]);
});

console.log("\nConversion map to obj");
let numMap = new Map([
	["first", 1],
	["seconde", 2],
	["third", 3],
	["fourth", 4]
]);
console.log(numMap);
let convObj = Object.fromEntries(numMap);
for (let key in convObj)
{
	console.log(`${key} : ${convObj[key]}`);

}

console.log("\nConversion obj to map");
let objMap = new Map(Object.entries(obj));
console.log(objMap);

objMap.forEach((value, key) => console.log(`${key} : ${value}`));

console.log("\nSuppresion content of map");
objMap.clear();
console.log(objMap);
console.log(`size == ${objMap.size}`);


console.log("\nSet");

let newSet = new Set();

newSet.add(1);
newSet.add(3);
newSet.add(99);
newSet.add(-5);
newSet.add(42);
newSet.add(1);
newSet.add(99);
console.log(newSet);
console.log(`Which is the size? : ${newSet.size}`);
console.log(`Set has value 99? : ${newSet.has(99)}`);
console.log(`Set has value 105? : ${newSet.has(105)}`);

console.log("\nBrowse with forEach");
newSet.forEach(value => console.log(value));

newSet.delete(-5);
console.log("\nBrowse with for of + delete one item");
for (let value of newSet)
	console.log(value);

console.log("\nConverse to array");

let arraySet = [...newSet];
console.log(arraySet);

let  newArrSet = new Set(arraySet);
console.log(newArrSet);

console.log("\nSuppresion content of Set");
newArrSet.clear();
console.log(newArrSet);
console.log(`size == ${newArrSet.size}`);