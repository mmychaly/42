import type { NavigateFn } from "../routerTypes.js";
import { login, verifyTwofaLogin } from "../authApi.js";
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

    <form id="login-2fa-form" class="space-y-3 hidden">
      <div class="flex flex-col gap-1">
        <label class="text-sm text-slate-300" for="twofa-code-input">
          2FA code from app
        </label>
        <input
          id="twofa-code-input"
          name="code"
          type="text"
          inputmode="numeric"
          autocomplete="one-time-code"
          class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100 tracking-[0.3em]"
        />
      </div>

      <p id="twofa-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>

      <button
        type="submit"
        class="w-full px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white font-medium"
      >
        Confirm 2FA
      </button>

      <button
        id="twofa-back-btn"
        type="button"
        class="w-full px-4 py-2 rounded bg-slate-800 hover:bg-slate-700 text-sm"
      >
        Use another account
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
  const twofaForm = document.getElementById(
    "login-2fa-form",
  ) as HTMLFormElement | null;
  if (!form) return;

  const errorEl = document.getElementById("login-error");
  const twofaErrorEl = document.getElementById("twofa-error");
  const twofaBackBtn = document.getElementById(
    "twofa-back-btn",
  ) as HTMLButtonElement | null;
  const twofaCodeInput = document.getElementById(
    "twofa-code-input",
  ) as HTMLInputElement | null;

  let pendingTwofaToken: string | null = null;

  const setTwofaMode = (enabled: boolean) => {
    form.classList.toggle("hidden", enabled);
    if (twofaForm) {
      twofaForm.classList.toggle("hidden", !enabled);
    }
    if (!enabled) {
      pendingTwofaToken = null;
      if (twofaCodeInput) twofaCodeInput.value = "";
      if (twofaErrorEl) twofaErrorEl.textContent = "";
    }
  };

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
      'button[type="submit"]',
    ) as HTMLButtonElement | null;

    try {
      if (submitButton) {
        submitButton.disabled = true;
      }

      const result = await login(loginValue, passwordValue);
      if (result.type === "2fa" && result.tempToken) {
        pendingTwofaToken = result.tempToken;
        setTwofaMode(true);
        if (twofaCodeInput) {
          twofaCodeInput.focus();
        }
        return;
      }
      if (result.type === "user") {
        setCurrentUser(result.user);
        navigate("/");
      }
    } catch (err) {
      if (errorEl) {
        errorEl.textContent =
          err instanceof Error ? err.message : "Unable to sign in";
      }
    } finally {
      if (submitButton) {
        submitButton.disabled = false;
      }
    }
  });

  if (twofaBackBtn) {
    twofaBackBtn.addEventListener("click", () => {
      setTwofaMode(false);
    });
  }

  if (twofaForm) {
    twofaForm.addEventListener("submit", async (event) => {
      event.preventDefault();
      if (twofaErrorEl) twofaErrorEl.textContent = "";

      const codeValue = String(twofaCodeInput?.value ?? "").trim();
      if (!codeValue) {
        if (twofaErrorEl) twofaErrorEl.textContent = "Enter the code";
        return;
      }

      const submitButton = twofaForm.querySelector(
        'button[type="submit"]',
      ) as HTMLButtonElement | null;

      try {
        if (!pendingTwofaToken) {
          throw new Error("2FA token missing. Try login again.");
        }
        if (submitButton) submitButton.disabled = true;

        const user = await verifyTwofaLogin(pendingTwofaToken, codeValue);
        setCurrentUser(user);
        navigate("/");
      } catch (err) {
        if (twofaErrorEl) {
          twofaErrorEl.textContent =
            err instanceof Error ? err.message : "Unable to verify 2FA";
        }
      } finally {
        if (submitButton) submitButton.disabled = false;
      }
    });
  }
}
