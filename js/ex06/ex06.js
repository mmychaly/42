"use strict";

const objTest1 = document.getElementById("test1");
const objTest2 = document.getElementById("test2");
const objTest3 = document.getElementById("test3");
const objTest4 = document.getElementById("test4");


//fonction classique
function getAnything(name){
	objTest1.textContent = "Salut " + name + "!";
}

getAnything("Mika");

//function expression 

let getHello = function (name) {
	objTest2.textContent = "Hello " + name + "!";
};

getHello("Alizée");

//arrow function

let helloWorld = () => objTest3.textContent = "Hello world!";

helloWorld();

//arrow function in map
let array = [ "Mika", "Alizée", "Alex"];

array.forEach(name => console.log("Salut " + name + "!"));


