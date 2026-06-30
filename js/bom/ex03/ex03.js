"use strict";

console.log("Lenght in beginning: ", localStorage.length);
localStorage.setItem("first", 1);
localStorage.setItem("mika", 34);
localStorage.setItem("alizée", 32);
console.log("Lenght after 2 setItem: ", localStorage.length);
console.log(localStorage.key(0), localStorage.getItem(localStorage.key(0)));
console.log(localStorage.key(1), localStorage.getItem(localStorage.key(1)));
console.log(localStorage.key(2), localStorage.getItem(localStorage.key(2)));
localStorage.removeItem(localStorage.key(0));
console.log("Lenght after removeItem: ", localStorage.length);
for (let i = 0; i < localStorage.length; i++)
	console.log(localStorage.key(i), localStorage.getItem(localStorage.key(i)));
localStorage.clear();
console.log("Lenght after removeItem: ", localStorage.length);