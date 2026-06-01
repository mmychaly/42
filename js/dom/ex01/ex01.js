"use strict";

let test1 = document.getElementById("test1");
let test2 = document.querySelector("#test2");
let allTest = document.querySelectorAll("p");
let article = document.querySelector("article");
let test3 = allTest[6];
test1.textContent = "Salut";
test2.textContent = "Hello";
test3.textContent = "Hola";

console.log("Use matches, closest, contains");
console.log(test1.matches("#test1"));
console.log(test2.closest("main"));
console.log(article.contains(test1));