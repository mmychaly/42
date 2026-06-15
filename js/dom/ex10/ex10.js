"use strict";

//Transition bloquée vers une autre page

const link = document.querySelector("#link");

link.addEventListener("click", (event) => {
	event.preventDefault();
	console.log("Google link is blocked");
	console.log("defaultPrevented: ", event.defaultPrevented);
});

//rafraîchissement de la page bloquée
const form = document.querySelector("#form");
const inputTest = document.querySelector("#input");

form.addEventListener("submit", (event) => {
	let content = inputTest.value;
	event.preventDefault();
	if (content === "")
	{
		console.log("Vide");
		return;
	}

	console.log("Form is send: ", content);
});

//context menu bloquée
document.addEventListener("contextmenu", (event) => event.preventDefault());
