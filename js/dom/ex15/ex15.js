"use strict";

const test = document.querySelector("#test3");

test.textContent = "Hello";

document.addEventListener("DOMContentLoaded", e => {
	console.log("DOMContentLoaded event");
	console.log(document.readyState);
});

window.addEventListener("load", e => {
	console.log("Load event");
	console.log(document.readyState);
});

document.addEventListener("readystatechange", e => {
	console.log("readystatechange event");
	console.log(document.readyState);
});

window.addEventListener("beforeunload", e => {
	console.log("beforeunload event");
	e.preventDefault();
	e.returnValue = "";
});

