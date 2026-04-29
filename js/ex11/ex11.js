"use strict";

const testObject1 = document.getElementById("test1");

testObject1.textContent = "Closure.Watch in console."
function counterFunc()
{
	let count = 0;

	return function() {
		return count++;
	}
}

let counter = counterFunc();
console.log("Function counter 1: ", counter());
console.log("Function counter 1: ", counter());
console.log("Function counter 1: ", counter());
console.log("Function counter 1: ", counter());

let newCounter = counterFunc();
console.log("\nFunction counter 2: ", newCounter());
console.log("Function counter 2: ", newCounter());
console.log("Function counter 2: ", newCounter());
console.log("Function counter 2: ", newCounter());

console.log("\nFunction counter 1: ", counter());
console.log("\nFunction counter 2: ", newCounter());

function accountBank(nameAcc) 
{
	let name = nameAcc;
	let balance = 10000;

	return {
		diposit(sum) {balance += sum},
		getName() { return  name},
		getBalance() { return  balance}
	};
}

console.log("\nClosure with 3 function");
let account = accountBank("Mike");
console.log("Account is open. ", account.getName(), " : ", account.getBalance())
account.diposit(1500);
console.log("Add diposite. ", account.getName(), " : ", account.getBalance());