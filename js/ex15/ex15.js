"use strict";

let obj = {
	name: "Mika",
	age: 34,
	sayHi: () => console.log("Salut")
};

obj.sayHi();

let newObj = Object.create(obj);

newObj.getName = function() {console.log(this.name)};
newObj.getAge = function() {console.log(this.age)};

console.log("\nContent of child object");
for (let key in newObj)
	console.log(`${key} == ${newObj[key]}`);

console.log("\nContent of parent object in child object");
console.log(Object.getPrototypeOf(newObj));

console.log("\nUse all function from children");
newObj.sayHi();
newObj.getName();
newObj.getAge();

console.log("\nCheck all parent variable from children");
let parentName = newObj.name;
console.log(`${parentName}`);
let parentAge = newObj.age;
console.log(`${parentAge}`);