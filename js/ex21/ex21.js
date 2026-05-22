"use strict";


console.log("test fetch");

try {
	async function createGet(){
		let response = await fetch("https://jsonplaceholder.typicode.com/users");
		if (!response.ok)
			throw new Error(`Error HTTP ${response.status}`);
		let data = await response.json();
		console.log(data);
		data.forEach(user => console.log(user.name, user.email));
	}
	createGet();
	async function creatPost(){
		let response = await fetch("https://jsonplaceholder.typicode.com/posts", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ title: "Mon post", body: "Contenu", userId: 1 })
    });
		if (!response.ok)
			throw new Error(`Error HTTP ${response.status}`);
		let data = await response.json();
		console.log(data);
		for (let key in data)
			console.log(key, data[key]);
	}
	creatPost();

} catch(err) {
	console.log(err.message);
}


