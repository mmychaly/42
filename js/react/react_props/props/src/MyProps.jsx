function User({name, age, allowed}) //use destructuration
{
	return (<>
		<h2 style={{marginTop: '30px', textAlign: 'center'}}>User</h2>
		<p>Name: {name}</p>
		<p>Age: {age}</p>
		{allowed && <p>Permit : true</p>}
	</>)
}

function SayHello({text, children}) //Use simple acces
{	
	return (
		<>
			<h1 style={{marginTop: '10px', textAlign: 'center'}}>Use props</h1>
			<p>{text}</p>
			<p>{children}</p>
		</>
	)

}

 function DisplayData(props){
	
	return (
		<>
			<h2 style={{marginTop: '30px', textAlign: 'center'}}>Other data</h2>
			<p>{props.data.city}</p>
			<p>{props.data.Student}</p>
			<p>{props.other[0]}</p>
		</>
	)

 }

function MyProps(){
	
	const otherData = {
		city: "Paris",
		Student: "School 42"
	};
	const arrWork = ["SSIAP", "ADS"];

	return (
		<>
			<SayHello text="Hi from composent React">"Use text from children"</SayHello>
			<User name="Mika" age={34} allowed={true} />
			<DisplayData data={otherData} other = {arrWork} />
		</>
	)

}

export default MyProps;

