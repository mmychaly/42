import {useState} from 'react'

function Controlled()
{
	const [value, setValue] = useState("");
	const [tempStorage, setTempStorage] = useState("");
	console.log("tempStorage in controlled: ",tempStorage);
	function handlerChange(event)
	{
		const longuer = event.target.value.length;
		console.log(longuer);
		console.log("Event: ", event.target.value);
		if (longuer === 5)
			setTempStorage("");
		else
			setTempStorage(event.target.value)
		console.log("tempStorage: ", tempStorage);
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
				<input value={tempStorage} onChange={handlerChange}/>
				<button type="submit">Submit</button>
				<p>{value}</p>
			</form>
		</>
	);
}

export default Controlled;