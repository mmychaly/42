"use strict";

const objTest1 = document.getElementById("test1");
const objTest2 = document.getElementById("test2");
const objTest3 = document.getElementById("test3");
const objTest4 = document.getElementById("test4");
const objTest5 = document.getElementById("test5");
const objTest6 = document.getElementById("test6");
const objTest7 = document.getElementById("test7");
const objTest8 = document.getElementById("test8");
const objTest9 = document.getElementById("test9");
const objTest10 = document.getElementById("test10");


let user = { //Declaration d'object
	name: "Micka", //Cle + valeur
	age: 34,
	presentation() { console.log("Salut, my name " + this.name + ".I am " + this.age + " year old.") } //Method
};

objTest1.textContent = user.name;
objTest2.textContent = user["age"];

for (let key in user)//Parcourir l'object
	console.log(key, ": ", user[key]);
user.presentation();//Lancer le method
user.age = 35;//Changment de valeur dans la propriété
user.work = "Dev full-stack";//Ajouter une propriété
objTest4.textContent = user.work;
delete user.work;//Supprimer une propriété
if (typeof user.work == "string")
	objTest5.textContent = user.work;
else
	objTest5.textContent = "Undefined";

objTest3.textContent = user.age;

console.log("\nConstructor presonel");//Creer un object avec constructor

function Users(name, age, phrase)
{
	this.name = name,//Utilisation de this
	this.age = age,
	this.phrase = phrase
}

let userAlizée = new Users("Alizée", 32, "Hi!");
for (let key in userAlizée)
	console.log(key, ": ", userAlizée[key]);
