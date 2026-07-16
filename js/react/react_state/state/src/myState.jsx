import { useState } from 'react'
function Button({func})
{
  return (
    <button onClick={func}> +1 </button>
  )
}

function Counter()
{
	  const [counter, setCounter] = useState(0);
	
	  function handler()
	  {
		setCounter(counter + 1);
	  }
	
	  return (
		<>
		  <h1 style={{textAlign: 'center'}}>Use state</h1>
		  <Button func={handler}/> 
		  <p>Counter: {counter}</p>
		</>
	  )
}

export default Counter;