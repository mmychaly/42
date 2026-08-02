import {useState, useEffect} from 'react'

function Resize()
{
	const [sizes, setSizes] = useState({width: "", height: ""});

	function handleSizes()
	{
		setSizes(prev => ({...prev, width: window.innerWidth, height: window.innerHeight}));
	}

	useEffect(() => {

		handleSizes();
		console.log("Launch useEffect for initial sizes");
	}, []);

	useEffect(() => {
		window.addEventListener("resize", handleSizes);
		console.log("launch useEffect for resize");
		return (() => window.removeEventListener("resize", handleSizes));
	}, []);

	return (
		<>
			<p>{`Width: ${sizes.width} && Height: ${sizes.height}`}</p>
		</>

	);
}

export default Resize;