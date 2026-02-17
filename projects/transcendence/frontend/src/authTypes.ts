type UserStatus = "online" | "offline" | "in_game";

export type AuthUser = {
  id: number;
  username: string;
  displayName: string | null;
  status: UserStatus;
  avatarUrl: string | null;
  statusMessage?: string | null;
  twofaEnabled?: boolean;
};
