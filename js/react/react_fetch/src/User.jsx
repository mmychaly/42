import {useEffect, useState} from 'react'

function Users()
{
	const [users, setUsers] = useState([]);
	const [loading, setLoading] = useState(true);
	const [error, setError] = useState(false);

	useEffect(() => {
		async function usersFetch()
		{   
			try{
				const respond = await fetch("https://httpstat.us/404");
				if (!respond.ok)
					throw new Error(`HTTP ${respond.status}`);
				const data = await respond.json();
				setUsers(data);
			}
			catch (err){
				setError(err.message);
			}
			finally {
				setLoading(false);
			}
		}

		usersFetch();
	}, []);

	if (loading) return <p>Loading...</p>;
	if (error) return <p>Error: {error}</p>;

	return (<>
				{users.map((item) => 
					(<div key={item.id} style={{marginBottom: "16px" }}>
						<p>User: {item.name}</p>
						<p>Email: {item.email}</p>
					</div>))};
			</>)
}

export default Users;

//https://jsonplaceholder.typicode.com/users

//https://httpstat.us/404