import {useState, useEffect} from 'react'

function Interval()
{
	const [counter, setCounter] = useState(0);

	useEffect(() => {
		const id = setInterval(() => setCounter(prev => prev + 1), 2000);
		console.log("launch useEffect");
		return () => (clearInterval(id));
	}, []);

	return (<>
				<p>Counter: {counter}</p>
	</>);
}

export default Interval;