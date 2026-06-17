"use strict";

const form_1 = document.forms[0];
const form_2 = document.forms.secondForm;

form_1.addEventListener("submit", event => {
	event.preventDefault();
	console.log("Form 1")
	console.log(`Input text: ${form_1.elements.name.name} == ${form_1.elements.name.value}`);		
	console.log(`Input checkbox: ${form_1.elements.input_2.id} == ${form_1.elements.input_2.checked}`);
});

form_2.addEventListener("submit", event => {
	event.preventDefault();
	console.log("Form 2")
	console.log(`Input text: ${form_2.elements.email.name} == ${form_2.elements[0].value}`);		
	console.log(`Input checkbox: ${form_2.elements.input_4.id} == ${form_2.elements["input_4"].checked}`);
});
