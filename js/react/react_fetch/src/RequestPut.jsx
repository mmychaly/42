import {useState, useEffect} from 'react'

function RequestPut()
{
	const [obj, setObj] = useState(null);
	const [loading, setLoading] = useState(true);
	const [error, setError] = useState(null);

	useEffect(() => {
		const controller = new AbortController();

		async function putFetch()
		{
			try {
				const respond = await fetch("https://jsonplaceholder.typicode.com/posts/1", {
					method: "PUT",
					headers: {"Content-Type": "application/json"},
					body: JSON.stringify({title:"Test PUT", body:"Hello from PUT request", userId: 1}),
					signal: controller.signal
				});
				if (!respond.ok)
					throw new Error(`${respond.status}`);
				const data = await respond.json();
				setObj(data);
				console.log(data);
			}
			catch(err){
				if (err.name !== 'AbortError')
					setError(err.message);
			}
			finally
			{
				setLoading(false);
			}
		} 

		putFetch();
		return () => controller.abort();

	}, []);

	if (loading) return <p>Loading...</p>;
	if (error) return <p>Error: {error}</p>;
	if (!obj) return null;

	return (
		<>
			<p>Title: {obj.title}</p>
			<p>Body: {obj.body}</p>
			<p>Id: {obj.id}</p>
		</>
	);
}

export default RequestPut;