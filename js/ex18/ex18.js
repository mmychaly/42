"use strict";


const testObj = document.getElementById("test1");
const testObj2 = document.getElementById("test2");

class User{

	rules = false; //Simple property
	#privateRule = false;

	constructor(name, age, email)
	{
		this.name = name;
		this.age = age;
		this.email = email;
	}

	sayHi() {console.log(`Hello, my name is ${this.name}`)};//Method of class in User.prototype
	showUser() { return `User: ${this.name}, ${this.age}, ${this.email}`};

	#showPrivateRule() {return this.#privateRule};
	#setPrivateRule(value) {
		if (value == true || value == false)
			this.#privateRule = value;
	};

	usePrivateMethod() {console.log(this.#showPrivateRule())};
	setPrivateMethod(value) {this.#setPrivateRule(value)};
	
	get userRules() {console.log(`User ${this.name} has rules: ${this.rules}`)}; //Getter for display value
	set userRules(value) {
		if (value == true)
			this.rules = value;
	} ;//Setter for set a value
}

let newUser = new User("Mika", 34, "mmychaly@dfdfdf.com");
let user2 = new User("Alizée", 32, "a_alizée@ffsfsfs.com");

newUser.sayHi();
//newUser.showRules();
newUser.userRules; //Launch getter. We don't make value
newUser.userRules = true; // For launch setter ae need add a value
newUser.userRules;

testObj.textContent = newUser.showUser();
testObj2.textContent = user2.showUser();

console.log("\nDisplay simple property ", newUser.rules); //We can display property simple == true
console.log("\nTry acces for private property, privateRule: ", newUser.privateRule);
console.log("Try acces for private property, privateRule with private method usePrivateMethod");
newUser.usePrivateMethod();
console.log("Try set other value for private property, privateRule with private method setPrivateMethod");
newUser.setPrivateMethod(true);
newUser.usePrivateMethod();

