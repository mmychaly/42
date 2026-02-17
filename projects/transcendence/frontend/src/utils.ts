// User helpers
type UserTitles = {
  displayName: string | null;
  username: string;
};

export function getUserDisplayName(user: UserTitles): string {
  return user.displayName || user.username;
}

export function getUserInitial(user: UserTitles): string {
  const name = (user.displayName || user.username || "?").trim();
  return name[0]?.toUpperCase() || "?";
}

// HTTP helpers
type ErrorPayload = {
  message?: string;
  error?: string;
};

export async function readErrorMessage(
  res: Response,
  fallback: string,
  field: keyof ErrorPayload = "message",
): Promise<string> {
  try {
    const body = (await res.json()) as ErrorPayload;
    const value = body?.[field];
    if (typeof value === "string" && value.trim().length > 0) {
      return value;
    }
  } catch {
    // ignore parse errors
  }
  return fallback;
}

// Avatar helpers
type AvatarUser = {
  avatarUrl: string | null;
  displayName: string | null;
  username: string;
};

type AvatarOptions = {
  sizeClass?: string;
  textClass?: string;
  className?: string;
};

export function createAvatarElement(
  user: AvatarUser,
  options: AvatarOptions = {},
): HTMLDivElement {
  const avatar = document.createElement("div");
  avatar.className = [
    options.sizeClass ?? "w-10 h-10",
    "rounded-full overflow-hidden bg-slate-800 flex items-center justify-center font-semibold text-slate-100",
    options.textClass ?? "text-sm",
    options.className,
  ]
    .filter(Boolean)
    .join(" ");

  if (user.avatarUrl) {
    const img = document.createElement("img");
    img.src = user.avatarUrl;
    img.alt = user.username;
    img.className = "w-full h-full object-cover";
    avatar.appendChild(img);
  } else {
    avatar.textContent = getUserInitial(user);
  }

  return avatar;
}

export function updateAvatarImage(
  imgEl: HTMLImageElement | null,
  fallbackEl: HTMLElement | null,
  url: string | null,
  initial: string,
): void {
  if (!imgEl || !fallbackEl) return;

  fallbackEl.textContent = initial;

  if (url) {
    imgEl.src = url;
    imgEl.classList.remove("hidden");
    fallbackEl.classList.add("hidden");
    return;
  }

  imgEl.removeAttribute("src");
  imgEl.classList.add("hidden");
  fallbackEl.classList.remove("hidden");
}

// History format helpers
export function parseTimestamp(value: string | null): number {
  if (!value) return Number.NaN;
  const normalized = value.includes("T") ? value : value.replace(" ", "T");
  const parsed = new Date(normalized);
  return parsed.getTime();
}

export function formatDateTime(value: string | null): string {
  if (!value) return "-";
  const time = parseTimestamp(value);
  if (Number.isNaN(time)) return value;
  return new Date(time).toLocaleString(undefined, {
    year: "numeric",
    month: "2-digit",
    day: "2-digit",
    hour: "2-digit",
    minute: "2-digit",
  });
}

export function formatModeLabel(mode: string): string {
  if (!mode) return "-";
  const normalized = mode.trim();
  if (!normalized) return "-";
  const lowered = normalized.toLowerCase();
  const labelMap: Record<string, string> = {
    quick: "Quick",
    tournament: "Tournament",
    local: "Local",
    online: "Online",
  };
  if (labelMap[lowered]) return labelMap[lowered];
  const cleaned = normalized.replace(/_/g, " ");
  return cleaned.charAt(0).toUpperCase() + cleaned.slice(1);
}

export function formatMatchResult(
  value: string | null,
): { label: string; className: string } {
  if (!value) return { label: "-", className: "text-slate-400" };
  const lowered = value.toLowerCase();
  if (lowered === "win")
    return { label: "Win", className: "text-emerald-400" };
  if (lowered === "loss")
    return { label: "Loss", className: "text-orange-400" };
  return { label: value, className: "text-slate-400" };
}

// Game helpers
export function getGameWsUrl(): string {
  const protocol = window.location.protocol === "https:" ? "wss:" : "ws:";
  return `${protocol}//${window.location.host}/ws/game`;
}

export function getLocalWsUrl(): string {
  const protocol = window.location.protocol === "https:" ? "wss:" : "ws:";
  return `${protocol}//${window.location.host}/ws/game/local`;
}

export function getTournamentWsUrl(tournamentId: number | string): string {
  const protocol = window.location.protocol === "https:" ? "wss:" : "ws:";
  return `${protocol}//${window.location.host}/ws/tournament/${tournamentId}`;
}

export function getOrCreateGuestName(suffix: string = "guest"): string {
  const key = `gameGuestName:${suffix}`;
  const existing = sessionStorage.getItem(key);
  if (existing) return existing;
  const random = Math.random().toString(36).slice(2, 6).toUpperCase();
  const name = `Guest-${random}`;
  sessionStorage.setItem(key, name);
  return name;
}

export function mapInputKey(event: KeyboardEvent): "up" | "down" | null {
  if (event.key === "ArrowUp" || event.key === "w" || event.key === "W") {
    return "up";
  }
  if (event.key === "ArrowDown" || event.key === "s" || event.key === "S") {
    return "down";
  }
  return null;
}

export function mapLocalInput(
  event: KeyboardEvent,
  type: "keydown" | "keyup",
  ids: { p1: number | string | null; p2: number | string | null },
): {
  playerId: number | string;
  input: { key: "up" | "down"; type: "keydown" | "keyup" };
} | null {
  if (!ids.p1 || !ids.p2) return null;

  if (event.key === "w" || event.key === "W") {
    return { playerId: ids.p1, input: { key: "up", type } };
  }
  if (event.key === "s" || event.key === "S") {
    return { playerId: ids.p1, input: { key: "down", type } };
  }
  if (event.key === "ArrowUp") {
    return { playerId: ids.p2, input: { key: "up", type } };
  }
  if (event.key === "ArrowDown") {
    return { playerId: ids.p2, input: { key: "down", type } };
  }
  return null;
}
