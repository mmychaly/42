"use strict"

//Initialisation de variables et const avec differents types
let num = 5;
let str = "Salut";
let double = 0.5;
let bool = true;
let und;
let obj = { name: "mika", 
			str: "Hello Word! ",
			num: 34,
			helloWord() {
				console.log("Hello Word!");
			}//Pas de parenthèses  en derniere element
		};

const constStr = "Mika";

var varObj = obj;

console.log("Let: ", und, num, str, bool, double, obj);
console.log("Const: ", constStr);
console.log("Var: ", varObj.name, varObj.str);

console.log("for of")
for (let char of obj.str)
	console.log(char);




//Display on the page  + work with string methods
let docObj1 = document.getElementById("test1");
let docObj2 = document.getElementById("test2");
let docObj3 = document.getElementById("test3");
let docObj4 = document.getElementById("test4");
let docObj5 = document.getElementById("test5");
let docObj6 = document.getElementById("test6");
let docObj7 = document.getElementById("test7");
let docObj8 = document.getElementById("test8");
let docObj9 = document.getElementById("test9");

obj.helloWord();
docObj1.textContent = obj.name;
docObj2.textContent = obj.num;
docObj3.textContent = obj.str;
docObj4.textContent = obj.str + constStr;

//string methods
console.log("\nTest string methods")
console.log("lenght: ", obj.str.length);
console.log("indexOf: ", obj.str.indexOf("Word"));
console.log("slice: ", obj.str.slice(0, 6));
console.log("substring: ", obj.str.substring(6, 10));
console.log("includes: ", obj.str.includes("!")); //": ", 
console.log("toLocaleLowerCase: ", obj.str.toLocaleLowerCase());
console.log("toLocaleUpperCase: ", obj.str.toLocaleUpperCase());
console.log("trim: ", obj.str.trim(), obj.str.trim().length); //Delete the space in ending
console.log("split: ", obj.str.split(" "));//split:  Array(3) [ "Hello", "Word!", "" ]
console.log("split[1]: ", obj.str.split(" ")[1]);//split[1]:  Word!
let split = obj.str.split(" ");
console.log("join: ", split.join(" "));



