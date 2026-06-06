"use strict";

let body = document.body;
//console.dir(body);


console.log("\nTest hasAttribute, getAttribute, setAttribute, removeAttribute")
let test1 = document.querySelector("#test1");
console.log(test1.getAttribute("data-mdmdm"));

for (let key of test1.attributes)
	console.log(key);
console.log("Use dataet in loop");
console.log(test1.dataset);
for (let obj of Object.keys(test1.dataset))
	console.log(obj, test1.dataset[obj]);
 test1.mdmdm = "rrrrrr";
 console.log(test1.dataset.mdmdm);
 console.log(test1.mdmdm);
// console.log(test1.getAttribute("data-mdmdm"));
console.log(test1.hasAttribute("data-mdmdm"));
test1.setAttribute("data-mdmdm", "New value");
console.log(test1.getAttribute("data-mdmdm"));
console.log(test1.dataset.mdmdm);
console.log(test1.mdmdm);
console.log("befor use dataset for assigne a value");
test1.dataset.mdmdm = "Hoppa";
console.log(test1.getAttribute("data-mdmdm"));
test1.removeAttribute("data-mdmdm");
console.log(test1.hasAttribute("data-mdmdm"));

for (let val of test1.attributes)
	console.log(val);