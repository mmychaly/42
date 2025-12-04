import type { NavigateFn } from "../routerTypes.js";
import { getCurrentUser } from "../authStore.js";

export const ProfilePage = () => `
  <section class="p-4 max-w-md mx-auto">
    <h2 class="text-2xl font-bold mb-4">Profile</h2>
    <div class="border border-slate-700 rounded p-4 mb-4">
      <p class="mb-1">
        <span class="font-semibold">Username:</span>
        <span id="profile-username">—</span>
      </p>
      <p class="mb-1">
        <span class="font-semibold">Display name:</span>
        <span id="profile-displayname">—</span>
      </p>
      <p class="mb-1">
        <span class="font-semibold">Status:</span>
        <span id="profile-status">Online</span>
      </p>
    </div>

    <div>
      <h3 class="font-semibold mb-2">Match history (stub)</h3>
      <ul class="space-y-1 text-sm text-slate-300">
        <li>2025-11-10 – vs Player_1 – Win 11:8</li>
        <li>2025-11-09 – vs Player_2 – Loss 7:11</li>
        <li>2025-11-08 – vs Player_3 – Win 11:3</li>
      </ul>
    </div>
  </section>
`;

export function setupProfilePage(navigate: NavigateFn): void {
  const user = getCurrentUser();

  if (!user) {
    // если не залогинен — отправляем на страницу логина
    navigate("/login");
    return;
  }

  const usernameEl = document.getElementById("profile-username");
  const displayNameEl = document.getElementById("profile-displayname");

  if (usernameEl) {
    usernameEl.textContent = user.username;
  }
  if (displayNameEl) {
    displayNameEl.textContent = user.displayName;
  }
}
