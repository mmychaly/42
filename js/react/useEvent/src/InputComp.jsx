import { useState } from 'react'

function InputFunc({handleChange})
{
	return <input onChange={handleChange} />
}

function InputComp()
{
	const [text, setText] = useState("Mika");
	function handleChange (event)
	{
		setText(event.target.value);
	}

	return (
		<>
			<h1>Use event react</h1>
			<InputFunc handleChange={handleChange}/>
			<p>{text}</p>
		</>
	)
}

export default InputComp;