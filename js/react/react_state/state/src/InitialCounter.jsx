import {useState} from 'react'

function ButtonRaiseCounter({func})
{
	return <button onClick={func}> +1 </button>
}

function ButtonResetCounter({func})
{
	return <button onClick={func}> Reset </button>
}


function InitialCounter({value})
{
	const [counter, setCounter] = useState(() => handlerInitial());

	function handlerInitial()
	{
		return value;
	}

	function handlerRaiseOne()
	{
		setCounter(counter + 1);
	}

	function handlerReset()
	{
		setCounter(0);
	}

	return (
		<>
			<h2>Use Counter with props</h2>
			<ButtonRaiseCounter func={handlerRaiseOne} />
			<ButtonResetCounter func={handlerReset} />
			<p>{counter}</p>
		</>
	);
}

export default InitialCounter;