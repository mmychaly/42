"use strict";

console.log("Test create, add and remove elemnt with createElement(),befor(),prepend(),append(),after(),reove()")
let test1 = document.querySelector("#test1");
let test2 = document.querySelector("#test2");
let test3 = document.querySelector("#test3");
let mainTest = document.querySelector("main");
let art = document.querySelector("article");

test1.textContent = "Hello";
test2.textContent = "Hi";
test3.textContent = "Remove element";
console.log(art.children);

//Create elements
let newP = document.createElement("p");
newP.textContent = "Salut";
newP.id = "test0";
let testPrepend = document.createElement("p");
testPrepend.textContent = "Holla";
testPrepend.id = "testPrepend";
let testAppend = document.createElement("p");
testAppend.textContent = "Privet";
testAppend.id = "testAppend";

//Add with befor()
test1.before(newP);

//Add and create inside after()
test1.after(document.createElement("div"));
let divText = document.querySelector("div");
divText.textContent = "Bonjour";


//Use prepend and append
mainTest.prepend(testPrepend);
mainTest.append(testAppend);
console.log(mainTest.children);
console.log(mainTest.firstChild.childNodes[0].textContent);
console.log(mainTest.lastChild.childNodes[0].textContent);

//Use remove
test3.remove();
