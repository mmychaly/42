import {useEffect, useState} from 'react'

function Users()
{
	const [users, setUsers] = useState([]);
	const [loading, setLoading] = useState(true);
	const [error, setError] = useState(false);

	useEffect(() => {
		const controller = new AbortController();

		async function usersFetch()
		{   
			try{
				const respond = await fetch("https://jsonplaceholder.typicode.com/users", {signal: controller.signal});
				if (!respond.ok)
					throw new Error(`HTTP ${respond.status}`);
				const data = await respond.json();
				console.log(data);
				setUsers(data);
			}
			catch (err){
				if (err.name !== "AbortError")
					setError(err.message);
			}
			finally {
				setLoading(false);
			}
		}

		usersFetch();
		return () => controller.abort();
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