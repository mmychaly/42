export type TournamentJoinInfo = {
  tournamentId: string;
  matchId: string;
  participantId: string;
  alias: string;
  isGuest: boolean;
  p1: {
    id: string;
    alias: string;
    isGuest: boolean;
  };
  p2: {
    id: string;
    alias: string;
    isGuest: boolean;
  };
  localControl?: boolean;
};

const JOIN_STORAGE_KEY = "tournamentJoin";
const GUEST_STORAGE_PREFIX = "tournamentGuests:";
const FINISHED_STORAGE_KEY = "tournamentFinished";
const SNAPSHOT_STORAGE_KEY = "tournamentSnapshot";
// Показываем "finished" только сразу после возврата из матча, а не после F5.
let allowFinishedDisplay = false;

function readGuestIds(tournamentId: string): string[] {
  const raw = sessionStorage.getItem(`${GUEST_STORAGE_PREFIX}${tournamentId}`);
  if (!raw) return [];
  try {
    const list = JSON.parse(raw);
    return Array.isArray(list) ? list.map(String) : [];
  } catch {
    return [];
  }
}

function writeGuestIds(tournamentId: string, ids: string[]): void {
  sessionStorage.setItem(
    `${GUEST_STORAGE_PREFIX}${tournamentId}`,
    JSON.stringify(ids),
  );
}

export function rememberTournamentGuest(
  tournamentId: string,
  participantId: string,
): void {
  const ids = new Set(readGuestIds(tournamentId));
  ids.add(String(participantId));
  writeGuestIds(tournamentId, Array.from(ids));
}

export function isTournamentGuestOnThisDevice(
  tournamentId: string,
  participantId: string,
): boolean {
  return readGuestIds(tournamentId).indexOf(String(participantId)) !== -1;
}

export function resetTournamentGuests(tournamentId: string): void {
  sessionStorage.removeItem(`${GUEST_STORAGE_PREFIX}${tournamentId}`);
}

export function setTournamentJoin(info: TournamentJoinInfo): void {
  // JoinInfo нужен странице матча, чтобы открыть правильный WS и матч.
  sessionStorage.setItem(JOIN_STORAGE_KEY, JSON.stringify(info));
}

export function getTournamentJoin(): TournamentJoinInfo | null {
  const raw = sessionStorage.getItem(JOIN_STORAGE_KEY);
  if (!raw) return null;
  try {
    return JSON.parse(raw) as TournamentJoinInfo;
  } catch {
    return null;
  }
}

export function clearTournamentJoin(): void {
  sessionStorage.removeItem(JOIN_STORAGE_KEY);
}

export function setTournamentSnapshot<T>(state: T): void {
  sessionStorage.setItem(SNAPSHOT_STORAGE_KEY, JSON.stringify(state));
}

export function getTournamentSnapshot<T>(): T | null {
  const raw = sessionStorage.getItem(SNAPSHOT_STORAGE_KEY);
  if (!raw) return null;
  try {
    return JSON.parse(raw) as T;
  } catch {
    return null;
  }
}

export function clearTournamentSnapshot(): void {
  sessionStorage.removeItem(SNAPSHOT_STORAGE_KEY);
}

export function setFinishedTournament<T>(state: T): void {
  // Разрешаем однократный показ результатов после выхода из матча.
  sessionStorage.setItem(FINISHED_STORAGE_KEY, JSON.stringify(state));
  allowFinishedDisplay = true;
}

export function getFinishedTournament<T>(): T | null {
  if (!allowFinishedDisplay) {
    return null;
  }
  const raw = sessionStorage.getItem(FINISHED_STORAGE_KEY);
  if (!raw) return null;
  try {
    return JSON.parse(raw) as T;
  } catch {
    return null;
  }
}

export function clearFinishedTournament(): void {
  sessionStorage.removeItem(FINISHED_STORAGE_KEY);
  allowFinishedDisplay = false;
}
