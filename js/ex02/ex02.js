"use strict"

let obj = document.getElementById("test1").textContent;
document.getElementById("test2").textContent = obj;
document.getElementById("test3").textContent = "salut";

document.getElementById("test2").innerHTML = "<p id='test4'>test4</p> <p id='test5'>test5</p>"
document.getElementById("test4").style.backgroundColor = "red";
document.getElementById("test5").style.backgroundColor = "blue";

document.querySelector("#test3").textContent = "bonjour";

function change()
{
	let test1 = document.getElementById("test1");
	test1.textContent = "New text after change!";
	test1.style.color = "black";
}
