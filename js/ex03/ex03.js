"use strict"

let num = 5;
let str = "Salut";
let char = 'c';
let double = 0.5;
let obj = { key: "stringObj", num: 5};

console.log(num, str, char, double, obj);

let docObj1 = document.getElementById("test1");
let docObj2 = document.getElementById("test2");
let docObj3 = document.getElementById("test3");

docObj1.textContent = obj.key;
docObj2.textContent = obj.num;
docObj3.textContent = str;