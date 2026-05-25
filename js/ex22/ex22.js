"use strict";

let numArray = [1, 5 , 9];
let strArray = ["salut", "hello", "privet"];
let objArray = [ {user: "Mika"}, {user: "Alizée"}];

console.log("Array lenght == ", numArray.length);
numArray.forEach((value, index) => console.log(index, value));
strArray.forEach(value => console.log(value));
objArray.forEach(value => {console.log(value)
	for (let key in value)
		console.log(`Key: ${key}.Value: ${value[key]}`);
});

console.log("\nTest pop/shift")
numArray.pop();
numArray.shift();
for (let value of numArray)
	console.log(value);
console.log("\ntest push/unshift")
numArray.push(42);
numArray.unshift(21);
numArray.forEach((value, index) => console.log(index, value));


console.log("Test splice ", numArray);
numArray.splice(1,1);
numArray.forEach((value, index) => console.log(index, value));

console.log("\nTest map");
let objArrayNew = objArray.map(value => value.user);
console.log(objArrayNew);


console.log("\nTest filter");
let newFiltArray = numArray.filter(value => {
	if (value == 42)
			return value;
});
console.log(newFiltArray);

console.log("Test find and reverse");
let res = numArray.find(val => val == 42);

let otherRes = numArray.reverse();
console.log("Find: ", res);
console.log("Reverse: ", otherRes);

console.log("Test sort");
otherRes.push(-2);
otherRes.sort((a,b) => a - b);
console.log("Sort: ", otherRes);

console.log("\nTest deep Copy");
let copy = structuredClone(objArrayNew);
objArrayNew[0] = "TOto";
console.log("Copy");
copy.forEach(el => console.log(el));
console.log("Parent");
objArrayNew.forEach(el => console.log(el));


