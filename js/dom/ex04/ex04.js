"use strict";


const testElem = document.querySelector(".test1");
const testElem2 = document.querySelector(".test2");
const testElem3 = document.querySelector("#test3");
testElem.textContent ="Hi!!!";

console.log("Use className");

console.log("Class name: ", testElem2.className);
testElem2.className = "second";
console.log("New class name: ",testElem2.className);


console.log("\nUse classListe");

console.log(testElem.classList);
testElem.classList.remove("first");
testElem.classList.add("other");
testElem.classList.toggle("test1");
console.log("Classes after add/remove/toggle");
for (let key of testElem.classList)
	console.log(key);
console.log("Use contains");
console.log("Other is a class ?", testElem.classList.contains("other"));
console.log("first is a class ?", testElem.classList.contains("first"));
// Use object style
testElem3.textContent = "Salut";
testElem3.style.color = "blue";


console.log("\nUse getComputedStyle");

let styles = getComputedStyle(testElem);
console.log("color: ", styles.color);
console.log("color from getPropertyValue: ", styles.getPropertyValue("color"));
console.log("font-size: ", styles.fontSize);
