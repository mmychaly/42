"use strict";

console.log("Test promise.Befor");
let prom = new Promise((resolve, reject) => resolve("Launch callback from promis in microtask"));
prom.then((result) => console.log(result));
console.log("Test promise.After");

let newProm = prom.then(result => `Use first promise for create seconde, ${result}`); //Return new promise
newProm.then(r => console.log("Launch new promise: " + r));

setTimeout(() => {
	Promise.resolve("\nLunch with, fast promise syntax").then(r => console.log(r));//Promise.resolve() == status fulfiled

	Promise.resolve("Test reject promise").then(r => console.log(r));
	let errProm = new Promise((resolve, reject) => reject("We have a problem!"));//Status reject

	errProm.then(r =>console.log("Error in then" + r))
			.catch(p => console.log("Error in catch " + p));//We execute console.log in catch
},2000);

setTimeout(() => {
function promFunc ()
{
	console.log("Launch promFunc in await")
	return new Promise((resolve, rejcet) => {
		setTimeout(() => resolve("Salut it's promis from promFunc"), 2000);
	});
}

async function asyncFunc() {
	console.log("\nTest async function.");
	console.log("In async befor await");
	let promAsync = await promFunc();
	console.log("In async function ", promAsync);
	console.log("In async function after await");
}

asyncFunc();

 }, 4000);