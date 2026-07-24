import {useState} from 'react'

function ListComp()
{
	const [list, setList] = useState(["Mika", "ALizée", "Sacha"]);

	return (<>
				<ul>
					{list.map(element => <li>{element}</li>)}
				</ul>
	
	</>);
}

export default ListComp;