"use strict"


const docObject = document.getElementById("test2");
const startBtn = document.getElementById("startBtn")
const modalObj = document.getElementById("modal");
const openBtn = document.getElementById("openBtn");
const closeBtn = document.getElementById("closeBtn");

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

openBtn.addEventListener("click", () => {
	modalObj.style.display = "block";
});

closeBtn.addEventListener("click", () => {
	modalObj.style.display = "none";
});


