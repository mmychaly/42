import {useState, useEffect} from "react"

function RequestPost()
{
	const [obj, setObj] = useState(null);
	const [loading, setLoading] = useState(true);
	const [error, setError] = useState(null);

	useEffect(() => {
		const controller = new AbortController();

		async function UserPostFetch()
		{
			try{
				const respond = await fetch("https://jsonplaceholder.typicode.com/posts", {
					method: "POST",
					headers: {"Content-Type":"application/json"},
					body: JSON.stringify({title:"Test POST", body:"Hello from POST request!", userId:1}),
					signal: controller.signal}, 
				);
				if (!respond.ok)
					throw new Error(`HTTP ${respond.status}`);
				const data = await respond.json();
				setObj(data);
			}
			catch (err){
				if (err.name !== "AbortError")
					setError(err.message);
			}
			finally
			{
				setLoading(false);
			}
		}

		UserPostFetch();

		return () => controller.abort();
	}, []);

	if (loading) return <p>Loading...</p>
	if (error) return <p>Error {error}</p>
	if (!obj) return null;

	return (
		<>
			<p>Title: {obj.title}</p>
			<p>Body: {obj.body}</p>
			<p>Id: {obj.id}</p>
		</>
	);
}

export default RequestPost;