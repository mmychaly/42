import type { NavigateFn } from "../routerTypes.js";
import { login } from "../authApi.js";
import { setCurrentUser } from "../authStore.js";

export const LoginPage = () => `
  <section class="p-4 max-w-sm mx-auto">
    <h2 class="text-2xl font-bold mb-4">Login</h2>
    <form id="login-form" class="space-y-3">
      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="login-input">
          Username or email
        </label>
        <input
          id="login-input"
          name="login"
          type="text"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
      </div>
      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="password-input">
          Password
        </label>
        <input
          id="password-input"
          name="password"
          type="password"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
      </div>

      <p id="login-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>

      <button
        type="submit"
        class="w-full px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white font-medium"
      >
        Log in
      </button>
    </form>

    <p class="mt-4 text-sm text-slate-400">
      Really?! Don’t have an account?
      <a href="/register" data-link class="text-blue-400 hover:text-blue-300">
        Sign up
      </a>
    </p>
  </section>
`;

export function setupLoginPage(navigate: NavigateFn): void {
  const form = document.getElementById("login-form") as HTMLFormElement | null;
  if (!form) return;

  const errorEl = document.getElementById("login-error");

  form.addEventListener("submit", async (event) => {
    event.preventDefault();

    if (errorEl) {
      errorEl.textContent = "";
    }

    const formData = new FormData(form);
    const loginValue = String(formData.get("login") ?? "").trim();
    const passwordValue = String(formData.get("password") ?? "").trim();

    if (!loginValue || !passwordValue) {
      if (errorEl) {
        errorEl.textContent = "Forget something?";
      }
      return;
    }

    const submitButton = form.querySelector(
      'button[type="submit"]'
    ) as HTMLButtonElement | null;

    try {
      if (submitButton) {
        submitButton.disabled = true;
      }

      const user = await login(loginValue, passwordValue);
      setCurrentUser(user);
      navigate("/");
    } catch (err) {
      if (errorEl) {
        errorEl.textContent =
          err instanceof Error ? err.message : "Не удалось войти";
      }
    } finally {
      if (submitButton) {
        submitButton.disabled = false;
      }
    }
  });
}
