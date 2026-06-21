"use strict";

const articleTest = document.querySelector("article");
const test = document.querySelector("p");
document.addEventListener("mousedown", (event) => 
	{
		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, Buttom: ${event.button}`);
		if (event.ctrlKey)
			console.log("Ctrl down");
		else if (event.shiftKey)
			console.log("Shift down");
		else if (event.altKey)
			console.log("Alt down");
		else if (event.metaKey)
			console.log("Meta down");
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

// articleTest.addEventListener("mouseover", event => {
//  		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
// });

// articleTest.addEventListener("mouseout", event => {
//  		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
// });

// articleTest.addEventListener("mouseenter", event => {
//  		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
// });

// articleTest.addEventListener("mouseleave", event => {
//  		console.log(`Event: ${event.type}, Target: ${event.target.tagName}, RelatedTarget: ${event.relatedTarget.tagName}`);
// });