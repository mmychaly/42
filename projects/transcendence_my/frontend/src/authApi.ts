import type { AuthUser } from "./authTypes.js";

function sleep(ms: number): Promise<void> {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

export async function login(login: string, password: string): Promise<AuthUser> {
  // ===== Бэк заглушка =====
  /*
  const res = await fetch("/api/auth/login", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ login, password }),
  });

  if (!res.ok) {
    let errorMessage = `Login failed with status ${res.status}`;

    try {
      const errorBody = await res.json();
      if (errorBody && typeof errorBody.message === "string") {
        errorMessage = errorBody.message;
      }
    } catch {
      // игнорим ошибку парсинга
    }

    throw new Error(errorMessage);
  }

  const data = await res.json();
  return data.user as AuthUser;
  */

  // ===== Бэк заглушка =====
  await sleep(400);

  if (!login || !password) {
    throw new Error("Login and password are required");
  }

  return {
    id: "mock-user-id",
    username: login,
    displayName: login,
  };
}

export async function register(
  username: string,
  email: string,
  password: string
): Promise<AuthUser> {
  // ===== Бэк заглушка =====
  /*
  const res = await fetch("/api/auth/register", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ username, email, password }),
  });

  if (!res.ok) {
    let errorMessage = `Register failed with status ${res.status}`;

    try {
      const errorBody = await res.json();
      if (errorBody && typeof errorBody.message === "string") {
        errorMessage = errorBody.message;
      }
    } catch {
      // ignore
    }

    throw new Error(errorMessage);
  }

  const data = await res.json();
  return data.user as AuthUser;
  */

  // ===== Бэк заглушка =====
  await sleep(400);

  if (!username || !email || !password) {
    throw new Error("Where the all inputs?!");
  }

  return {
    id: "mock-registered-id",
    username,
    displayName: username,
  };
}

export async function logout(): Promise<void> {
  // ===== Бэк заглушка =====
  /*
  const res = await fetch("/api/auth/logout", {
    method: "POST",
    credentials: "include",
  });

  if (!res.ok && res.status !== 401) {
    throw new Error(`Logout failed with status ${res.status}`);
  }
  */

  // ===== Бэк заглушка =====
  await sleep(200);
}

export async function fetchMe(): Promise<AuthUser | null> {
  // ===== Бэк заглушка =====
  /*
  const res = await fetch("/api/auth/me", {
    method: "GET",
    credentials: "include",
  });

  if (res.status === 401) {
    return null;
  }

  if (!res.ok) {
    throw new Error(`Failed to fetch current user: ${res.status}`);
  }

  const data = await res.json();
  return data.user as AuthUser;
  */

  // ===== Бэк заглушка =====
  await sleep(200);
  return null;
}
