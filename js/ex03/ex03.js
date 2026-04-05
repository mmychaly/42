"use strict"
//Initialisation de variables et const avec differents types
let num = 5;
let str = "Salut";
let double = 0.5;
let bool = true;
let und;
let obj = { name: "mika", 
			str: "Hello Word!",
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

str = `Combinaison de strings , ${constStr}`;
console.log(str);
console.log(str.length);
console.log(obj.name.length);
console.log(obj.name.toUpperCase());
console.log(obj.helloWord());


