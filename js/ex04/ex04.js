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
array.forEach((elem, index) => {
	if (typeof elem == "string")
 		array[index] = elem.toLocaleUpperCase();
});

array.forEach((elem, index) => {
	console.log("index", index, ":", elem);
});


console.log("\nMethods of array");
console.log("Push + unshift"); //Ajouter un element a la fin et ajouter un element devant.
array.push("by");
array.unshift("Chao");
console.log("array:", array);

console.log("pop + shift"); //Supprimer un element a la fin et supprimer un element devant.
array.pop();
array.shift("Chao");
console.log("array:", array);

console.log("slice + splice");//Copier l'element . Supprimer un element de array
let newObj = array.slice(1, 2);
array.splice(1, 1);
console.log(newObj, "\n", array);


console.log("includes + indexOf");//Verifier l'element + trouver son index 
console.log(array.includes("SALUT"), ":", array.indexOf("SALUT"));


//map() //Creer un nouveau tab.en gardent la taille de tab initiale
console.log("\nmap()");
array.push({name: "Mika", age: 34});
array.push({name: "Alizée", age: 32});

array.forEach((elem, index) => {
	console.log("index", index, ":", elem);
});

let arrayNew= array.map(elem => {
	if (typeof elem == "object")
		return elem.name;
	else
		return elem;
});

arrayNew.forEach((elem, index) => {
	console.log("index", index, ":", elem);
});

console.log("\n filter()");//Creer un array juste avec les elements choisis

let arrayObj = array.filter(elem => typeof elem === "object");
arrayObj.forEach((elem, index) => {
	console.log("index", index, ":", elem);
});