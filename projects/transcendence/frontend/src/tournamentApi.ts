import { TournamentState } from "./tournamentTypes.js";
import { readErrorMessage } from "./utils.js";

type TournamentResponse = { tournament: TournamentState };

export async function getTournament(): Promise<TournamentState> {
  const res = await fetch("/api/tournament", {
    method: "GET",
    credentials: "include", // чтобы отправлялась кука сессии
  });

  if (!res.ok) {
    throw new Error(`Failed to load tournament: ${res.status}`);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}

export async function resetTournament(): Promise<TournamentState> {
  const res = await fetch("/api/tournament/reset", {
    method: "POST",
    credentials: "include",
  });

  if (!res.ok) {
    throw new Error(`Failed to reset tournament: ${res.status}`);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}

// Добавляем участника: либо реального юзера (userId), либо гостя (alias).
export async function addParticipant(payload: {
  alias: string;
  userId?: number;
  isGuest?: boolean;
}): Promise<TournamentState> {
  const res = await fetch("/api/tournament/participants", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    credentials: "include",
    body: JSON.stringify({
      alias: payload.alias,
      userId: payload.userId,
    }),
  });

  if (!res.ok) {
    const message = await readErrorMessage(
      res,
      `Failed to add participant: ${res.status}`,
      "error",
    );
    throw new Error(message);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}

export async function startTournament(): Promise<TournamentState> {
  const res = await fetch("/api/tournament/start", {
    method: "POST",
    credentials: "include",
  });

  if (!res.ok) {
    const message = await readErrorMessage(
      res,
      `Failed to start tournament: ${res.status}`,
      "error",
    );
    throw new Error(message);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}

export async function prepareTournament(): Promise<TournamentState> {
  const res = await fetch("/api/tournament/prepare", {
    method: "POST",
    credentials: "include",
  });

  if (!res.ok) {
    const message = await readErrorMessage(
      res,
      `Failed to start tournament: ${res.status}`,
      "error",
    );
    throw new Error(message);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}

export async function finishTournamentMatch(
  matchId: string,
  winner: "p1" | "p2",
): Promise<TournamentState> {
  // В реальности матч завершается через сервис матчей,
  // а потом мы уже дергаем свежий турнир.
  const res = await fetch(
    `/api/matches/${encodeURIComponent(matchId)}/finish`,
    {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({ winner, type: "tournament" }),
    },
  );

  if (!res.ok) {
    const message = await readErrorMessage(
      res,
      `Failed to finish match: ${res.status}`,
      "error",
    );
    throw new Error(message);
  }

  const data = (await res.json()) as TournamentResponse;
  return data.tournament;
}
