import {useState} from 'react'

function ConditComp()
{
	const [number, setNumber] = useState(0);

	function handlerNumber()
	{
		setNumber(number + 1);
	}
	let message ;
	if(number === 10)
	{
		message = <>
			<button onClick={handlerNumber}>+1</button>
			<p>Number equal ten!</p>
		</>;
	}

	else if (number === 15)
	{
		message = <>
			<button onClick={handlerNumber}>+1</button>
			<p>Number equal Fifteen!</p>
		</>;
	}
	else
	{
		message = <>
			<button onClick={handlerNumber}>+1</button>
			<p>{number} est {number % 2 === 0 ? "pair": "impair"}</p>
			<p>{number % 2 === 0 && "It's really pair!"}</p>
		</>
	}


	return ( <>{message}</>);
}

export default ConditComp;