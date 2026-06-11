"use strict";

console.log('Use metrique for html page');
console.log("ClientWidth: ", document.documentElement.clientWidth);
console.log("ClientHeight: ", document.documentElement.clientHeight);

console.log("InnerWidth: ", window.innerWidth);
console.log("InnerHeight: ", window.innerHeight);

console.log("ScrollHeight: ", document.documentElement.scrollHeight);
console.log("ScrollTop: ", document.documentElement.scrollTop);

console.log("PageXOffset: ", window.pageXOffset);
console.log("PageYOffset: ", window.pageYOffset);

console.log("Use scrollBy and scrollTo");
let scroll1 = setInterval(() => {
	window.scrollBy(0, 100);
	if (window.pageYOffset + document.documentElement.clientHeight >= document.documentElement.scrollHeight)
	{
		setTimeout(() => window.scrollTo(0, 0));
		clearInterval(scroll1);
	}		
}, 200);