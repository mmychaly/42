import { layout, setupNav } from "./pages/layout.js";
import type { Route } from "./routerTypes.js";

import { HomePage } from "./pages/home.js";
import { TournamentPage } from "./pages/tournament.js";
import { GamePage } from "./pages/game.js";
import { LoginPage, setupLoginPage } from "./pages/login.js";
import { ProfilePage, setupProfilePage } from "./pages/profile.js";
import { RegisterPage, setupRegisterPage } from "./pages/register.js";

const routes: Route[] = [
  { path: "/", render: HomePage },
  { path: "/tournament", render: TournamentPage },
  { path: "/game", render: GamePage },
  { path: "/login", render: LoginPage, setup: setupLoginPage },
  { path: "/register", render: RegisterPage, setup: setupRegisterPage },
  { path: "/profile", render: ProfilePage, setup: setupProfilePage },
];

function match(pathname: string): Route {
  return routes.find((r) => r.path === pathname) || routes[0];
}

export function navigate(path: string): void {
  if (location.pathname === path) return;
  history.pushState({}, "", path);
  render();
}

export function render(): void {
  const root = document.getElementById("app");
  if (!root) return;

  const route = match(location.pathname);
  root.innerHTML = layout(route.render());

  setupNav(navigate);
  route.setup?.(navigate);
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
