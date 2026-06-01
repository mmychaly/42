"use strict";


let html = document.documentElement;
let body = document.body;
let head = document.head;

console.log(html, body, head)

console.log("\nUse childNodes");
for (let child of document.body.childNodes)
	console.log(child);

console.log("\nUse children");
for (let children of document.body.children)
	console.log(children);

console.log("\nUse array for childNodes");
let arrChildNodes = Array.from(document.body.childNodes);
arrChildNodes.forEach(elem => console.log(elem));

console.log("\nUse array for children");
let arrChildren = Array.from(document.body.children);
arrChildren.forEach(elem => console.log(elem));

//firstChild and lastChild
console.log("\n firstChild and lastChild")
let first = document.body.firstChild;
console.log(first);
let last = document.body.lastChild;
console.log(last);