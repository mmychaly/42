import {useState} from 'react'

function Controlled()
{
	const [value, setValue] = useState("");
	const [tempStorage, setTempStorage] = useState("");
	function handlerChange(event)
	{
		setTempStorage(event.target.value);
		console.log(tempStorage)
	}

	function hadlerSubmit(event)
	{
		event.preventDefault();
		setValue(tempStorage);
	}

	return (
		<>
			<h1>Use controlled components</h1>
			<form onSubmit={hadlerSubmit}>
				<input onChange={handlerChange}/>
				<button type="submit">Submit</button>
				<p>{value}</p>
			</form>
		</>
	);
}

export default Controlled;