"use strict";

const testObj = document.getElementById("test1");


console.log("Use constuctor of function");
let printMsg = new Function("msg", "return msg;");
testObj.textContent = printMsg('Hello');




