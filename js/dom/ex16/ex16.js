"use strict";

const test = document.querySelector("#test3");
const pImg = document.querySelector("#pImg");

test.addEventListener("click", e => {
	console.log("click déclenché !");
	let imgTest = new Image();

    imgTest.addEventListener("load", () => {
        console.log("Image chargée");
    });

    imgTest.addEventListener("error", () => {
        console.log("Image non trouvée");
        console.log(imgTest.src); 
    });
	imgTest.src = "astonavt.jpg";
	imgTest.width = 200;
	imgTest.height = 200;
	test.before(imgTest);
});

//	pImg.append(imgTest);
