import {useEffect, useState} from 'react'

function RequestDelete()
{
	const [success, setSuccess] = useState(false);
	const [loading, setLoading] = useState(true);
	const [error, setError] = useState(null);

	useEffect(() => {
		const controller = new AbortController();

		async function deleteFetch()
		{
			try {
				const respond = await fetch ("https://jsonplaceholder.typicode.com/posts/1", {
					method: "DELETE",
					signal: controller.signal
				});
				if (!respond.ok)
					throw new Error(respond.status);
				setSuccess(true);
			}catch (err)
			{
				if (err.name != "AbortError")
					setError(err.message);
			}finally {
				setLoading(false);
			}
		}

		deleteFetch();
		return () => controller.abort();
	}, []);

	if (loading) return <p>Loading...</p>;
	if (error) return <p>Error: {error}</p>;

	return <p>Request DELETE finished with success!</p>
}

export default RequestDelete;