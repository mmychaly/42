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

//firstChild / lastChild / hasChildNodes
console.log("\n firstChild and lastChild,hasChildNodes")
let first = document.body.firstChild;
console.log(first);
let last = document.body.lastChild;
console.log(last);
console.log(document.body.hasChildNodes());

//nextSibling vs nextElementSibling and previousSibling vs previousElementSibling
console.log("\n nextSibling vs nextElementSibling")
console.log(head.nextSibling);
console.log(head.nextElementSibling);
console.log("\n previousSibling vs previousElementSibling")
console.log(body.previousSibling);
console.log(body.previousElementSibling);

//parentNode
console.log("\n Use parentNode")
console.log(body.parentNode);