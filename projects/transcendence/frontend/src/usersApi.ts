import type { AuthUser } from "./authTypes.js";
import { readErrorMessage } from "./utils.js";

export type UserMatchScore = {
  me: number;
  opponent: number;
};

export type UserMatch = {
  id: number;
  mode: string;
  opponentName: string | null;
  startedAt: string | null;
  result: string | null;
  score?: UserMatchScore;
};

export type UserStats = {
  totalWins: number;
  totalLosses: number;
  winRate: number;
  lastMatches: UserMatch[];
};

export type MeProfile = {
  user: AuthUser;
  stats: UserStats;
};

export type PatchMePayload = {
  displayName?: string;
  statusMessage?: string;
};

type UserMatchPayload = UserMatch;
type MeProfileResponse = MeProfile;

type UserMatchesResponse = {
  matches: UserMatchPayload[];
};

type MeResponse = {
  user: AuthUser;
};

type UploadAvatarResponse = {
  avatarUrl: string;
};

export async function getMeProfile(): Promise<MeProfile> {
  const res = await fetch("/api/users/me", {
    method: "GET",
    credentials: "include",
  });

  if (!res.ok) {
    const msg = await readErrorMessage(
      res,
      `GET /api/users/me failed: ${res.status}`,
      "message",
    );
    throw new Error(msg);
  }

  const data = (await res.json()) as MeProfileResponse;
  return data;
}

export async function getUserMatches(): Promise<UserMatch[]> {
  const res = await fetch("/api/users/me/matches", {
    method: "GET",
    credentials: "include",
  });

  if (!res.ok) {
    const msg = await readErrorMessage(
      res,
      `GET /api/users/me/matches failed: ${res.status}`,
      "message",
    );
    throw new Error(msg);
  }

  const data = (await res.json()) as UserMatchesResponse;
  return data.matches;
}

export async function getMe(): Promise<AuthUser> {
  const res = await fetch("/api/users/me", {
    method: "GET",
    credentials: "include",
  });

  if (!res.ok) {
    const msg = await readErrorMessage(
      res,
      `GET /api/users/me failed: ${res.status}`,
      "message",
    );
    throw new Error(msg);
  }

  const data = (await res.json()) as MeResponse;
  return data.user;
}

export async function patchMe(patch: PatchMePayload): Promise<AuthUser> {
  const res = await fetch("/api/users/me", {
    method: "PATCH",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify(patch),
  });

  if (!res.ok) {
    const msg = await readErrorMessage(
      res,
      `PATCH /api/users/me failed: ${res.status}`,
      "message",
    );
    throw new Error(msg);
  }

  const data = (await res.json()) as MeResponse;
  return data.user;
}

export async function uploadMyAvatar(file: File): Promise<string> {
  const form = new FormData();
  form.append("avatar", file);

  const res = await fetch("/api/users/me/avatar", {
    method: "POST",
    credentials: "include",
    body: form,
  });

  if (!res.ok) {
    const msg = await readErrorMessage(
      res,
      `POST /api/users/me/avatar failed: ${res.status}`,
      "message",
    );
    throw new Error(msg);
  }

  const data = (await res.json()) as UploadAvatarResponse;
  return data.avatarUrl;
}
