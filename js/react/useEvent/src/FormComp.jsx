import {useState} from 'react';

function FormComp()
{
	const [user, setUser] = useState(["user", "email"]);
	const [textIntputName, setTextIntput] = useState(["", ""]);

	function handlerChangeFormInput(event)
	{
		if (event.target.name == "user")
		{
			setTextIntput(textIntputName.map((value, index) => {
					if (index === 0)
						return value = event.target.value;
					else if (index == 1)
						return value;
			}));
			console.log(`handlerChangeFormInput for user: ${textIntputName[0]}`);
		}
		else if (event.target.name == "email")
		{
			setTextIntput(textIntputName.map((value, index) => {
					if (index === 1)
						return value = event.target.value;
					else if (index == 0)
						return value;
			}));
			console.log("handlerChangeFormInput for email: ", textIntputName[1]);
		}
	}

	function handlerSubmitForm(event)
	{
		event.preventDefault();
		console.log(`handlerSubmitForm. User: ${textIntputName[0]} // email: ${textIntputName[1]}`);
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