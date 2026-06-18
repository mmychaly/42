"use strict";

console.log("Focus active : ", document.activeElement);

let name_1 = document.forms[0].elements[0];
let name_2 = document.forms[1].elements[0];

//name_2.focus();

name_2.addEventListener("focus", e => console.log("focus form 2"));

//name_1.focus();

name_2.addEventListener("blur", e => console.log("Blur form 1"));


name_1.addEventListener("focus", e => {console.log("Focus active : ", document.activeElement);
	console.log("focus form 1");
});

//name_1.focus();

name_1.addEventListener("blur", e => console.log("Blur form 1"));

//name_1.blur();

let copy = document.getElementById("copyright");
copy.addEventListener("focus", e => console.log("focus copy"));

copy.focus();