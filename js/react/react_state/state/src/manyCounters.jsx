import { count } from 'console';
import {useState} from 'react'

function ButtonForOne({func})
{
	<button onClick={func}> +1 </button>;
}
function ButtonForFive({func})
{
	<button onClick={func}> +5 </button>;
}

function ButtonReset({func})
{
	<button onClick={func}> Reset </button>;
}

function ManyCounters()
{
	const [counter_1, setCounter_1] = useState(0);
	const [counter_2, setCounter_2] = useState(0);

	function handlerRaiseForOne()
	{
		setCounter_1(counter_1 + 1);
		setCounter_2(counter_2 + 1);
	}

	function handlerRaiseForFive()
	{
		setCounter_1(counter_1 + 5);
		setCounter_2(counter_2 + 5);
	}

	function handleReset()
	{
		setCounter_1(0);
		setCounter_2(0);
	}

	return (
		<>
			<h2>Use different counters</h2>
			<p>Counter A: {counter_1}</p>
			<ButtonForOne func={ButtonForOne} />
			<ButtonForFive func={ButtonForFive} />
			<ButtonReset func={ButtonReset} />
			<p>Counter A: {counter_1}</p>
			<ButtonForOne func={ButtonForOne} />
			<ButtonForFive func={ButtonForFive} />
			<ButtonReset func={ButtonReset} />
		</>
	);
}

export default ManyCounters;