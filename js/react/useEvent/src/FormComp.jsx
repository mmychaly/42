import {useState} from 'react';

function FormFunc({handlerInputChange, handlerSubmit})
{
	return (
		<>
			<form onSubmit={handlerSubmit}>
				<input onChange={handlerInputChange}/>
				<button type="submit">Submit</button>
			</form>
		</>
	);
}


function FormComp()
{
	const [user, setUser] = useState("User");
	const [textIntput, setTextIntput] = useState("");

	function handlerChangeFormInput(event)
	{
		setTextIntput(event.target.value);
	}

	function handlerSubmitForm(event)
	{
		event.preventDefault();
		setUser(textIntput);
	}


	return (
		<>
			<h1>Use event React with form</h1>
			<FormFunc handlerInputChange={handlerChangeFormInput} handlerSubmit={handlerSubmitForm}/>
			<p>{user}</p>
		</>
	);
}

export default FormComp;