import {useEffect, useState} from 'react'
import { Fragment } from 'react';

function Users()
{
	const [user, setUser] = useState([]);

	useEffect(() => { 
		async function usersFetch()
		{
			const respond = await fetch("https://jsonplaceholder.typicode.com/users");
			const data = await respond.json();
			setUser(data);
		}

		usersFetch();
	}, []);

	return (<> 
		{user.map((item) => (
			<div key={item.id} style={{marginBottom: '16px'}}>
				<p>User: {item.name}.</p>
				<p>Email: {item.email}.</p>
			</div>))}
	</>);
}

export default Users;