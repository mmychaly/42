"use strict";

window.addEventListener("resize", () => console.log("Sise of window: ", window.innerWidth, window.innerHeight));
window.addEventListener("scroll", () => console.log("Scroll position: ", window.scrollY));

window.addEventListener("online", () => console.log("Connected"));
window.addEventListener("offline", () => console.log("Disconected"));

console.log("location: ", location);
console.log("navigation: ", navigator);
console.log("history: ", history);
console.log("screen: ", screen);
console.log("document: ", document);
console.log("localStorage: ", localStorage);
console.log("sessionStorage: ", sessionStorage);

