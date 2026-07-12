function User({name, age, allowed}) //use destructuration
{
	return (<>
		<h2 style={{marginTop: '30px', textAlign: 'center'}}>User</h2>
		<p>Name: {name}</p>
		<p>Age: {age}</p>
		{allowed && <p>Permit : true</p>}
	</>)
}

function SayHello(props) //Use simple acces
{	
	return (
		<>
			<h1 style={{marginTop: '10px', textAlign: 'center'}}>Use props</h1>
			<p>{props.text}</p>
		</>
	)

}

// function DisplayData(props){

// }

function MyProps(){
	
	// otherData = {
	// 	city: "paris",
	// 	Student: "42"
	// }

	return (
		<>
			<SayHello text="Hi from composent React"/>
			<User name="Mika" age={34} allowed={true} />
		</>
	)

}

export default MyProps;

//		<DisplayData data={otherData} />