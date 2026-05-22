"use strict";

console.log("String");

let str = " Salut comment va tu ";
let newStr = "Mika";

console.log(str.toLocaleUpperCase());
console.log(str.toLocaleLowerCase());
console.log(str.slice(0,6));
console.log("Lenght", str.length);
console.log(str.substring(10));
console.log(str.indexOf("comment"));
console.log(str.includes("Salut"));
console.log(str.replace("va", "no"));
console.log(str.split(" "));
console.log(str.split(" ").join("/"));
console.log(str.trim());
console.log(str[1]);


//console.log();