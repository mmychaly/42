import { useState } from "react";

function UserInput({user, storageInput, handlerSubmit, handlerChange})
{
	return (
		<>
			<form onSubmit={handlerSubmit}>
				<input onChange={handlerChange} type="text" name="name" value={storageInput.name} />
				<input onChange={handlerChange} type="text" name="age" value={storageInput.age}/>
				<input onChange={handlerChange} type="email" name="email" value={storageInput.email}/>
				<button type="submit">Send</button>
			</form>
		</>
	);
}

function Anki()
{
	const [user, setUser] = useState({name:"", age:"", email:""});
	const [storageInput, setStorageInput] = useState({name:"", age:"", email:""});
	
	function handlerChange(event)
	{
		const {name, value} = event.target;
		setStorageInput(prev => ({...prev, [name]:value}));
		console.log(name, value);
	}


	function handlerSubmit(event)
	{
		event.preventDefault();
		const form = new FormData(event.target);
		form.append("city", "paris");
		console.log("Test of FormData");
		for (const [key, value] of form)
			console.log(key, ":", value);
		console.log("Test of FormData after set and delete");
		form.set("age", "35");
		form.delete("city");
		for (const [key, value] of form)
			console.log(key, ":", value);
		setUser(prev => ({...prev, name:form.get("name"), age:form.get("age"), email:form.get("email")}));
	}
	return (
		<>
			<p>Form and FormData</p>
			<UserInput user={user} storageInput={storageInput} handlerSubmit={handlerSubmit} handlerChange={handlerChange}/>
			<p>Data</p>
			<p>User: {user.name}</p>
			<p>Age: {user.age}</p>
			<p>Email: {user.email}</p>
		</>
	);
}

export default Anki;

//pouvoir saissier les donnés
//afficher les donnés