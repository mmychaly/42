import {useState} from 'react'

function ButtonForOne({func})
{
	return <button onClick={func}> +1 </button>;
}
function ButtonForFive({func})
{
	return <button onClick={func}> +5 </button>;
}

function ButtonReset({func})
{
	return <button onClick={func}> Reset </button>;
}

function ManyCounters()
{
	const [counter_1, setCounter_1] = useState(0);
	const [counter_2, setCounter_2] = useState(0);

	function handlerRaiseForOneFirst()
	{
		setCounter_1(counter_1 + 1);
	}

	function handlerRaiseForOneSecond()
	{
		setCounter_2(counter_2 + 1);
	}

	function handlerRaiseForFiveFirst()
	{
		setCounter_1(counter_1 + 5);
	}

	function handlerRaiseForFiveSecond()
	{
		setCounter_2(counter_2 + 5);
	}

	function handleResetFirst()
	{
		setCounter_1(0);
	}

	function handleResetSecond()
	{
		setCounter_2(0);
	}

	return (
		<>
			<h2>Use different counters</h2>
			<p>Counter A: {counter_1}</p>
			<ButtonForOne func={handlerRaiseForOneFirst} />
			<ButtonForFive func={handlerRaiseForFiveFirst} />
			<ButtonReset func={handleResetFirst} />
			<p>Counter B: {counter_2}</p>
			<ButtonForOne func={handlerRaiseForOneSecond} />
			<ButtonForFive func={handlerRaiseForFiveSecond} />
			<ButtonReset func={handleResetSecond} />
		</>
	);
}

export default ManyCounters;