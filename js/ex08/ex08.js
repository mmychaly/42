"use strict";

const objTest1 = document.getElementById("test1");
const objTest2 = document.getElementById("test2");
const objTest3 = document.getElementById("test3");
const objTest4 = document.getElementById("test4");
const objTest5 = document.getElementById("test5");
const objTest6 = document.getElementById("test6");
const objTest7 = document.getElementById("test7");
const objTest8 = document.getElementById("test8");
const objTest9 = document.getElementById("test9");
const objTest10 = document.getElementById("test10");

let numStr = "42";
let float1 = 34.5;
let float2 = 34.3;
let float3 = 2.5;
let float4 = 10.3;
let num = Number(numStr);



objTest1.textContent = num;
objTest2.textContent = Math.round(float1);
objTest3.textContent = Math.round(float2);
objTest4.textContent = Math.floor(float3);
objTest5.textContent = Math.ceil(float4);

let array = [2, 0, 100, -8];
objTest6.textContent = Math.min(...array);//attention il faut faire la copy
objTest7.textContent = Math.max(...array);

console.log("Conversation");
let newStr = num.toString();
console.log(num, " :", typeof num);
console.log(newStr, " :", typeof newStr);
let numInt = parseInt("5gf");
let numFloat = parseFloat("2.8");
console.log("5gf", " ", typeof "5gf", " :", numInt , " ", typeof numInt);
console.log("2.8", " ", typeof "2.8", " :", numFloat , " ", typeof numFloat);

console.log("Check NaN");
let isNumb = Number.isNaN(num);
let isNumb2 = Number.isNaN(newStr);
let isNumb3 = Number.isNaN("sdds");
let isNumb4 = Number.isNaN(NaN);
console.log(num, " ", typeof num, " :", isNumb);
console.log(newStr, " ", typeof newStr, " :", isNumb2);
console.log("sdds", " ", typeof "sdds", " :", isNumb3);
console.log(NaN, " ", typeof NaN, " :", isNumb4);
console.log("!Number.isNaN(Number('sdds')) ", !Number.isNaN(Number("sdds")));