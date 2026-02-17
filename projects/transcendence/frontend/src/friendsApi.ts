import type {
  FriendUser,
  FriendListEntry,
  FriendRequest,
  SendFriendRequestResult,
  RespondAction,
  UserProfile,
  BlockedUser,
} from "./friendsTypes.js";
import { readErrorMessage } from "./utils.js";

type FriendUserInput = {
  id: number;
  username: string;
  displayName: string | null;
  avatarUrl: string | null;
  status?: FriendUser["status"];
  statusMessage?: string | null;
};

type FriendListItemPayload = {
  user: FriendUserInput;
  isOnline: boolean;
};

type FriendRequestPayload = {
  id: number;
  from: FriendUserInput;
};

type FriendsResponse = {
  friends: FriendListItemPayload[];
};

type FriendRequestsResponse = {
  requests: FriendRequestPayload[];
};

type BlockedUsersResponse = {
  blocked: FriendUserInput[];
};

type SendFriendRequestResponse = {
  status: SendFriendRequestResult["status"];
  requestId: number | null;
};

type RespondFriendRequestResponse = {
  status: "accepted" | "rejected";
};

type SearchUsersResponse = {
  results: FriendUserInput[];
};

type UserProfileResponse = {
  user: FriendUserInput;
  stats: {
    totalWins: number;
    totalLosses: number;
    winRate: number;
  };
};

function mapUser(raw: FriendUserInput): FriendUser {
  return {
    id: raw.id,
    username: raw.username,
    displayName: raw.displayName,
    avatarUrl: raw.avatarUrl,
    status: raw.status ?? "offline",
    statusMessage: raw.statusMessage,
  };
}

async function ensureOk<T>(res: Response, fallback: string): Promise<T> {
  if (res.ok) {
    return (await res.json()) as T;
  }

  const message = await readErrorMessage(res, fallback, "message");
  throw new Error(message);
}

export async function fetchFriends(): Promise<FriendListEntry[]> {
  const res = await fetch("/api/users/me/friends", {
    method: "GET",
    credentials: "include",
  });

  const data = await ensureOk<FriendsResponse>(
    res,
    `Failed to load friends: ${res.status}`,
  );
  return data.friends.map((item) => ({
    user: mapUser(item.user),
    isOnline: item.isOnline,
  }));
}

export async function fetchFriendRequests(): Promise<FriendRequest[]> {
  const res = await fetch("/api/users/me/friend-requests", {
    method: "GET",
    credentials: "include",
  });

  const data = await ensureOk<FriendRequestsResponse>(
    res,
    `Failed to load friend requests: ${res.status}`,
  );
  return data.requests.map((item) => ({
    id: item.id,
    from: mapUser(item.from),
  }));
}

export async function fetchBlockedUsers(): Promise<BlockedUser[]> {
  const res = await fetch("/api/users/me/blocked", {
    method: "GET",
    credentials: "include",
  });

  const data = await ensureOk<BlockedUsersResponse>(
    res,
    `Failed to load blocked users: ${res.status}`,
  );
  return data.blocked.map(mapUser);
}

export async function sendFriendRequest(
  userId: number,
): Promise<SendFriendRequestResult> {
  const res = await fetch(
    `/api/users/${encodeURIComponent(String(userId))}/friend-request`,
    {
      method: "POST",
      credentials: "include",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({}),
    },
  );

  const data = await ensureOk<SendFriendRequestResponse>(
    res,
    `Failed to send friend request: ${res.status}`,
  );

  return {
    status: data.status,
    requestId: data.requestId,
  };
}

export async function blockUser(userId: number): Promise<void> {
  const res = await fetch(
    `/api/users/${encodeURIComponent(String(userId))}/block`,
    {
      method: "POST",
      credentials: "include",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({}),
    },
  );

  await ensureOk(res, `Failed to block user: ${res.status}`);
}

export async function unblockUser(userId: number): Promise<void> {
  const res = await fetch(
    `/api/users/${encodeURIComponent(String(userId))}/block`,
    {
      method: "DELETE",
      credentials: "include",
    },
  );

  await ensureOk(res, `Failed to unblock user: ${res.status}`);
}

export async function respondToFriendRequest(
  requestId: number,
  action: RespondAction,
): Promise<"accepted" | "rejected"> {
  const res = await fetch(
    `/api/friend-requests/${encodeURIComponent(String(requestId))}/respond`,
    {
      method: "POST",
      credentials: "include",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ action }),
    },
  );

  const data = await ensureOk<RespondFriendRequestResponse>(
    res,
    `Failed to respond to request: ${res.status}`,
  );

  return data.status;
}

export async function searchUsers(query: string): Promise<FriendUser[]> {
  const res = await fetch(
    `/api/users/search?query=${encodeURIComponent(query)}`,
    {
      method: "GET",
      credentials: "include",
    },
  );

  const data = await ensureOk<SearchUsersResponse>(
    res,
    `Failed to search users: ${res.status}`,
  );

  return data.results.map(mapUser);
}

export async function fetchUserProfile(userId: number): Promise<UserProfile> {
  const res = await fetch(`/api/users/${encodeURIComponent(String(userId))}`, {
    method: "GET",
    credentials: "include",
  });

  const data = await ensureOk<UserProfileResponse>(
    res,
    `Failed to load user profile: ${res.status}`,
  );

  return {
    user: mapUser(data.user),
    stats: data.stats,
  };
}
