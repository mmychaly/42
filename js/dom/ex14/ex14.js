"use strict";

const myForm = document.querySelector("#userData");

myForm.addEventListener("input", e => {
	if (e.type === "input" && e.target.name === "name")
	{
		console.log("input event: ", e.type);
		let data = new FormData(myForm);
		console.log(data.get("name"));
	}
});

myForm.addEventListener("change", e => {
	if (e.type === "change" && e.target.name === "email")
	{
		console.log("change event");
		let data = new FormData(myForm);
		console.log(data.get("email"));
	}
});

myForm.addEventListener("submit", e => {
	e.preventDefault();
	console.log("submit event");
	let data = new FormData(myForm);
	console.log(`All data.\nName: ${data.get("name")}.\nEmail: ${data.get("email")}.\nPassword: ${data.get("password")}.`);
});

//myForm.requestSubmit();