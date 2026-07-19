import {useState} from 'react';

function Button({isChange})
{
	return <button onClick={isChange}>Change</button>
}

function Changer()
{
	const [word, setWord] = useState("Bonjour");
//	const [isChange, setIsChange] = useState(false);

	function handler()
	{
		setWord("Bonsoir");
//		setIsChange(true);
	}

	return (
		<>
			<h2>Use changer</h2>
			<p>Say: {word}</p>
			<Button isChange={handler}/>
		</>
	)
}

export default Changer;