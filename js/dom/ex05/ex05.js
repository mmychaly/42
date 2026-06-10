"use strict";

const test = document.querySelector("#other");

test.textContent = "Salut fjdifuofoisfoisfoi egt tdbbtvwtd gqtgqetg qethqethqethqeth sfpoisvpisvp sivppivspsrvp srvsprv sorppsovrposcpvsoprovs sropvo srpovs vrovsrposv$ eso^srv sr^v";

const test2 = document.querySelector("#test2");

test2.textContent = "Hello";

//clientWidth + clienHeight

console.log("clientWidth: ", test.clientWidth);
console.log("clienHeight: ", test.clientHeight);

//offsetTop + offsetLeft

console.log("offsetTop: ", test.offsetTop);
console.log("offsetLeft: ", test.offsetLeft);

//scrollHeight + scrollTop

console.log("scrollHeight: ", test.scrollHeight);
console.log("scrollTop: ", test.scrollTop);

let int = setInterval(() => {
	test.scrollTop += 30
	console.log("in setInterval scrollTop: ", test.scrollTop);
	if (test.scrollTop + test.clientHeight >= test.scrollHeight)
	{
		test.scrollTop = 0;
		clearInterval(int);
	}	
}, 1000);