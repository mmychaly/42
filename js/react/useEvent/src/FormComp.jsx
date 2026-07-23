import {useState} from 'react';

function FormComp()
{
	const [user, setUser] = useState(["user", "email"]);
	const [textIntputName, setTextIntput] = useState(["", ""]);

	function handlerChangeFormInput(event)
	{
		const {name, value} = event.target;
		const index = name === "user" ? 0 : 1;

		setTextIntput(prev => prev.map((v, i) => i === index ? value : v));
	}

	function handlerSubmitForm(event)
	{
		event.preventDefault();
		setUser([...textIntputName]);
	}


	return (
		<>
			<h1>Use react event with form</h1>
			<form onSubmit={handlerSubmitForm}>
				<input name="user" onChange={handlerChangeFormInput}/>
				<input name="email" onChange={handlerChangeFormInput}/>
				<button type="submit">Submit</button>
			</form>
			<p>"User: "{user[0]}</p>
			<p>"Email: "{user[1]}</p>
		</>
	);
}

export default FormComp;