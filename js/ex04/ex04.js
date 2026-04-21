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
console.log(JSON.stringify(array), array.length);//Convertation array to string
console.log(JSON.stringify(array[1]));
array[1] = {name: "Mika", age: 34};
console.log("Add obj in index 1: ", JSON.stringify(array), array.length);
console.log(JSON.stringify(array[1]));
console.log(JSON.stringify(array[1].name));

//Browse array
console.log("\nBrowse Array with for");
let array_2 = structuredClone(array); //Deep copy

console.log("With for");
for (let i = 0; i < array_2.length; i++)
{
	console.log("index", i, array_2[i]);
}

console.log("With forEach");
array_2.forEach(function(elem) {
	console.log("index", array_2.indexOf(elem), elem);
});

console.log("elem.toLocaleUpperCase()");
array_2.forEach(function(elem) {
	if (typeof elem == "string")
		console.log(elem.toLocaleUpperCase());
});

array_2.forEach(function(elem) {
	console.log("index", array_2.indexOf(elem), elem);
});

console.log("array[array_2.indexOf(elem)].toLocaleUpperCase()");
array_2.forEach((elem, index) => {
	if (typeof elem == "string")
 		array_2[index] = elem.toLocaleUpperCase();
});

console.log("\nUse item + index");
array_2.forEach((item, index) => {
	console.log("index", index, ":", item);
});

console.log("\nMethods of array");
let array_3 = structuredClone(array);

console.log("Push + unshift");  //Ajouter un element a la fin et ajouter un element devant.
console.log("Befor array:", JSON.stringify(array_3));
array_3.push("by");
array_3.unshift("Chao");
console.log("After array:", JSON.stringify(array_3));

console.log("pop + shift"); //Supprimer un element a la fin et supprimer un element devant.
array_3.pop();
array_3.shift();
console.log("After array:", JSON.stringify(array_3));

console.log("slice + splice");//Copier l'element . Supprimer un element de array
let newObj = array_3.slice(2, 3);
array_3.splice(1, 1); //Delet from index 1 to index 1
console.log(newObj, "\n");
console.log(JSON.stringify(array_3));


console.log("includes + indexOf");//Verifier l'element + trouver son index 
console.log(array_3.includes("Salut"), ":", array_3.indexOf("Salut"));


let array_4 = structuredClone(array_3);
//map() //Creer un nouveau tab.en gardent la taille de tab initiale
console.log("\n Use map()");
array_4.push({name: "Mika", age: 34});
array_4.push({name: "Alizée", age: 32});

array_4.forEach((item, index) => {
	console.log("index", index, ":", item);
});

let arrayNew= array_4.map(item => {
	if (typeof item == "object")
		return item.name;
	else
		return item;
});

console.log("After map(), new array")
arrayNew.forEach((item, index) => 
	console.log("index", index, ":", item)
);

console.log("\n Use filter()");//Creer un array juste avec les elements choisis

let arrayObj = array_4.filter(item => typeof item === "object");//If true , return item in new array automaticly
arrayObj.forEach((item, index) => {
	console.log("index", index, ":", item);
});

console.log("\nsort()")
let sortArray = [2, -1, 9, 50, 5, 110, 0];
sortArray.sort((a,b) => a - b);
sortArray.forEach(item => console.log(item));
console.log(sortArray);

console.log("\n reduce()");
let reducArr = [10, 8, 2 , 35];
let sum = reducArr.reduce((sum, n) => sum + n, 0);
console.log(sum);