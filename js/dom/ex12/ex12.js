"use strict";

const form_1 = document.forms[0];
const form_2 = document.forms.form_2;

form_1.addEventListener("submit", event => {
	console.log("Form 1")
	console.log(`Input text: ${form_1.elements.name} == ${form_1.elements.name.value}`);		console.logconsole.log(`Input checkbox: ${form_1.elements.input_2} == ${form_1.elements.input_2.checked}`);
});

form_2.addEventListener("submit", event => {
	console.log("Form 2")
	console.log(`Input text: ${form_1.elements.name} == ${form_1.elements.name.value}`);		console.logconsole.log(`Input checkbox: ${form_1.elements.input_2} == ${form_1.elements.input_2.checked}`);
});
