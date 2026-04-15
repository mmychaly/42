"use strict"


let array = {
	user1: { name: Mika, age: 34},
	user2: { name: Alizée, age: 32},
	};

//Display on the page  
let docObj1 = document.getElementById("test1");
let docObj2 = document.getElementById("test2");
let docObj3 = document.getElementById("test3");
let docObj4 = document.getElementById("test4");
let docObj5 = document.getElementById("test5");
let docObj6 = document.getElementById("test6");
let docObj7 = document.getElementById("test7");
let docObj8 = document.getElementById("test8");
let docObj9 = document.getElementById("test9");

docObj1.textContent = array;
docObj2.textContent = array[0];
docObj3.textContent = array[1];
docObj4.textContent = array[2];


