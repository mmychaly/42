"use strict";

const articleTest = document.querySelector("article");
const test = document.querySelector("p");

document.addEventListener("mousedown", (event) => 
	{
		console.log(`Event: ${event.type}, Target: ${event.target.tagName}`);
});

document.addEventListener("mouseup", (event) => 
	{
		console.log(`Event: ${event.type}, Target: ${event.target.tagName}`);
});

document.addEventListener("click", (event) => 
	{
		console.log(`Event: ${event.type}, Target: ${event.target.tagName}`);
});

document.addEventListener("dblclick", (event) => 
	{
		console.log(`Event: ${event.type}, Target: ${event.target.tagName}`);
});

// document.addEventListener("mousemove", event =>
// 	{
// 		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, X: ${event.clientX} Y: ${event.clientY}`);
// });

articleTest.addEventListener("mouseover", event => {
 		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
});

articleTest.addEventListener("mouseout", event => {
 		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
});