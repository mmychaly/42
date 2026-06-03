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

let testNode = document.querySelector("#test1");
let testNode2 = document.querySelector("#test2");

//nodeName, nodeType, tagName
console.log("\nnodeType, nodeName, tagName")
let textChildNode = testNode.firstChild;
console.log(textChildNode.nodeType);
console.log(textChildNode.nodeName);

console.log(testNode.nodeType);
console.log(testNode.nodeName);
console.log(testNode.tagName);

//Data
console.log("\ndata")
console.log(textChildNode.data);
textChildNode.data = "Hi";

//hidden
test3.hidden = true;
setInterval(() => test3.hidden = !test3.hidden, 1000);

console.log("\nouterHTML")
console.log(testNode2.childNodes);
console.log(testNode2.outerHTML);
console.log(testNode2.nodeType);
console.log(testNode2.nodeName);
console.log(testNode2.tagName);
console.log("\nafter outerHTML")
testNode2.outerHTML = "<h3 id='test2'> Modification with outerHTML <p> New Hello <p> <h3>"

let newTestNode = document.querySelector("#test2");
console.log(newTestNode.childNodes);
console.log(newTestNode.outerHTML);
console.log(newTestNode.nodeType);
console.log(newTestNode.nodeName);
console.log(newTestNode.tagName);

//Content of h3 . text + p . Into p we have text
console.log(newTestNode.childNodes[0]);
console.log(newTestNode.childNodes[1].firstChild);
