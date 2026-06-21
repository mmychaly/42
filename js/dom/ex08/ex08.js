"use strict"

const inputTest = document.querySelector("#test2");

//Use addEventListener with function anonymous

inputTest.addEventListener("input", (event) => {
	console.log(inputTest.value);
});

//Use addEventListener with named function
const btn = document.querySelector("#btn1");

function diplayEvent(event)
{
	console.log("Type: ", event.type);
	console.log("Target: ", event.target);
	console.log("X: ", event.clientX, " | ", "Y: ", event.clientY);
}

btn.addEventListener("click", diplayEvent);


//Use Property DOM onclick

const btn3 = document.querySelector("#btn3");

function sayHello(){
	console.log("Hello from .js")
}
btn3.onclick = sayHello;


const btn4 = document.querySelector("#btn4");

function removeFunc()
{
	console.log("This is remove function");
}

btn4.addEventListener("click", removeFunc);

btn4.removeEventListener("click", removeFunc);