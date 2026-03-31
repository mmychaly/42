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
let docObj4 = document.getElementById("test4");
let docObj5 = document.getElementById("test5");
let docObj6 = document.getElementById("test6");

docObj1.textContent = obj;
docObj2.textContent = obj.num;
docObj3.textContent = str;

str = "New_string";
docObj4.textContent = str;

const constStr = "Hello";
docObj5.textContent = constStr;

// constStr = "NewConstStr"; //invalid assignment to const 'constStr'
// docObj6.textContent = constStr;
// console.log(constStr);

var varObj = obj;
docObj6.textContent = varObj.key;

let und;
console.log(und);//undefined

str = `Combinaison de strings , ${constStr}`;
console.log(str);
console.log("objkey".length);
console.log("objkey".toUpperCase());