"use strict";

let prom = new Promise((resolve, reject) => resolve("Launch callback in microtask"));

console.log("Test promise.Befor");
prom.then((result) => console.log(result));
console.log("Test promise.After");
console.log("Console.log prom ", prom);
let newProm = prom.then(result => result);
console.log("Console.log newProm ", newProm);

console.log("\nFast promise syntax");

Promise.resolve("My message from promise").then(r => console.log(r));

let errProm = new Promise((resolve, reject) => reject("We have a problem!"));

errProm.then(console.log("errProm in then"))
		.catch(p => console.log("errProm in catch " + p));

