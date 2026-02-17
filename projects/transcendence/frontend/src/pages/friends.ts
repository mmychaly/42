import type { NavigateFn } from "../routerTypes.js";
import { getCurrentUser } from "../authStore.js";
import { ChatWidget, setupChatWidget } from "./chatWidget.js";
import {
	fetchFriends,
	fetchFriendRequests,
	fetchUserProfile,
	respondToFriendRequest,
	searchUsers,
	sendFriendRequest,
	fetchBlockedUsers,
	blockUser,
	unblockUser,
} from "../friendsApi.js";
import { createAvatarElement, getUserDisplayName } from "../utils.js";
import type {
	BlockedUser,
	FriendListEntry,
	FriendRequest,
	FriendUser,
	UserProfile,
} from "../friendsTypes.js";

const statusBadge = (status: FriendUser["status"]): string => {
	if (status === "online") {
		return `<span class="px-2 py-0.5 rounded-full text-xs font-semibold bg-emerald-600/80 text-emerald-50">Online</span>`;
	}
	if (status === "in_game") {
		return `<span class="px-2 py-0.5 rounded-full text-xs font-semibold bg-amber-600/80 text-amber-50">In game</span>`;
	}
	return `<span class="px-2 py-0.5 rounded-full text-xs font-semibold bg-slate-700 text-slate-200">Offline</span>`;
};

export const FriendsPage = () => `
  <section class="p-4 max-w-6xl w-full mx-auto">
    <div class="flex flex-col sm:flex-row sm:items-center sm:justify-between gap-2 mb-4">
      <div>
        <h2 class="text-2xl font-bold">Friends</h2>
      </div>
    </div>

    <div class="grid gap-4 lg:grid-cols-[minmax(18rem,22rem),minmax(0,1fr)]">
      <div class="space-y-4">
        <div class="border border-slate-800 rounded-lg bg-slate-950/50 p-3 shadow-lg shadow-slate-950/40">
          <div class="flex items-center gap-2 mb-2">
            <h3 class="font-semibold">Your friends</h3>
            <button id="friends-reload" class="ml-auto text-xs px-2 py-1 rounded bg-slate-800 hover:bg-slate-700 text-slate-200">Reload</button>
          </div>
          <p id="friends-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>
          <div id="friends-list" class="space-y-2 min-h-[6rem]"></div>
        </div>

        <div class="border border-slate-800 rounded-lg bg-slate-950/50 p-3 shadow-lg shadow-slate-950/40">
          <div class="flex items-center gap-2 mb-2">
            <h3 class="font-semibold">Friend requests</h3>
          </div>
          <p id="requests-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>
          <div id="requests-list" class="space-y-2 min-h-[4rem]"></div>
        </div>

        <div class="border border-slate-800 rounded-lg bg-slate-950/50 p-3 shadow-lg shadow-slate-950/40">
          <div class="flex items-center gap-2 mb-2">
            <h3 class="font-semibold">Black list</h3>
          </div>
          <p id="blocked-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>
          <div id="blocked-list" class="space-y-2 min-h-[4rem]"></div>
        </div>
      </div>

      <div class="space-y-4">
        <div class="border border-slate-800 rounded-lg bg-slate-950/50 p-4 shadow-lg shadow-slate-950/40 min-h-[14rem]">
          <div class="flex items-center justify-between gap-2 mb-3">
            <h3 class="font-semibold">Friend preview</h3>
            <span id="preview-note" class="text-xs text-slate-400">Select a user</span>
          </div>
          <div id="friend-preview" class="space-y-3"></div>
        </div>

        <div class="border border-slate-800 rounded-lg bg-slate-950/50 p-4 shadow-lg shadow-slate-950/40">
          <div class="flex items-center justify-between gap-2 mb-3">
            <h3 class="font-semibold">Find new friends</h3>
          </div>
          <form id="friends-search-form" class="flex flex-col sm:flex-row gap-2 mb-2">
            <input
              id="friends-search-input"
              type="text"
              placeholder="Search by username or display name"
              class="flex-1 px-3 py-2 rounded border border-slate-700 bg-slate-900 text-slate-100"
            />
            <button
              id="friends-search-btn"
              type="submit"
              class="px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white font-medium sm:w-auto w-full disabled:opacity-60 disabled:cursor-not-allowed"
            >
              Search
            </button>
          </form>
          <p id="friends-search-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>
          <div id="friends-search-results" class="space-y-2 min-h-[6rem]"></div>
        </div>
      </div>
    </div>
    ${ChatWidget()}
  </section>
`;

export function setupFriendsPage(navigate: NavigateFn): void {
  const me = getCurrentUser();
  if (!me) {
    navigate("/login");
    return;
  }

  const friendsListEl = document.getElementById("friends-list");
  const friendsErrorEl = document.getElementById("friends-error");
  const friendsReloadBtn = document.getElementById(
    "friends-reload",
  ) as HTMLButtonElement | null;

  const requestsListEl = document.getElementById("requests-list");
  const requestsErrorEl = document.getElementById("requests-error");

  const blockedListEl = document.getElementById("blocked-list");
  const blockedErrorEl = document.getElementById("blocked-error");

  const previewEl = document.getElementById("friend-preview");
  const previewNoteEl = document.getElementById("preview-note");

  const searchForm = document.getElementById(
    "friends-search-form",
  ) as HTMLFormElement | null;
  const searchInput = document.getElementById(
    "friends-search-input",
  ) as HTMLInputElement | null;
  const searchBtn = document.getElementById(
    "friends-search-btn",
  ) as HTMLButtonElement | null;
  const searchErrorEl = document.getElementById("friends-search-error");
  const searchResultsEl = document.getElementById("friends-search-results");

  let friends: FriendListEntry[] = [];
  let friendsLoading = false;
  let requests: FriendRequest[] = [];
  let requestsLoading = false;
  let blockedUsers: BlockedUser[] = [];
  let blockedLoading = false;
  let friendsError = "";
  let requestsError = "";
  let blockedError = "";
  let selectedFriendId: number | null = null;
  let selectedProfile: UserProfile | null = null;
  let previewLoading = false;
  let previewError = "";

  let searchResults: FriendUser[] = [];
  let searchLoading = false;
  let searchNotes = new Map<number, string>();
  let searchError = "";

  const { openChatWithUser } = setupChatWidget({
    onUserClick: (userId) => {
      if (selectedFriendId === userId) return;
      selectedFriendId = userId;
      selectedProfile = null;
      previewError = "";
      renderFriends();
      renderBlocked();
      renderPreview();
      void loadFriendProfile(userId);
    },
  });

  const renderFriends = () => {
    if (!friendsListEl) return;
    friendsListEl.innerHTML = "";
    if (friendsErrorEl) friendsErrorEl.textContent = friendsError;

    if (friendsLoading) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Loading friends...";
      friendsListEl.appendChild(p);
      return;
    }

    if (friends.length === 0) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "No friends yet.";
      friendsListEl.appendChild(p);
      return;
    }

    friends.forEach((entry) => {
      const btn = document.createElement("button");
      btn.type = "button";
      btn.className = [
        "w-full flex items-center gap-3 px-3 py-2 rounded border",
        "border-transparent hover:border-slate-700 hover:bg-slate-800/60",
        selectedFriendId === entry.user.id
          ? "border-blue-600 bg-slate-800/70"
          : "bg-slate-900/40",
        "transition-colors duration-150 text-left",
      ].join(" ");
      btn.dataset.userId = String(entry.user.id);

      const avatar = createAvatarElement(entry.user);

      const textBox = document.createElement("div");
      textBox.className = "flex-1 min-w-0";
      const name = document.createElement("p");
      name.className = "font-semibold text-slate-100 truncate";
      name.textContent = getUserDisplayName(entry.user);
      const username = document.createElement("p");
      username.className = "text-xs text-slate-400 truncate";
      username.textContent = `@${entry.user.username}`;
      textBox.appendChild(name);
      textBox.appendChild(username);

      const statusBox = document.createElement("div");
      statusBox.innerHTML = statusBadge(entry.user.status);

      btn.appendChild(avatar);
      btn.appendChild(textBox);
      btn.appendChild(statusBox);

      btn.addEventListener("click", () => {
        if (selectedFriendId === entry.user.id) return;
        selectedFriendId = entry.user.id;
        selectedProfile = null;
        previewError = "";
        renderFriends();
        renderPreview();
        void loadFriendProfile(entry.user.id);
      });

      friendsListEl.appendChild(btn);
    });
  };

  const renderRequests = () => {
    if (!requestsListEl) return;
    requestsListEl.innerHTML = "";

    if (requestsErrorEl) requestsErrorEl.textContent = requestsError;

    if (requestsLoading) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Loading requests...";
      requestsListEl.appendChild(p);
      return;
    }

    if (requests.length === 0) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "No incoming requests.";
      requestsListEl.appendChild(p);
      return;
    }

    requests.forEach((req) => {
      const row = document.createElement("div");
      row.className =
        "flex items-center gap-3 px-3 py-2 rounded border border-slate-800 bg-slate-900/50";
      row.dataset.requestId = String(req.id);

      const avatar = createAvatarElement(req.from);

      const textBox = document.createElement("div");
      textBox.className = "flex-1 min-w-0";
      const name = document.createElement("p");
      name.className = "font-semibold text-slate-100 truncate";
      name.textContent = getUserDisplayName(req.from);
      const username = document.createElement("p");
      username.className = "text-xs text-slate-400 truncate";
      username.textContent = `@${req.from.username}`;
      textBox.appendChild(name);
      textBox.appendChild(username);

      const actions = document.createElement("div");
      actions.className = "flex items-center gap-2";

      const acceptBtn = document.createElement("button");
      acceptBtn.type = "button";
      acceptBtn.textContent = "Accept";
      acceptBtn.className =
        "px-3 py-1 rounded bg-emerald-600 hover:bg-emerald-500 text-xs font-semibold text-white";

      const rejectBtn = document.createElement("button");
      rejectBtn.type = "button";
      rejectBtn.textContent = "Reject";
      rejectBtn.className =
        "px-3 py-1 rounded bg-slate-700 hover:bg-slate-600 text-xs font-semibold text-white";

      const setButtonsState = (
        loading: boolean,
        action?: "accept" | "reject",
      ) => {
        acceptBtn.disabled = loading;
        rejectBtn.disabled = loading;
        if (loading && action === "accept") {
          acceptBtn.textContent = "Accepting...";
        } else {
          acceptBtn.textContent = "Accept";
        }
        if (loading && action === "reject") {
          rejectBtn.textContent = "Rejecting...";
        } else {
          rejectBtn.textContent = "Reject";
        }
      };

      acceptBtn.addEventListener("click", async () => {
        requestsError = "";
        if (requestsErrorEl) requestsErrorEl.textContent = requestsError;
        setButtonsState(true, "accept");
        try {
          const result = await respondToFriendRequest(req.id, "accept");
          if (result === "accepted") {
            await loadFriends();
          }
          requests = requests.filter((r) => r.id !== req.id);
          renderRequests();
          void loadRequests();
        } catch (error) {
          requestsError =
            error instanceof Error ? error.message : "Failed to accept request";
          if (requestsErrorEl) requestsErrorEl.textContent = requestsError;
          setButtonsState(false);
        }
      });

      rejectBtn.addEventListener("click", async () => {
        requestsError = "";
        if (requestsErrorEl) requestsErrorEl.textContent = requestsError;
        setButtonsState(true, "reject");
        try {
          await respondToFriendRequest(req.id, "reject");
          requests = requests.filter((r) => r.id !== req.id);
          renderRequests();
          void loadRequests();
        } catch (error) {
          requestsError =
            error instanceof Error ? error.message : "Failed to reject request";
          if (requestsErrorEl) requestsErrorEl.textContent = requestsError;
          setButtonsState(false);
        }
      });

      actions.appendChild(acceptBtn);
      actions.appendChild(rejectBtn);

      row.appendChild(avatar);
      row.appendChild(textBox);
      row.appendChild(actions);

      requestsListEl.appendChild(row);
    });
  };

  const renderBlocked = () => {
    if (!blockedListEl) return;
    blockedListEl.innerHTML = "";

    if (blockedErrorEl) blockedErrorEl.textContent = blockedError;

    if (blockedLoading) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Loading blocked users...";
      blockedListEl.appendChild(p);
      return;
    }

    if (blockedUsers.length === 0) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Black list is empty.";
      blockedListEl.appendChild(p);
      return;
    }

    blockedUsers.forEach((user) => {
      const row = document.createElement("div");
      row.className =
        "flex items-center gap-3 px-3 py-2 rounded border border-slate-800 bg-slate-900/50";
      row.dataset.userId = String(user.id);

      const avatar = createAvatarElement(user);

      const textBox = document.createElement("div");
      textBox.className = "flex-1 min-w-0";
      const name = document.createElement("p");
      name.className = "font-semibold text-slate-100 truncate";
      name.textContent = getUserDisplayName(user);
      const username = document.createElement("p");
      username.className = "text-xs text-slate-400 truncate";
      username.textContent = `@${user.username}`;
      textBox.appendChild(name);
      textBox.appendChild(username);

      const actions = document.createElement("div");
      actions.className = "flex items-center gap-2";
      const unblockBtn = document.createElement("button");
      unblockBtn.type = "button";
      unblockBtn.textContent = "Unblock";
      unblockBtn.className =
        "px-3 py-1 rounded bg-slate-700 hover:bg-slate-600 text-xs font-semibold text-white";

      unblockBtn.addEventListener("click", async (event) => {
        event.stopPropagation();
        blockedError = "";
        if (blockedErrorEl) blockedErrorEl.textContent = blockedError;
        unblockBtn.disabled = true;
        unblockBtn.textContent = "Unblocking...";
        try {
          await unblockUser(user.id);
          await loadBlocked();
          await loadFriends();
        } catch (error) {
          blockedError =
            error instanceof Error ? error.message : "Failed to unblock user";
          if (blockedErrorEl) blockedErrorEl.textContent = blockedError;
        } finally {
          unblockBtn.disabled = false;
          unblockBtn.textContent = "Unblock";
        }
      });

      row.addEventListener("click", () => {
        if (selectedFriendId === user.id) return;
        selectedFriendId = user.id;
        selectedProfile = null;
        previewError = "";
        renderFriends();
        renderBlocked();
        renderPreview();
        void loadFriendProfile(user.id);
      });

      actions.appendChild(unblockBtn);

      row.appendChild(avatar);
      row.appendChild(textBox);
      row.appendChild(actions);

      blockedListEl.appendChild(row);
    });
  };

  const renderPreview = () => {
    if (!previewEl) return;
    previewEl.innerHTML = "";

    const isSelectedBlocked = selectedFriendId
      ? blockedUsers.some((user) => user.id === selectedFriendId)
      : false;

    if (previewNoteEl) {
      if (!selectedFriendId) {
        previewNoteEl.textContent = "Select a user";
      } else if (previewLoading) {
        previewNoteEl.textContent = "Loading...";
      } else if (previewError) {
        previewNoteEl.textContent = "Error";
      } else {
        previewNoteEl.textContent = "";
      }
    }

    if (!selectedFriendId) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Choose someone from the list to see their profile.";
      previewEl.appendChild(p);
      return;
    }

    if (previewLoading) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Loading friend...";
      previewEl.appendChild(p);
      return;
    }

    if (previewError) {
      const p = document.createElement("p");
      p.className = "text-sm text-red-400";
      p.textContent = previewError;
      previewEl.appendChild(p);
      return;
    }

    if (!selectedProfile) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "No data.";
      previewEl.appendChild(p);
      return;
    }

    const { user, stats } = selectedProfile;

    const header = document.createElement("div");
    header.className = "flex flex-col sm:flex-row sm:items-center gap-3";

    const avatar = createAvatarElement(user, {
      sizeClass: "w-16 h-16",
      textClass: "text-lg",
    });

    const info = document.createElement("div");
    info.className = "flex-1 min-w-0 space-y-1";
    const name = document.createElement("p");
    name.className = "text-lg font-semibold text-slate-100 truncate";
    name.textContent = getUserDisplayName(user);
    const username = document.createElement("p");
    username.className = "text-sm text-slate-400 truncate";
    username.textContent = `@${user.username}`;
    const statusWrap = document.createElement("div");
    statusWrap.className = "mt-1";
    statusWrap.innerHTML = statusBadge(user.status);

    info.appendChild(name);
    info.appendChild(username);
    info.appendChild(statusWrap);

    header.appendChild(avatar);
    header.appendChild(info);

    const statusMsgBox = document.createElement("div");
    statusMsgBox.className = "text-sm text-slate-200";
    const statusTitle = document.createElement("p");
    statusTitle.className = "font-semibold";
    statusTitle.textContent = "Status message";
    const statusMsg = document.createElement("p");
    statusMsg.className = "mt-1 text-slate-300 whitespace-pre-wrap break-words";
    statusMsg.textContent =
      user.statusMessage && user.statusMessage.trim().length > 0
        ? user.statusMessage
        : "—";
    statusMsgBox.appendChild(statusTitle);
    statusMsgBox.appendChild(statusMsg);

    const statsBox = document.createElement("div");
    statsBox.className =
      "grid grid-cols-1 sm:grid-cols-3 gap-3 text-sm text-slate-200";

    const stat = (label: string, value: string) => {
      const box = document.createElement("div");
      box.className = "p-3 rounded bg-slate-900/60 border border-slate-800";
      const l = document.createElement("p");
      l.className = "text-xs text-slate-400";
      l.textContent = label;
      const v = document.createElement("p");
      v.className = "text-lg font-semibold text-slate-100";
      v.textContent = value;
      box.appendChild(l);
      box.appendChild(v);
      return box;
    };

    const winRatePercent = Number.isFinite(stats.winRate)
      ? Math.round(stats.winRate * 100)
      : 0;

    statsBox.appendChild(stat("Wins", `${stats.totalWins}`));
    statsBox.appendChild(stat("Losses", `${stats.totalLosses}`));
    statsBox.appendChild(stat("Win rate", `${winRatePercent}%`));

    const actionRow = document.createElement("div");
    actionRow.className = "flex flex-col sm:flex-row gap-2";

    if (!isSelectedBlocked) {
      const chatBtn = document.createElement("button");
      chatBtn.type = "button";
      chatBtn.className =
        "px-3 py-2 rounded text-sm font-semibold bg-blue-600 hover:bg-blue-500 text-white";
      chatBtn.textContent = "Message";
      chatBtn.addEventListener("click", async () => {
        if (!selectedFriendId) return;
        try {
          await openChatWithUser(selectedFriendId);
        } catch (error) {
          previewError =
            error instanceof Error ? error.message : "Failed to open chat";
          renderPreview();
        }
      });
      actionRow.appendChild(chatBtn);
    }

    const blockBtn = document.createElement("button");
    blockBtn.type = "button";
    blockBtn.className = [
      "px-3 py-2 rounded text-sm font-semibold",
      isSelectedBlocked
        ? "bg-slate-700 hover:bg-slate-600 text-white"
        : "bg-rose-600 hover:bg-rose-500 text-white",
    ].join(" ");
    blockBtn.textContent = isSelectedBlocked
      ? "Unblock this user"
      : "Block this user";

    blockBtn.addEventListener("click", async () => {
      if (!selectedFriendId) return;
      blockBtn.disabled = true;
      blockBtn.textContent = isSelectedBlocked
        ? "Unblocking..."
        : "Blocking...";
      previewError = "";
      try {
        if (isSelectedBlocked) {
          await unblockUser(selectedFriendId);
        } else {
          await blockUser(selectedFriendId);
        }
        await loadBlocked();
        await loadFriends();
        await loadRequests();
      } catch (error) {
        previewError =
          error instanceof Error
            ? error.message
            : "Failed to update block list";
      } finally {
        blockBtn.disabled = false;
        renderPreview();
      }
    });

    actionRow.appendChild(blockBtn);

    previewEl.appendChild(header);
    previewEl.appendChild(statusMsgBox);
    previewEl.appendChild(statsBox);
    previewEl.appendChild(actionRow);
  };

  const renderSearch = () => {
    if (!searchResultsEl) return;
    searchResultsEl.innerHTML = "";

    if (searchLoading) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = "Searching...";
      searchResultsEl.appendChild(p);
      return;
    }

    if (searchErrorEl) {
      searchErrorEl.textContent = searchError;
    }

    if (searchResults.length === 0) {
      const p = document.createElement("p");
      p.className = "text-sm text-slate-400";
      p.textContent = searchError ? "" : "Start by typing a name above.";
      searchResultsEl.appendChild(p);
      return;
    }

    searchResults.forEach((user) => {
      const row = document.createElement("div");
      row.className =
        "flex items-center gap-3 px-3 py-2 rounded border border-slate-800 bg-slate-900/50";

      const avatar = createAvatarElement(user);

      const textBox = document.createElement("div");
      textBox.className = "flex-1 min-w-0";
      const name = document.createElement("p");
      name.className = "font-semibold text-slate-100 truncate";
      name.textContent = getUserDisplayName(user);
      const username = document.createElement("p");
      username.className = "text-xs text-slate-400 truncate";
      username.textContent = `@${user.username}`;
      const statusMsg = document.createElement("p");
      statusMsg.className = "text-xs text-slate-500 truncate";
      statusMsg.textContent =
        user.statusMessage && user.statusMessage.trim().length > 0
          ? user.statusMessage
          : "";
      textBox.appendChild(name);
      textBox.appendChild(username);
      if (statusMsg.textContent) textBox.appendChild(statusMsg);

      const statusBox = document.createElement("div");
      statusBox.className = "flex flex-col items-end gap-1";
      const badgeWrap = document.createElement("div");
      badgeWrap.innerHTML = statusBadge(user.status);

      const sendBtn = document.createElement("button");
      sendBtn.type = "button";
      sendBtn.className =
        "px-3 py-1 rounded bg-blue-600 hover:bg-blue-500 text-xs font-semibold text-white disabled:opacity-50 disabled:cursor-not-allowed";
      sendBtn.textContent = "Send request";

      const note = document.createElement("p");
      note.className = "text-[11px] text-slate-400 min-h-[1rem]";
      note.textContent = searchNotes.get(user.id) ?? "";

      const setSending = (state: boolean) => {
        sendBtn.disabled = state;
        sendBtn.textContent = state ? "Sending..." : "Send request";
      };

      sendBtn.addEventListener("click", async () => {
        setSending(true);
        if (searchErrorEl) searchErrorEl.textContent = "";
        try {
          const res = await sendFriendRequest(user.id);
          let noteText = "Request sent";
          if (res.status === "accepted") {
            noteText = "Already friends";
            await loadFriends();
          } else if (res.status === "pending" && !res.requestId) {
            noteText = "Request already sent";
          }
          searchNotes.set(user.id, noteText);
        } catch (error) {
          const msg =
            error instanceof Error ? error.message : "Failed to send request";
          searchNotes.set(user.id, msg);
          if (searchErrorEl) searchErrorEl.textContent = "";
        } finally {
          setSending(false);
          renderSearch();
        }
      });

      statusBox.appendChild(badgeWrap);
      statusBox.appendChild(sendBtn);
      statusBox.appendChild(note);

      row.appendChild(avatar);
      row.appendChild(textBox);
      row.appendChild(statusBox);

      searchResultsEl.appendChild(row);
    });
  };

  const loadFriends = async () => {
    friendsLoading = true;
    friendsError = "";
    renderFriends();
    try {
      friends = await fetchFriends();
      // Remove selection if user disappeared
      if (
        selectedFriendId &&
        !friends.some((f) => f.user.id === selectedFriendId) &&
        !blockedUsers.some((user) => user.id === selectedFriendId)
      ) {
        selectedFriendId = null;
        selectedProfile = null;
      }
    } catch (error) {
      friendsError =
        error instanceof Error ? error.message : "Failed to load friends";
    } finally {
      friendsLoading = false;
      renderFriends();
      renderPreview();
    }
  };

  const loadBlocked = async () => {
    blockedLoading = true;
    blockedError = "";
    renderBlocked();
    try {
      blockedUsers = await fetchBlockedUsers();
      if (
        selectedFriendId &&
        !blockedUsers.some((user) => user.id === selectedFriendId) &&
        !friends.some((f) => f.user.id === selectedFriendId)
      ) {
        selectedFriendId = null;
        selectedProfile = null;
      }
    } catch (error) {
      blockedError =
        error instanceof Error ? error.message : "Failed to load blocked users";
    } finally {
      blockedLoading = false;
      renderBlocked();
      renderPreview();
    }
  };

  const loadRequests = async () => {
    requestsLoading = true;
    requestsError = "";
    renderRequests();
    try {
      requests = await fetchFriendRequests();
    } catch (error) {
      requestsError =
        error instanceof Error ? error.message : "Failed to load requests";
    } finally {
      requestsLoading = false;
      renderRequests();
    }
  };

  const loadFriendProfile = async (userId: number) => {
    const targetId = userId;
    previewLoading = true;
    previewError = "";
    renderPreview();

    try {
      const profile = await fetchUserProfile(userId);
      if (selectedFriendId !== targetId) {
        return; // selection changed while loading
      }
      selectedProfile = profile;
    } catch (error) {
      if (selectedFriendId !== targetId) {
        return;
      }
      selectedProfile = null;
      previewError =
        error instanceof Error ? error.message : "Failed to load profile";
    } finally {
      if (selectedFriendId !== targetId) {
        return;
      }
      previewLoading = false;
      renderPreview();
    }
  };

  const performSearch = async (query: string) => {
    searchLoading = true;
    searchError = "";
    searchNotes = new Map<number, string>();
    if (searchBtn) searchBtn.disabled = true;
    renderSearch();

    try {
      const results = await searchUsers(query);
      searchResults = results.filter((user) => user.id !== me.id);
      if (searchResults.length === 0) {
        searchError = "No users found";
      }
    } catch (error) {
      searchError =
        error instanceof Error ? error.message : "Failed to search users";
      searchResults = [];
    } finally {
      searchLoading = false;
      if (searchBtn) searchBtn.disabled = false;
      if (searchErrorEl) searchErrorEl.textContent = searchError;
      renderSearch();
    }
  };

  if (friendsReloadBtn) {
    friendsReloadBtn.addEventListener("click", () => {
      void loadFriends();
      void loadRequests();
    });
  }

  if (searchForm && searchInput) {
    searchForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const query = searchInput.value.trim();
      if (!query || query.length < 2) {
        searchError = "Enter at least 2 characters";
        if (searchErrorEl) searchErrorEl.textContent = searchError;
        return;
      }
      void performSearch(query);
    });
  }

  friendsLoading = true;
  requestsLoading = true;
  blockedLoading = true;

  renderFriends();
  renderRequests();
  renderBlocked();
  renderPreview();
  renderSearch();

  void loadFriends();
  void loadRequests();
  void loadBlocked();
}
