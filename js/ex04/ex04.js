"use strict"


let array = ["Salut", "Hi", "Hello"];

//Display on the page  
let docObj1 = document.getElementById("test1");
let docObj2 = document.getElementById("test2");
let docObj3 = document.getElementById("test3");
let docObj4 = document.getElementById("test4");
let docObj5 = document.getElementById("test5");
let docObj6 = document.getElementById("test6");
let docObj7 = document.getElementById("test7");
let docObj8 = document.getElementById("test8");
let docObj9 = document.getElementById("test9");

docObj1.textContent = array;
docObj2.textContent = array[0];
docObj3.textContent = array[1];
docObj4.textContent = array[2];


//Array
console.log("\nWork with Array");
console.log(array, array.length);
console.log(array[1]);
array[1] = {name: "Mika", age: 34};
console.log("Add obj in index 1: ", array, array.length);
console.log(array[1]);
console.log(array[1].name);

//Browse array
console.log("\nBrowse Array with for");
console.log("With for");
for (let i = 0; i < array.length; i++)
{
	console.log("index", i, array[i]);
}

console.log("With forEach");

array.forEach(function(elem) {
	console.log("index", array.indexOf(elem), elem);
});

console.log("elem.toLocaleUpperCase()");
array.forEach(function(elem) {
	if (typeof elem == "string")
		console.log(elem.toLocaleUpperCase());
});

// console.log("array[array.indexOf(elem)].toLocaleUpperCase()");
// array.forEach(function(elem) {
// 	array[array.indexOf(elem)].toLocaleUpperCase();
// });

array.forEach(function(elem) {
	console.log("index", array.indexOf(elem), elem);
});

console.log("array[array.indexOf(elem)].toLocaleUpperCase()");
array.forEach(function(elem, index) {
	if (typeof elem == "string")
 		array[index] = elem.toLocaleUpperCase();
});

array.forEach(function(elem, index) {
	console.log("index", index, elem);
});
