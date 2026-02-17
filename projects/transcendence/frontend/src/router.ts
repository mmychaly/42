import { layout, setupNav } from "./pages/layout.js";
import type { Route } from "./routerTypes.js";

import { HomePage, setupHomePage } from "./pages/home.js";
import { TournamentPage, setupTournamentPage } from "./pages/tournament.js";
import { GamePage, setupGamePage } from "./pages/game.js";
import { LoginPage, setupLoginPage } from "./pages/login.js";
import { ProfilePage, setupProfilePage } from "./pages/profile.js";
import { RegisterPage, setupRegisterPage } from "./pages/register.js";
import { FriendsPage, setupFriendsPage } from "./pages/friends.js";
import { HistoryPage, setupHistoryPage } from "./pages/history.js";

const routes: Route[] = [
	{ path: "/", render: HomePage, setup: setupHomePage },
	{ path: "/tournament", render: TournamentPage, setup: setupTournamentPage },
	{ path: "/game", render: GamePage, setup: setupGamePage },
	{ path: "/game/room/:id", render: GamePage, setup: setupGamePage },
	{ path: "/history", render: HistoryPage, setup: setupHistoryPage },
	{ path: "/login", render: LoginPage, setup: setupLoginPage },
	{ path: "/register", render: RegisterPage, setup: setupRegisterPage },
	{ path: "/profile", render: ProfilePage, setup: setupProfilePage },
	{ path: "/friends", render: FriendsPage, setup: setupFriendsPage }
];

function match(pathname: string): Route {
	// Removes '/' at the end of url
	const normalized = pathname.length > 1 && pathname.endsWith("/")
		? pathname.slice(0, -1) : pathname;

	const found = routes.find((r) => {
		// Exact Match (ex "/login", "/game")
		if (r.path === normalized) {
			return true;
		}

		// Dynamic Match (ex "/game/room/:id")
		if (r.path.includes("/:id")) {
			const base = r.path.replace(":id", "");

			// Check if the current URL starts with that base
			// and if there is actually something after it (the ID)
			if (normalized.startsWith(base) && normalized.length > base.length) {
				return true;
			}
		}
		return false;
	});

	// Return the found route or homepage if nothing matches
	return found || routes[0];
}

export function navigate(path: string): void {
	if (location.pathname === path) return;
	history.pushState({}, "", path);
	render();
}

let cleanupRoute: (() => void) | null = null;

export function render(): void {
	const root = document.getElementById("app");
	if (!root) return;

	cleanupRoute?.();
	cleanupRoute = null;

	const route = match(location.pathname);
	root.innerHTML = layout(route.render());

	setupNav(navigate);
	const cleanup = route.setup?.(navigate);
	if (typeof cleanup === "function") {
		cleanupRoute = cleanup;
	}
}

export function bootRouter(): void {
	document.addEventListener("click", (event) => {
		const target = event.target as HTMLElement;
		const link = target.closest("a[data-link]") as HTMLAnchorElement | null;

		if (link) {
			const href = link.getAttribute("href");
			if (href && href.startsWith("/")) {
				event.preventDefault();
				navigate(href);
			}
		}
	});

	window.addEventListener("popstate", () => {
		render();
	});

	render();
}
