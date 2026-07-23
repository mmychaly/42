import {useState} from 'react'

function ConditComp()
{
	const [number, setNumber] = useState(0);

	function handlerNumber()
	{
		setNumber(number + 1);
	}

	return (
		<>
			<button onClick={handlerNumber}>+1</button>
			<p>{number} est {number % 2 === 0 ? "pair": "impair"}</p>
			<p>{number % 2 === 0 && "It's really pair!"}</p>
		</>

	);
}

export default ConditComp;