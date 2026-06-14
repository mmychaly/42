"use strict";

const artic = document.querySelector("article");
const test2 = document.querySelector("#test2");
const btn4 = document.querySelector("#btn_4");
//Bubbling phase, propogation d'envenement
document.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.nodeName}`);
});
artic.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}`);
});
test2.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}`);
});

//Use stopPropagation
btn4.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}`);
	event.stopPropagation();
});

