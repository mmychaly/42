"use strict"


let docObject = document.getElementById("test2");
let startBtn = document.getElementById("startBtn")

startBtn.addEventListener("click", () => {
	let message = alert("Merci d'accepter!");
	let isBoolen = confirm("Do you agree transmit information?");
	if (isBoolen)
	{
		let age = prompt("How old are you?");
		if (age != null && age != "")
			docObject.textContent = "You answered: " + age;
	}
	else
		docObject.textContent= "You didn't respond";
});




