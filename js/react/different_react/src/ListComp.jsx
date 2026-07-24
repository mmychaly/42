import {useState} from 'react'

export function ListComp()
{
	const [list, setList] = useState(["Mika", "Alizée", "Sacha"]);

	return (<>
				<h3>Simple list</h3>
				<ol>
					{list.map(element => <li>{element}</li>)}
				</ol>
	
	</>);
}

export function ListCompObj()
{
	const [list_obj, setList] = useState([{ id:"1a", name: "Sacha", age:33}, { id:"1t", name: "Mika", age:34}, { id:"1b", name: "Alizée", age:32}, ]);

	return (<>
				<h3>List with obj and key</h3>
				<ul>
					{list_obj.map(element => <li key={list_obj.id}>Id: {element.id} / {element.name} {element.age}</li>)}
				</ul>
	
	</>);
}