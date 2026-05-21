"use strict";

import * as math from "./math.js"
import User from "./user.js"
import {counter, showElement} from "./other.js"

let a = 10;
let b = 5;

console.log("\nUse import total")
console.log(math.add(a,b));
console.log(math.sub(a,b));
console.log(math.div(a,b));
console.log(math.mul(a,b));

console.log("\nUse import default of class");

const objTest = document.getElementById("test1");

let myUser = new User("Mika", 34, "mmychaly@dfdfdf.com");

objTest.textContent = myUser.showUser();

console.log("\nUse import named of function");

console.log(showElement(myUser));
console.log(counter);