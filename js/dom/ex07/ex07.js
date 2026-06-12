"use strict";

const test1 = document.querySelector("#test1");
const test2 = document.querySelector("#test2");
const test3 = document.querySelector("#test3");

test1.textContent = "ldslps sppsd";
test2.textContent = "scess cscd";
test3.textContent = "scs ccesc<s  qssc";

console.log("Use getBoundingClientRect");
let data = test1.getBoundingClientRect();
console.log(data);

