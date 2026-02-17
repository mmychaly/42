import type { AuthUser } from "./authTypes.js";

export type FriendUser = {
  id: number;
  username: string;
  displayName: string | null;
  avatarUrl: string | null;
  status: AuthUser["status"];
  statusMessage?: string | null;
};

export type FriendListEntry = {
  user: FriendUser;
  isOnline: boolean;
};

export type FriendRequest = {
  id: number;
  from: FriendUser;
};

export type BlockedUser = FriendUser;

export type SendFriendRequestResult = {
  status: "pending" | "accepted";
  requestId: number | null;
};

export type RespondAction = "accept" | "reject";

export type UserProfile = {
  user: FriendUser;
  stats: {
    totalWins: number;
    totalLosses: number;
    winRate: number;
  };
};
