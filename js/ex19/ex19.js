"use strict";


class AnimalOwner{
	constructor(name)
	{
		this.name = name;
	}

	showAnimalOwner() {console.log(`Owner of animal is ${this.name}`)};
}

let animalAction = {
	goEat() {console.log(`${this.petName} eat!`)},
	goWalk() {console.log(`${this.petName} walk!`)}
}



class Cat extends AnimalOwner{
	constructor(name, petName, color){
		super(name);
		this.petName = petName;
		this.color = color;
	}

	showCat() {console.log(`Cat name is ${this.petName}, his color is: ${this.color}`)};
}

class Dog extends AnimalOwner{
	constructor(name, petName, color){
		super(name);
		this.petName = petName;
		this.color = color;
	}

	showDog() {console.log(`Dog name is ${this.petName}, his color is: ${this.color}`)};
}

Object.assign(Dog.prototype, animalAction);
Object.assign(Cat.prototype, animalAction);

let myDog = new Dog("Mika", "Bloody", "black");
let newDog = new Dog("Alizée", "Pig", "white");

let myCat = new Cat("Mika", "Lolo", "white");
let newCat = new Cat("Alizée", "Damnf", "brown");

myDog.showDog();
myDog.showAnimalOwner();
myDog.goEat();
myDog.goWalk();

newDog.showDog();
newDog.showAnimalOwner();
newDog.goEat();
newDog.goWalk();

myCat.showCat();
myCat.showAnimalOwner();
myCat.goEat();
myCat.goWalk();

newCat.showCat();
newCat.showAnimalOwner();
newCat.goEat();
newCat.goWalk();


console.log("\nTest try catch");

//sayHelloNew(); //Sans try catch ici le programme s'arret mais avec try catch on recois les error mais l'execution continue

try {
	console.log("We are in try");
	sayHello();
} catch(err){
	console.log("We are in catch");
	console.log(err);
	console.log("Just error name: ", err.name);
	console.log("Just error message: ", err.message);

} finally {
	console.log("We are in finally");
}

console.log("After try catch");

console.log("\nTest throw");

try {
	console.log("In try befor throw");
	throw new Error("Error enforced");
	console.log("In try after throw");
} catch(err)
{
	console.log("In catch");
	console.log(err.message);
}
console.log("After try catch");
