"use strict";

const artic = document.querySelector("article");
const test2 = document.querySelector("#test2");
const btn4 = document.querySelector("#btn_4");
const bodyTest = document.body;
const btn3 = document.querySelector("#btn_3");

//Bubbling phase, propogation d'envenement
document.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.nodeName}. Phase ${event.eventPhase}`);
},);
artic.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}. Phase ${event.eventPhase}`);
});
test2.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}. Phase ${event.eventPhase}`);
});

//Use stopPropagation
btn4.addEventListener("click", (event) => {
	console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}. Phase ${event.eventPhase}`);
	event.stopPropagation();
});

//Capturing phase.
btn3.addEventListener("click", (event) => console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}. Phase ${event.eventPhase}`), true);
bodyTest.addEventListener("click", (event) => console.log(`Target: ${event.target.tagName} , id: ${event.target.id}. Current Target: ${event.currentTarget.tagName}. Phase ${event.eventPhase}`), true);
