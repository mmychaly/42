"use strict"

console.log(navigator.userAgent);
console.log(navigator.language);
console.log(navigator.languages);
console.log(navigator.onLine);

navigator.geolocation.getCurrentPosition(position => {
    console.log(position.coords.latitude);
    console.log(position.coords.longitude);
	console.log("accurance", position.coords.accuracy);
});

console.log(navigator.cookieEnabled);