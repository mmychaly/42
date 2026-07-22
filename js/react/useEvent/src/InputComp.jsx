import { useState } from 'react'

function InputFunc({handleChange})
{
	return <input onChange={handleChange} />
}

function FormFunc({handleChange})
{
	return (
			<form onSubmit={handleChange}>
				<input />
				<button type="submit">Submit</button>
			</form>
	)
}

function InputComp()
{
	const [text, setText] = useState("Mika");
	function handleChangeInput (event)
	{
		console.log("handleChangeInput");
		setText(event.target.value);
	}

	function handleChangeForm (event)
	{
		event.preventDefault();
		console.log("handleChangeForm");
		setText(event.target.elements[0].value);
	}

	return (
		<>
			<h1>Use event react with input + form</h1>
			<InputFunc handleChange={handleChangeInput}/>
			<FormFunc handleChange={handleChangeForm}/>
			<p>{text}</p>
		</>
	)
}

export default InputComp;