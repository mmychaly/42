"use strict";

window.addEventListener("resize", () => console.log(window.innerWidth, window.innerHeight));
window.addEventListener("scroll", () => console.log(window.scrollY));

window.addEventListener("online", () => console.log("Connected"));
window.addEventListener("offline", () => console.log("Disconected"));