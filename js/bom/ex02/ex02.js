"use strict";

const nav_item = document.querySelector("nav");
const content = document.querySelector("#content");

function renderHome(){
	console.log("renderHome launch");
	content.innerHTML = "<h2>Page Accueil</h2>";
}

function renderUsers(){
	console.log("renderUsers launch");
	content.innerHTML = "<h2>Page Users</h2><p>Liste des utilisateurs</p>";
}

function renderProfile(){
	console.log("renderProfile launch");
	content.innerHTML = "<h2>Page Profile</h2><p>Mon profil</p>";
}

function renderPage(url){
	console.log("location.pathname in renderPage: ", location.pathname, "url: ", url);
	if (url === "/")
		renderHome();
	if (url === "/users")
		renderUsers();
	if (url === "/profile")
		renderProfile();
}

nav_item.addEventListener("click", (e) => {
	console.log("location.pathname in nav_item: ", location.pathname, ".e.target.id: ", e.target.id);
	let url = "";
	if (e.target.id === "btn_1")
		url = "/";
	if (e.target.id === "btn_2")
		url = "/users";
	if (e.target.id === "btn_3")
		url = "/profile";

	history.pushState({url}, "", url);
	renderPage(url);
});

window.addEventListener("popstate", (e) => {
	console.log("popstate déclenché");
    console.log("e.state:", e.state);
    console.log("history.state:", history.state);
    console.log("history.length:", history.length);
	renderPage(location.pathname);
});

history.replaceState({url: "/"}, "", "/");
renderPage(location.pathname);
console.log("location.pathname initial", location.pathname);

setTimeout(() => history.back(), 5000);
setTimeout(() => history.forward(), 7000);