import { getCurrentUser, setCurrentUser } from "../authStore.js";
import { logout as apiLogout } from "../authApi.js";
import type { NavigateFn } from "../routerTypes.js";

// Функция layout оборачивает переданный контент в общий для всех страниц и смотрит если залогинен - одна шапка, если нет - другая. 
export function layout(content: string): string {
  const user = getCurrentUser();

  const authPart = user
    ? `
      <span class="ml-auto text-sm text-slate-300">
        Hi, ${user.displayName}
      </span>
      <a href="/profile" data-link class="ml-4 hover:text-blue-300">Profile</a>
      <a href="#" id="logout-link" class="ml-4 hover:text-blue-300">Logout</a>
    `
    : `
      <a href="/login" data-link class="ml-auto hover:text-blue-300">Login</a>
    `;

  return `
    <div class="min-h-screen bg-slate-900 text-slate-100">
      <nav class="flex gap-4 px-6 py-3 border-b border-slate-800 bg-slate-950">
        <a href="/" data-link class="text-blue-400 hover:text-blue-300">Home</a>
        <a href="/tournament" data-link class="hover:text-blue-300">Tournament</a>
        <a href="/game" data-link class="hover:text-blue-300">Game</a>
        ${authPart}
      </nav>
      <main>
        ${content}
      </main>
    </div>
  `;
}

export function setupNav(navigate: NavigateFn): void {
  const logoutLink = document.getElementById("logout-link") as
    | HTMLAnchorElement
    | null;

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
