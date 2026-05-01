"use strict";

const testObj = document.getElementById("test1");


console.log("Use constuctor of function");
let printMsg = new Function("msg", "return msg;");
testObj.textContent = printMsg('Hello');


let printMsgCons = new Function("msg", "console.log(msg);");


setTimeout(printMsgCons.bind(null, 'Salut'), 1500);
console.log("Use setTimeout with bind");

let idSt = setTimeout(printMsgCons.bind(null, 'He'), 5000);
console.log("Use clearTimeout with bind");
setTimeout(() => clearTimeout(idSt), 1000);

setTimeout(console.log.bind(null, "Use setInterval with bind"), 1500);

let counter = 0;
let idI = setInterval(() => {
							counter++;
							console.log(`Holla ${counter}`);
 }, 2000);
setTimeout(() => clearInterval(idI), 10000);