export let counter = 0;

export function showElement(value) {
	for (let key in value)
	{
		counter++;
		console.log(key, value[key]);
	}
	return counter;
}