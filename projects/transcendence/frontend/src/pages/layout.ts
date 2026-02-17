import { getCurrentUser, setCurrentUser } from "../authStore.js";
import { logout as apiLogout } from "../authApi.js";
import type { NavigateFn } from "../routerTypes.js";
import {
  getUserDisplayName,
  getUserInitial,
  updateAvatarImage,
} from "../utils.js";

// Функция layout оборачивает переданный контент в общий для всех страниц и смотрит если залогинен - одна шапка, если нет - другая.
export function layout(content: string): string {
  const user = getCurrentUser();
  const currentPath = window.location.pathname;

  const isActiveTab = (path: string) =>
    currentPath === path ? "text-blue-300" : "hover:text-blue-300";

  const authPart = user
    ? `
      <div id="nav-user" class="ml-auto flex items-center gap-2 text-sm text-slate-300">
        <div class="w-7 h-7 rounded-full overflow-hidden bg-slate-700 flex items-center justify-center text-xs font-semibold text-slate-100">
          <img
            id="nav-avatar-img"
            alt="avatar"
            class="w-full h-full object-cover hidden"
          />
          <span id="nav-avatar-fallback">?</span>
        </div>
        <span id="nav-greeting">Hi, <span id="nav-displayname"></span></span>
      </div>
      <a href="/profile" data-link class="ml-4 ${isActiveTab("/profile")}">Profile</a>
      <a href="#" id="logout-link" class="ml-4 hover:text-blue-300">Logout</a>
    `
    : `
      <a href="/login" data-link class="ml-auto hover:text-blue-300">Login</a>
    `;

  // Турниры и история доступны только авторизованным.
  const authLinks = user
    ? `
        <a href="/tournament" data-link class="${isActiveTab("/tournament")}">Tournament</a>
        <a href="/history" data-link class="${isActiveTab("/history")}">History</a>
      `
    : "";

  return `
    <div class="min-h-screen bg-slate-900 text-slate-100">
      <nav class="flex gap-4 px-6 py-3 border-b border-slate-800 bg-slate-950">
        <a href="/" data-link class="${isActiveTab("/")}">Home</a>
        ${authLinks}
        <a href="/game" data-link class="${isActiveTab("/game")}">Game</a>
        <a href="/friends" data-link class="${isActiveTab("/friends")}">Friends</a>
        ${authPart}
      </nav>
      <main>
        ${content}
      </main>
    </div>
  `;
}

// чтобы после сохранений в профиле шапка обновлялась без перерендеринга
export function refreshNavUserUI(): void {
  const user = getCurrentUser();
  if (!user) return;

  const nameEl = document.getElementById("nav-displayname");
  const imgEl = document.getElementById(
    "nav-avatar-img",
  ) as HTMLImageElement | null;
  const fallbackEl = document.getElementById("nav-avatar-fallback");

  if (nameEl) {
    nameEl.textContent = getUserDisplayName(user);
  }

  updateAvatarImage(imgEl, fallbackEl, user.avatarUrl, getUserInitial(user));
}

export function setupNav(navigate: NavigateFn): void {
  refreshNavUserUI();
  const logoutLink = document.getElementById(
    "logout-link",
  ) as HTMLAnchorElement | null;

  if (!logoutLink) return;

  logoutLink.addEventListener("click", async (event) => {
    event.preventDefault();

    try {
      await apiLogout();
    } catch (error) {
      console.error("Logout failed", error);
    } finally {
      setCurrentUser(null);
      navigate("/login");
    }
  });
}
