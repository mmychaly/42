import type { AuthUser } from "./authTypes.js";
import { readErrorMessage } from "./utils.js";

type AuthUserResponse = { user: AuthUser };
type LoginResponse =
  | { requires2fa: true; tempToken: string }
  | AuthUserResponse;
type TwofaSetupResponse = { otpauthUrl: string; manualEntryKey: string };
type TwofaStatusResponse = { enabled: boolean };

function sleep(ms: number): Promise<void> {
  return new Promise((resolve) => setTimeout(resolve, ms));
}

export type LoginResult =
  | { type: "user"; user: AuthUser }
  | { type: "2fa"; tempToken: string };

export async function login(
  login: string,
  password: string,
): Promise<LoginResult> {
  const res = await fetch("/api/auth/login", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ login, password }),
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `Login failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as LoginResponse;
  if ("requires2fa" in data) {
    return { type: "2fa", tempToken: data.tempToken };
  }
  return { type: "user", user: data.user };
}

export async function register(
  username: string,
  email: string,
  password: string,
): Promise<AuthUser> {
  const res = await fetch("/api/auth/register", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ username, email, password }),
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `Register failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as AuthUserResponse;
  return data.user;
}

export async function logout(): Promise<void> {
  // ===== Бэк заглушка =====
  const res = await fetch("/api/auth/logout", {
    method: "POST",
    credentials: "include",
  });

  if (!res.ok && res.status !== 401) {
    throw new Error(`Logout failed with status ${res.status}`);
  }
}

export async function verifyTwofaLogin(
  tempToken: string,
  code: string,
): Promise<AuthUser> {
  const res = await fetch("/api/auth/2fa", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ tempToken, code }),
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `2FA login failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as AuthUserResponse;
  return data.user;
}

export async function setupTwofa(): Promise<{
  otpauthUrl: string;
  manualEntryKey: string;
}> {
  const res = await fetch("/api/2fa/setup", {
    method: "GET",
    credentials: "include",
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `2FA setup failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as TwofaSetupResponse;
  return data;
}

export async function verifyTwofaSetup(code: string): Promise<boolean> {
  const res = await fetch("/api/2fa/verify", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ code }),
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `2FA verification failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as TwofaStatusResponse;
  return data.enabled;
}

export async function disableTwofa(code: string): Promise<boolean> {
  const res = await fetch("/api/2fa/disable", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({ code }),
  });

  if (!res.ok) {
    const errorMessage = await readErrorMessage(
      res,
      `2FA disable failed with status ${res.status}`,
      "message",
    );
    throw new Error(errorMessage);
  }

  const data = (await res.json()) as TwofaStatusResponse;
  return data.enabled;
}

export async function fetchMe(): Promise<AuthUser | null> {
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

  const data = (await res.json()) as AuthUserResponse;
  return data.user;
}

export async function pingSession(): Promise<"ok" | "unauthorized"> {
  const res = await fetch("/api/presence/ping", {
    method: "POST",
    credentials: "include",
  });

  if (res.status === 401) {
    return "unauthorized";
  }

  if (!res.ok) {
    throw new Error(`Presence ping failed: ${res.status}`);
  }

  return "ok";
}
