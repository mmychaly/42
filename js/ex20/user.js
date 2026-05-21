export default class User {
	constructor(name, age, email)
	{
		this.name = name;
		this.age = age;
		this.email = email;
	}

	showUser() {return `${this.name} ${this.age} ${this.email}`};
}