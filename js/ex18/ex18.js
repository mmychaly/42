"use strict";


const testObj = document.getElementById("test1");
const testObj2 = document.getElementById("test2");

class User{
	static counter = 0; //Static variable . appartien que a class
	rules = false; //Simple property
	#_privateRule = false;

	constructor(name, age, email)
	{
		User.counter++;
		this.name = name;
		this.age = age;
		this.email = email;
	}

	sayHi() {console.log(`Hello, my name is ${this.name}`)};//Method of class in User.prototype
	saySimpleHi() {console.log("Salut!")};
	showUser() { return `User: ${this.name}, ${this.age}, ${this.email}`};

	#_showPrivateRule() {return this.#_privateRule};
	#_setPrivateRule(value) {
		if (value == true || value == false)
			this.#_privateRule = value;
	};

	usePrivateMethod() {console.log(this.#_showPrivateRule())};
	setPrivateMethod(value) {this.#_setPrivateRule(value)};
	
	get userRules() {console.log(`User ${this.name} has rules: ${this.rules}. Information from getter`)}; //Getter for display value
	set userRules(value) {
		if (value == true)
			this.rules = value;
	} ;//Setter for set a value

	static showCounter() {console.log(User.counter)};
}

let newUser = new User("Mika", 34, "mmychaly@dfdfdf.com");
let user2 = new User("Alizée", 32, "a_alizée@ffsfsfs.com");

newUser.sayHi();//Use method from class
//newUser.showRules();

console.log("\nUse getter and setter in class");
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

console.log("\nTry acces for private property, privateRule in second user");
user2.usePrivateMethod();

class OtherData extends User {
	constructor(name, age, email, city, number)
	{
		super(name, age, email);
		this.city = city;
		this.number = number;
	}

	sayHiFromUser() {
			super.saySimpleHi();
	}
	
	showFullUser() {
		console.log(super.showUser(), this.city, this.number);
	}
}

let fullUser = new OtherData("Mychaly", 34, "mmychaly@dfdf.com", "Paris", "07649949");

console.log("\nTest heritage de class");
fullUser.sayHi();
fullUser.saySimpleHi();
fullUser.showFullUser();
console.log(fullUser.showUser());

console.log("\nUse static variable and methode");
User.showCounter();