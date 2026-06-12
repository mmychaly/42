"use strict"

const inputTest = document.querySelector("#test2");

//console.log(inputTest.value);

inputTest.addEventListener("input", (event) => {
//	console.log(inputTest.value);
	console.log(event);
});

const btn = document.querySelector("button");

btn.addEventListener("click", (event) => console.log(event));