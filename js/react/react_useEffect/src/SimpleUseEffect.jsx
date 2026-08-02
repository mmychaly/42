import {useState, useEffect} from "react"

function SimpleUseEffect()
{
	const [values, setValues] = useState("");
	const [other, setOther] = useState("");
	console.log("rendering composant");

	useEffect(() => {
		console.log("Launch useEffect without []");
	});

	useEffect(() => {
		console.log("Launch useEffect with []");
	}, []);

	useEffect(() => {
		console.log("Launch useEffect with [state]");
		console.log("State values: ", values);
	}, [values]);

	function handleValue(event)
	{
		setValues(event.target.value);
	}

	
	function handleOther(event)
	{
		setOther(event.target.value);
	}


	return (<>
			<p>{values}</p>
			<p>{other}</p>
			<input value = {values} onChange = {handleValue} />
			<input value = {other} onChange = {handleOther} />
	</>);

}


export default SimpleUseEffect;