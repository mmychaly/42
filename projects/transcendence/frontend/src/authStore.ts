import type { AuthUser } from "./authTypes.js";
import { pingSession } from "./authApi.js";

let currentUser: AuthUser | null = null;
let heartbeatTimer: ReturnType<typeof setInterval> | null = null;
const HEARTBEAT_INTERVAL_MS = 25_000;

export function getCurrentUser(): AuthUser | null {
  return currentUser;
}

export function setCurrentUser(user: AuthUser | null): void {
  currentUser = user;

  if (currentUser) {
    startHeartbeat();
  } else {
    stopHeartbeat();
  }
}

async function heartbeatTick(): Promise<void> {
  if (!currentUser) return;
  try {
    const result = await pingSession();
    if (result === "unauthorized") {
      setCurrentUser(null);
    }
  } catch (error) {
    console.error("Heartbeat failed", error);
  }
}

function startHeartbeat(): void {
  if (heartbeatTimer) return;

  heartbeatTimer = setInterval(() => {
    void heartbeatTick();
  }, HEARTBEAT_INTERVAL_MS);

  void heartbeatTick();
}

function stopHeartbeat(): void {
  if (heartbeatTimer) {
    clearInterval(heartbeatTimer);
    heartbeatTimer = null;
  }
}
