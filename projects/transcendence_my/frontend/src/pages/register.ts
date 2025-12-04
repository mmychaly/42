import type { NavigateFn } from "../routerTypes.js";
import { register } from "../authApi.js";
import { setCurrentUser } from "../authStore.js";

export const RegisterPage = () => `
  <section class="p-4 max-w-sm mx-auto">
    <h2 class="text-2xl font-bold mb-4">Create account</h2>
    <form id="register-form" class="space-y-3">
      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="reg-username">
          Username
        </label>
        <input
          id="reg-username"
          name="username"
          type="text"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
      </div>

      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="reg-email">
          Email
        </label>
        <input
          id="reg-email"
          name="email"
          type="email"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
      </div>

      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="reg-password">
          Password
        </label>
        <input
          id="reg-password"
          name="password"
          type="password"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
      </div>

      <p id="register-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>

      <button
        type="submit"
        class="w-full px-4 py-2 rounded bg-green-600 hover:bg-green-500 text-white font-medium"
      >
        Sign up
      </button>
    </form>

    <p class="mt-4 text-sm text-slate-400">
      Already have an account?
      <a href="/login" data-link class="text-blue-400 hover:text-blue-300">
        Log in
      </a>
    </p>
  </section>
`;

export function setupRegisterPage(navigate: NavigateFn): void {
  const form = document.getElementById("register-form") as HTMLFormElement | null;
  if (!form) return;

  const errorEl = document.getElementById("register-error");

  form.addEventListener("submit", async (event) => {
    event.preventDefault();

    if (errorEl) {
      errorEl.textContent = "";
    }

    const formData = new FormData(form);
    const username = String(formData.get("username") ?? "").trim();
    const email = String(formData.get("email") ?? "").trim();
    const password = String(formData.get("password") ?? "").trim();

    if (!username || !email || !password) {
      if (errorEl) {
        errorEl.textContent = "Watafak - Please fill all fields!";
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

      const user = await register(username, email, password);
      setCurrentUser(user);
      navigate("/");
    } catch (err) {
      if (errorEl) {
        errorEl.textContent =
          err instanceof Error ? err.message : "Could not register";
      }
    } finally {
      if (submitButton) {
        submitButton.disabled = false;
      }
    }
  });
}
