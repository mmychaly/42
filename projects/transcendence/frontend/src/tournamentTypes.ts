export type TournamentStatus = "waiting" | "prepared" | "running" | "finished";

export type TournamentParticipant = {
  id: string; // id участника (userId реального игрока или guest-идентификатор)
  participantId?: string; // имя поля, которое приходит с бэка
  alias: string; // отображаемое имя в UI
  isGuest?: boolean; // true — если добавлен как гость
  userId?: string; // дублируем реальный userId для удобства (если есть)
  createdBy?: string; // id пользователя, который создал участника (если есть)
};

export type TournamentMatchType = "regular" | "final" | "third_place";
export type TournamentMatchStatus = "pending" | "running" | "finished";

export type TournamentMatch = {
  id: string;
  round: number; // номер раунда: 0,1,2,... (0 — первый)
  order: number; // порядок внутри раунда: 0,1,...
  type: TournamentMatchType; // обычный матч, финал или матч за 3 место

  // Участники могут быть пустыми, пока матчи следующего раунда не сформированы
  p1: TournamentParticipant | null;
  p2: TournamentParticipant | null;

  status: TournamentMatchStatus;
  winnerId?: string;
  loserId?: string;
};

export type TournamentState = {
  id: string;
  status: TournamentStatus;

  // Все участники турнира
  participants: TournamentParticipant[];

  // Все матчи турнира, включая финал и матч за 3 место.
  matches: TournamentMatch[];

  // Текущий матч, который сейчас "идёт" (по индексу в массиве matches)
  currentMatchIndex: number | null;
};
