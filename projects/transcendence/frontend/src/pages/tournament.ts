import type { NavigateFn } from "../routerTypes.js";
import {
	getTournament,
	resetTournament,
	addParticipant,
	startTournament,
	prepareTournament,
} from "../tournamentApi.js";
import type { TournamentState } from "../tournamentTypes.js";
import { searchUsers } from "../friendsApi.js";
import type { FriendUser } from "../friendsTypes.js";
import { getCurrentUser } from "../authStore.js";
import { getUserDisplayName } from "../utils.js";
import {
	rememberTournamentGuest,
	isTournamentGuestOnThisDevice,
	resetTournamentGuests,
	setTournamentJoin,
	getFinishedTournament,
	clearFinishedTournament,
	setTournamentSnapshot,
	clearTournamentSnapshot,
} from "../tournamentSession.js";
import { ChatWidget, setupChatWidget } from "./chatWidget.js";

const PARTICIPANTS_LIMIT = 4;

const getInviteErrorForUser = (user: FriendUser): string | null => {
	if (user.status === "in_game") return "Player in game now, wait";
	if (user.status !== "online") return "Can't invite offline players";
	return null;
};

export const TournamentPage = () => `
  <section class="p-4 max-w-xl mx-auto">
    <h2 class="text-2xl font-bold mb-4">Tournament</h2>

    <div class="mb-4 flex items-center gap-2">
      <span class="text-sm text-slate-400">Status:</span>
      <span id="tournament-status" class="text-sm font-semibold text-slate-100">
        Loading...
      </span>
      <button
        id="tournament-reset"
        class="ml-auto px-3 py-1 rounded bg-green-600 hover:bg-green-500 text-white text-sm"
      >
        Reset
      </button>
    </div>

    <form id="tournament-add-form" class="space-y-2 mb-4">
      <div class="flex gap-2">
        <input
          id="tournament-name-input"
          type="text"
          placeholder="Search user or type guest alias"
          class="flex-1 px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
        />
        <button
          id="tournament-add-guest"
          type="submit"
          class="px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white font-medium disabled:opacity-50 disabled:cursor-not-allowed"
          disabled
        >
          Add guest
        </button>
      </div>
      <div
        id="tournament-search-results"
        class="border border-slate-700 rounded px-3 py-2 bg-slate-900/50 text-sm min-h-[2.75rem]"
      >
        <p class="text-slate-400">Start typing to search players or add as guest.</p>
      </div>
    </form>
    <p id="tournament-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>

    <div class="mb-4">
      <div class="flex items-center mb-2">
        <h3 class="font-semibold">Participants</h3>
        <span id="tournament-players-count" class="ml-2 text-xs text-slate-400"></span>
      </div>
      <ul
        id="tournament-players-list"
        class="space-y-1 text-slate-200 text-sm border border-slate-700 rounded p-3 min-h-[2rem]"
      >
        </ul>
    </div>

    <div class="mb-4 flex items-center gap-3">
      <button
        id="tournament-prepare"
        class="px-4 py-2 rounded bg-amber-600 hover:bg-amber-500 text-white text-sm disabled:opacity-40 disabled:cursor-not-allowed"
        disabled
      >
        Set tournament
      </button>
      <button
        id="tournament-start"
        class="px-4 py-2 rounded bg-green-600 hover:bg-green-500 text-white text-sm disabled:opacity-40 disabled:cursor-not-allowed"
        disabled
      >
        Start matches
      </button>
      <span class="text-xs text-slate-400">
        Need ${PARTICIPANTS_LIMIT} players
      </span>
    </div>

    <div class="border border-slate-600 rounded p-3 text-sm space-y-2">
      <div>
        <span class="font-semibold">Current match:</span>
        <span id="tournament-current-match" class="ml-2 text-slate-200">
          —
        </span>
      </div>
      <div>
        <span class="font-semibold">Next up:</span>
        <span id="tournament-next-match" class="ml-2 text-slate-200">
          —
        </span>
      </div>

      <div class="mt-3">
        <p class="text-xs text-slate-400 mb-1">Join match</p>
        <div class="flex flex-col sm:flex-row gap-2">
          <button
            id="tournament-join-p1"
            class="px-3 py-1 rounded bg-blue-700 hover:bg-blue-600 text-white text-xs disabled:opacity-40 disabled:cursor-not-allowed w-full sm:w-auto"
            disabled
          >
            Join as —
          </button>
          <button
            id="tournament-join-p2"
            class="px-3 py-1 rounded bg-blue-700 hover:bg-blue-600 text-white text-xs disabled:opacity-40 disabled:cursor-not-allowed w-full sm:w-auto"
            disabled
          >
            Join as —
          </button>
        </div>
        <p id="tournament-join-message" class="text-xs text-slate-300 mt-2 min-h-[1.25rem]"></p>
      </div>
    </div>

    <div class="mt-4 border border-slate-600 rounded p-3 text-sm">
      <h3 class="font-semibold mb-2">Match results</h3>
      <div class="overflow-x-auto">
        <table class="w-full text-xs">
          <thead class="text-slate-400">
            <tr>
              <th class="text-left py-1 pr-2">Match</th>
              <th class="text-left py-1 pr-2">Players</th>
              <th class="text-left py-1">Result</th>
            </tr>
          </thead>
          <tbody id="tournament-summary-body" class="text-slate-200"></tbody>
        </table>
      </div>
    </div>

    <div
      id="tournament-results"
      class="mt-4 border border-slate-600 rounded p-3 text-sm hidden"
    >
      <h3 class="font-semibold mb-2">Results</h3>
      <ul class="space-y-1 text-slate-200">
        <li id="tournament-result-1">1st: —</li>
        <li id="tournament-result-2">2nd: —</li>
        <li id="tournament-result-3">3rd: —</li>
        <li id="tournament-result-4">4th: —</li>
      </ul>
    </div>
    ${ChatWidget()}
  </section>
`;

// ---------- Results Calculation ----------

function computeResults(state: TournamentState): {
	first?: string;
	second?: string;
	third?: string;
	fourth?: string;
} {
	const res: {
		first?: string;
		second?: string;
		third?: string;
		fourth?: string;
	} = {};

	if (state.status !== "finished") {
		return res;
	}

	// Get winner of final and third place match
	// Final
	const finalMatch = state.matches.find((m) => m.type === "final");
	if (!finalMatch || !finalMatch.winnerId || !finalMatch.p1 || !finalMatch.p2) {
		return res;
	}

	const finalP1Id = getParticipantId(finalMatch.p1);
	const finalP2Id = getParticipantId(finalMatch.p2);
	const finalWinner =
		finalMatch.winnerId &&
		finalP1Id &&
		String(finalMatch.winnerId) === String(finalP1Id)
			? finalMatch.p1
			: finalMatch.winnerId &&
				  finalP2Id &&
				  String(finalMatch.winnerId) === String(finalP2Id)
				? finalMatch.p2
				: null;
	if (!finalWinner) {
		return res;
	}
	const finalLoser =
		finalWinner === finalMatch.p1 ? finalMatch.p2 : finalMatch.p1;

	res.first = finalWinner.alias;
	res.second = finalLoser?.alias;

	// Third place match
	const thirdMatch = state.matches.find((m) => m.type === "third_place");
	if (thirdMatch && thirdMatch.winnerId && thirdMatch.p1 && thirdMatch.p2) {
		const thirdP1Id = getParticipantId(thirdMatch.p1);
		const thirdP2Id = getParticipantId(thirdMatch.p2);
		const thirdWinner =
			thirdP1Id && String(thirdMatch.winnerId) === String(thirdP1Id)
				? thirdMatch.p1
				: thirdP2Id && String(thirdMatch.winnerId) === String(thirdP2Id)
					? thirdMatch.p2
					: null;
		if (thirdWinner) {
			const thirdLoser =
				thirdWinner === thirdMatch.p1 ? thirdMatch.p2 : thirdMatch.p1;

			res.third = thirdWinner.alias;
			res.fourth = thirdLoser?.alias;
		}
	}

	return res;
}

function getParticipantAlias(
	participant: TournamentState["participants"][number] | null | undefined
): string {
	return participant?.alias ?? "TBD";
}

function getParticipantId(
	participant: TournamentState["participants"][number] | null | undefined
): string | undefined {
	if (!participant) return undefined;
	return participant.id ?? participant.participantId ?? participant.userId;
}

function canControlParticipantOnDevice(
	tournamentId: string,
	meId: string | null,
	participant: TournamentState["participants"][number] | null | undefined
): boolean {
	if (!participant) return false;
	const participantId = getParticipantId(participant);
	if (!participantId) return false;
	// Guest can only play on the device they were added on
	if (participant.isGuest) {
		return isTournamentGuestOnThisDevice(tournamentId, participantId);
	}
	return Boolean(meId && String(participantId) === String(meId));
}

function findCurrentMatch(state: TournamentState): {
	match?: TournamentState["matches"][number];
	index: number;
} {
	const runningIdx = state.matches.findIndex((m) => m.status === "running");
	if (runningIdx !== -1) {
		return { match: state.matches[runningIdx], index: runningIdx };
	}

	if (state.currentMatchIndex !== null) {
		const matchByIndex = state.matches[state.currentMatchIndex];
		if (matchByIndex) {
			return { match: matchByIndex, index: state.currentMatchIndex };
		}
	}

	return { match: undefined, index: -1 };
}

function findNextMatch(
	state: TournamentState,
	currentIndex: number
): TournamentState["matches"][number] | undefined {
	if (currentIndex >= 0) {
		return state.matches
			.slice(currentIndex + 1)
			.find((m) => m.status !== "finished");
	}

	return state.matches.find(
		(m) => m.status === "pending" || m.status === "running"
	);
}

function formatMatchLabel(
	match: TournamentState["matches"][number] | undefined
): string {
	if (!match) return "—";
	return `${getParticipantAlias(match.p1)} vs ${getParticipantAlias(match.p2)}`;
}

function formatMatchTitle(match: TournamentState["matches"][number]): string {
	if (match.type === "final") return "Final";
	if (match.type === "third_place") return "3rd place";
	return `Round ${match.round + 1} · Match ${match.order + 1}`;
}

function getMatchWinnerAlias(
	match: TournamentState["matches"][number]
): string | null {
	if (!match.winnerId) return null;
	const winnerId = String(match.winnerId);
	const p1Id = match.p1 ? getParticipantId(match.p1) : undefined;
	const p2Id = match.p2 ? getParticipantId(match.p2) : undefined;

	if (p1Id && String(p1Id) === winnerId) return match.p1?.alias ?? null;
	if (p2Id && String(p2Id) === winnerId) return match.p2?.alias ?? null;
	return null;
}

function getJoinDisabledTitle(options: {
	isMatchActive: boolean;
	isLocalMode: boolean;
	isGuest: boolean;
}): string {
	if (!options.isMatchActive) {
		return "Match is not active yet";
	}
	if (options.isLocalMode) {
		return "Match is available only on this device";
	}
	if (options.isGuest) {
		return "Guest can join only from the device that added them";
	}
	return "Not available on this device";
}

function renderStatusBadge(
	state: TournamentState,
	statusEl: HTMLElement | null
): void {
	if (statusEl) {
		statusEl.textContent = state.status.toUpperCase();
	}
}

function renderNameInput(
	state: TournamentState,
	nameInputEl: HTMLInputElement | null
): void {
	const isFull = state.participants.length >= PARTICIPANTS_LIMIT;
	const addingLocked = state.status !== "waiting" || isFull;
	if (!nameInputEl) return;
	nameInputEl.disabled = addingLocked;
	nameInputEl.title = addingLocked
		? isFull
			? "Tournament is full"
			: "Tournament already started"
		: "";
}

function renderParticipants(
	state: TournamentState,
	playersList: HTMLUListElement | null,
	playersCountEl: HTMLElement | null
): void {
	if (playersList) {
		playersList.innerHTML = "";
		state.participants.forEach((p, index) => {
			const li = document.createElement("li");
			li.className = "flex items-center gap-2";

			const label = document.createElement("span");
			label.textContent = `${index + 1}. ${p.alias}`;
			li.appendChild(label);

			if (p.isGuest) {
				const badge = document.createElement("span");
				badge.className =
					"px-2 py-0.5 text-[10px] rounded-full bg-slate-800 text-slate-200";
				badge.textContent = "Guest";
				li.appendChild(badge);
			}

			playersList.appendChild(li);
		});
	}

	if (playersCountEl) {
		playersCountEl.textContent = `(${state.participants.length})`;
	}
}

function renderActionButtons(
	state: TournamentState,
	prepareBtn: HTMLButtonElement | null,
	startBtn: HTMLButtonElement | null,
	resetBtn: HTMLButtonElement | null
): void {
	const count = state.participants.length;
	if (prepareBtn) {
		prepareBtn.disabled =
			state.status !== "waiting" || count !== PARTICIPANTS_LIMIT;
	}
	if (startBtn) {
		startBtn.disabled = state.status !== "prepared";
	}
	if (resetBtn) {
		resetBtn.disabled = false;
		resetBtn.classList.remove("opacity-50", "cursor-not-allowed");
		resetBtn.removeAttribute("title");
	}
}

function renderMatchLabels(
	currentMatchEl: HTMLElement | null,
	nextMatchEl: HTMLElement | null,
	currentMatch: TournamentState["matches"][number] | undefined,
	nextMatch: TournamentState["matches"][number] | undefined
): void {
	if (currentMatchEl) {
		currentMatchEl.textContent = formatMatchLabel(currentMatch);
	}
	if (nextMatchEl) {
		nextMatchEl.textContent = formatMatchLabel(nextMatch);
	}
}

function renderJoinButtons(options: {
	currentMatch: TournamentState["matches"][number] | undefined;
	canJoin: (
		participant: TournamentState["participants"][number] | null | undefined
	) => boolean;
	canJoinMatch: boolean;
	joinP1Btn: HTMLButtonElement | null;
	joinP2Btn: HTMLButtonElement | null;
}): void {
	const { currentMatch, canJoin, canJoinMatch, joinP1Btn, joinP2Btn } = options;
	const canLocalControl = Boolean(
		currentMatch?.p1 &&
			currentMatch?.p2 &&
			canJoin(currentMatch.p1) &&
			canJoin(currentMatch.p2)
	);
	const canLocalJoin = Boolean(canLocalControl && canJoinMatch);

	// In local mode, show one Join button and hide the other
	if (joinP1Btn) {
		if (currentMatch) {
			const joinLabel = canLocalControl
				? `Join local match: ${getParticipantAlias(currentMatch.p1)} vs ${getParticipantAlias(currentMatch.p2)}`
				: `Join as ${getParticipantAlias(currentMatch.p1)}`;
			joinP1Btn.textContent = joinLabel;
			const canJoinP1 = canJoin(currentMatch.p1);
			const allowed = canLocalControl
				? canLocalJoin
				: canJoinP1 && canJoinMatch;
			joinP1Btn.disabled = !allowed;
			if (!allowed) {
				joinP1Btn.title = getJoinDisabledTitle({
					isMatchActive: canJoinMatch,
					isLocalMode: canLocalControl,
					isGuest: Boolean(currentMatch.p1?.isGuest),
				});
			} else {
				joinP1Btn.removeAttribute("title");
			}
		} else {
			joinP1Btn.textContent = "Join as —";
			joinP1Btn.disabled = true;
			joinP1Btn.removeAttribute("title");
		}
	}

	if (joinP2Btn) {
		if (currentMatch) {
			joinP2Btn.textContent = `Join as ${getParticipantAlias(currentMatch.p2)}`;
			const canJoinP2 = canJoin(currentMatch.p2);
			const allowed = canJoinP2 && canJoinMatch;
			joinP2Btn.disabled = !allowed;
			if (!allowed) {
				joinP2Btn.title = getJoinDisabledTitle({
					isMatchActive: canJoinMatch,
					isLocalMode: false,
					isGuest: Boolean(currentMatch.p2?.isGuest),
				});
			} else {
				joinP2Btn.removeAttribute("title");
			}
		} else {
			joinP2Btn.textContent = "Join as —";
			joinP2Btn.disabled = true;
			joinP2Btn.removeAttribute("title");
		}

		joinP2Btn.classList.toggle("hidden", canLocalControl);
	}
}

function renderSummaryTable(
	state: TournamentState,
	summaryBody: HTMLTableSectionElement | null
): void {
	if (!summaryBody) return;
	summaryBody.innerHTML = "";
	const matches = [...state.matches].sort(
		(a, b) => a.round - b.round || a.order - b.order
	);

	if (matches.length === 0) {
		const row = document.createElement("tr");
		row.innerHTML =
			'<td class="py-2 text-slate-400" colspan="3">No matches yet.</td>';
		summaryBody.appendChild(row);
		return;
	}

	matches.forEach((match) => {
		const row = document.createElement("tr");
		row.className = "border-t border-slate-800";

		const titleCell = document.createElement("td");
		titleCell.className = "py-1 pr-2";
		titleCell.textContent = formatMatchTitle(match);

		const playersCell = document.createElement("td");
		playersCell.className = "py-1 pr-2";
		playersCell.textContent = formatMatchLabel(match);

		const resultCell = document.createElement("td");
		resultCell.className = "py-1";
		const winner = getMatchWinnerAlias(match);
		if (match.status === "finished" && winner) {
			resultCell.textContent = `Winner: ${winner}`;
		} else if (match.status === "running") {
			resultCell.textContent = "In progress";
		} else {
			resultCell.textContent = "Pending";
		}

		row.appendChild(titleCell);
		row.appendChild(playersCell);
		row.appendChild(resultCell);
		summaryBody.appendChild(row);
	});
}

function renderResultsBox(
	state: TournamentState,
	resultsBox: HTMLElement | null,
	res1: HTMLElement | null,
	res2: HTMLElement | null,
	res3: HTMLElement | null,
	res4: HTMLElement | null
): void {
	if (!resultsBox || !res1 || !res2 || !res3 || !res4) return;
	if (state.status === "finished") {
		const results = computeResults(state);
		resultsBox.classList.remove("hidden");

		res1.textContent = `1st: ${results.first ?? "—"}`;
		res2.textContent = `2nd: ${results.second ?? "—"}`;
		res3.textContent = `3rd: ${results.third ?? "—"}`;
		res4.textContent = `4th: ${results.fourth ?? "—"}`;
	} else {
		resultsBox.classList.add("hidden");
	}
}



// ---------- Render Tournament State ----------

function renderTournamentState(state: TournamentState): void {
	const me = getCurrentUser();
	const meId = me ? String(me.id) : null;

	const canJoin = (
		participant: TournamentState["participants"][number] | null | undefined
	) => canControlParticipantOnDevice(state.id, meId, participant);

	const statusEl = document.getElementById("tournament-status");
	const errorEl = document.getElementById("tournament-error");
	const playersList = document.getElementById(
		"tournament-players-list"
	) as HTMLUListElement | null;
	const playersCountEl = document.getElementById("tournament-players-count");
	const prepareBtn = document.getElementById(
		"tournament-prepare"
	) as HTMLButtonElement | null;
	const startBtn = document.getElementById(
		"tournament-start"
	) as HTMLButtonElement | null;
	const resetBtn = document.getElementById(
		"tournament-reset"
	) as HTMLButtonElement | null;
	const currentMatchEl = document.getElementById("tournament-current-match");
	const nextMatchEl = document.getElementById("tournament-next-match");
	const joinP1Btn = document.getElementById(
		"tournament-join-p1"
	) as HTMLButtonElement | null;
	const joinP2Btn = document.getElementById(
		"tournament-join-p2"
	) as HTMLButtonElement | null;
	const joinMsgEl = document.getElementById("tournament-join-message");
	const nameInputEl = document.getElementById(
		"tournament-name-input"
	) as HTMLInputElement | null;
	const summaryBody = document.getElementById(
		"tournament-summary-body"
	) as HTMLTableSectionElement | null;

	const resultsBox = document.getElementById("tournament-results");
	const res1 = document.getElementById("tournament-result-1");
	const res2 = document.getElementById("tournament-result-2");
	const res3 = document.getElementById("tournament-result-3");
	const res4 = document.getElementById("tournament-result-4");

	if (errorEl) errorEl.textContent = "";
	if (joinMsgEl) joinMsgEl.textContent = "";

	renderStatusBadge(state, statusEl);
	renderNameInput(state, nameInputEl);
	renderParticipants(state, playersList, playersCountEl);
	renderActionButtons(state, prepareBtn, startBtn, resetBtn);

	const { match: currentMatch, index: currentMatchIndex } =
		findCurrentMatch(state);
	const nextMatch = findNextMatch(state, currentMatchIndex);

	renderMatchLabels(currentMatchEl, nextMatchEl, currentMatch, nextMatch);

	const canJoinMatch =
		state.status === "running" && currentMatch?.status === "running";

	// Local mode is possible only when both participants are available on this device.
	renderJoinButtons({
		currentMatch,
		canJoin,
		canJoinMatch,
		joinP1Btn,
		joinP2Btn,
	});

	renderSummaryTable(state, summaryBody);
	renderResultsBox(state, resultsBox, res1, res2, res3, res4);
}



// ---------- Setup Page ----------

export function setupTournamentPage(navigate: NavigateFn): void {
	const me = getCurrentUser();
	if (!me) {
		navigate("/login");
		return;
	}

	setupChatWidget();

	const errorEl = document.getElementById("tournament-error");
	const addForm = document.getElementById(
		"tournament-add-form"
	) as HTMLFormElement | null;
	const nameInput = document.getElementById(
		"tournament-name-input"
	) as HTMLInputElement | null;
	const addGuestBtn = document.getElementById(
		"tournament-add-guest"
	) as HTMLButtonElement | null;
	const searchResultsEl = document.getElementById("tournament-search-results");
	const resetBtn = document.getElementById(
		"tournament-reset"
	) as HTMLButtonElement | null;
	const prepareBtn = document.getElementById(
		"tournament-prepare"
	) as HTMLButtonElement | null;
	const startBtn = document.getElementById(
		"tournament-start"
	) as HTMLButtonElement | null;
	const joinP1Btn = document.getElementById(
		"tournament-join-p1"
	) as HTMLButtonElement | null;
	const joinP2Btn = document.getElementById(
		"tournament-join-p2"
	) as HTMLButtonElement | null;
	const joinMsgEl = document.getElementById("tournament-join-message");

	let latestState: TournamentState | null = null;
	let searchResults: FriendUser[] = [];
	let searchLoading = false;
	let searchError = "";
	let addInProgress = false;
	let searchRequestId = 0;
	let lastQuery = "";

	const isTournamentFull = () =>
		Boolean(
			latestState && latestState.participants.length >= PARTICIPANTS_LIMIT
		);

	const isAddingLocked = () =>
		Boolean(
			latestState &&
				(latestState.status !== "waiting" ||
					latestState.participants.length >= PARTICIPANTS_LIMIT)
		);

	const getAddBlockReason = () => {
		if (!latestState) return null;
		if (latestState.status !== "waiting") return "Tournament already started";
		if (latestState.participants.length >= PARTICIPANTS_LIMIT) {
			return `Tournament already has ${PARTICIPANTS_LIMIT} players`;
		}
		return null;
	};

	const ensureAddAllowed = (): boolean => {
		// Single point of check for consistent error messages.
		const reason = getAddBlockReason();
		if (!reason) return true;
		if (errorEl) errorEl.textContent = reason;
		return false;
	};

	async function loadAndRender() {
		try {
			const state = await getTournament();
			latestState = state;
			if (state.status !== "finished") {
				clearFinishedTournament();
			}
			// Snapshot is needed as a backup for results if finish request didn't update tournament in time.
			setTournamentSnapshot(state);
			renderTournamentState(state);
			syncGuestButton();
			renderSearchResults();
		} catch (err) {
			latestState = null;
			if (errorEl) {
				errorEl.textContent =
					err instanceof Error ? err.message : "Failed to load tournament";
			}
			syncGuestButton();
			renderSearchResults();
		}
	}

	const syncGuestButton = () => {
		if (!addGuestBtn || !nameInput) return;
		const trimmed = nameInput.value.trim();
		const addingLocked = isAddingLocked();

		nameInput.disabled = addingLocked;
		nameInput.title = addingLocked
			? isTournamentFull()
				? "Tournament is full"
				: "Tournament already started"
			: "";

		addGuestBtn.disabled =
			addInProgress || trimmed.length === 0 || addingLocked;
		addGuestBtn.title = addingLocked
			? isTournamentFull()
				? "Tournament is full"
				: "Tournament already started"
			: "";
		addGuestBtn.textContent = trimmed
			? `Add guest "${trimmed}"`
			: "Add guest";
	};

	const renderSearchResults = () => {
		if (!searchResultsEl) return;
		searchResultsEl.innerHTML = "";

		const addingLocked = isAddingLocked();
		if (addingLocked) {
			const p = document.createElement("p");
			p.className = "text-slate-400";
			p.textContent = isTournamentFull()
				? `Tournament already has ${PARTICIPANTS_LIMIT} players.`
				: "Tournament already in progress.";
			searchResultsEl.appendChild(p);
			return;
		}

		if (!lastQuery) {
			const p = document.createElement("p");
			p.className = "text-slate-400";
			p.textContent = "Start typing to search players or add as guest.";
			searchResultsEl.appendChild(p);
			return;
		}

		if (searchLoading) {
			const p = document.createElement("p");
			p.className = "text-slate-400";
			p.textContent = "Searching...";
			searchResultsEl.appendChild(p);
			return;
		}

		if (searchError) {
			const p = document.createElement("p");
			p.className = "text-red-400";
			p.textContent = searchError;
			searchResultsEl.appendChild(p);
			return;
		}

		if (searchResults.length === 0) {
			const p = document.createElement("p");
			p.className = "text-slate-400";
			p.textContent = "No players found. Add as guest?";
			searchResultsEl.appendChild(p);
			return;
		}

		searchResults.forEach((user) => {
			const row = document.createElement("div");
			row.className =
				"flex items-center gap-3 py-1 border-b border-slate-800 last:border-b-0";

			const textBox = document.createElement("div");
			textBox.className = "flex-1 min-w-0";

			const aliasEl = document.createElement("p");
			aliasEl.className = "text-slate-100 font-semibold truncate";
			aliasEl.textContent = getUserDisplayName(user);
			textBox.appendChild(aliasEl);

			const usernameEl = document.createElement("p");
			usernameEl.className = "text-xs text-slate-400 truncate";
			usernameEl.textContent = `@${user.username}`;
			textBox.appendChild(usernameEl);

			const statusNote = getInviteErrorForUser(user);
			const statusEl = document.createElement("p");
			statusEl.className = "text-xs truncate";
			statusEl.textContent = statusNote ? statusNote : "Online";
			statusEl.classList.add(
				statusNote ? "text-amber-400" : "text-emerald-400"
			);
			textBox.appendChild(statusEl);

			const btn = document.createElement("button");
			btn.type = "button";
			btn.textContent = "Add user";
			btn.className =
				"px-3 py-1 rounded bg-slate-800 hover:bg-slate-700 text-xs text-slate-100 disabled:opacity-40 disabled:cursor-not-allowed";
			btn.disabled = addInProgress || Boolean(statusNote) || addingLocked;
			if (addingLocked) {
				btn.title = "Tournament already started";
			}
			btn.addEventListener("click", () => {
				if (addInProgress) return;
				if (!ensureAddAllowed()) return;
				const err = getInviteErrorForUser(user);
				if (err) {
					if (errorEl) errorEl.textContent = err;
					return;
				}
				void handleAddUser(user);
			});

			row.appendChild(textBox);
			row.appendChild(btn);

			searchResultsEl.appendChild(row);
		});
	};

	async function performSearch(query: string): Promise<void> {
		const requestId = ++searchRequestId;
		searchLoading = true;
		searchError = "";
		renderSearchResults();

		try {
			const results = await searchUsers(query);
			if (requestId !== searchRequestId) return;
			searchResults = results;
		} catch (err) {
			if (requestId !== searchRequestId) return;
			searchResults = [];
			searchError =
				err instanceof Error ? err.message : "Failed to search players";
		} finally {
			if (requestId !== searchRequestId) return;
			searchLoading = false;
			renderSearchResults();
		}
	}

	function resetSearchUi(): void {
		lastQuery = "";
		searchResults = [];
		searchError = "";
		searchLoading = false;
		renderSearchResults();
		syncGuestButton();
	}

	async function addParticipantAndRender(
		alias: string,
		userId?: number
	): Promise<void> {
		if (errorEl) errorEl.textContent = "";
		addInProgress = true;
		syncGuestButton();
		renderSearchResults();

		try {
			const state = await addParticipant({ alias, userId });
			latestState = state;
			if (!userId) {
				const created = state.participants.find(
					(p) => p.isGuest && p.alias === alias
				);
				const createdId = created ? getParticipantId(created) : undefined;
				if (createdId) {
					rememberTournamentGuest(state.id, createdId);
				}
			}
			if (nameInput) nameInput.value = "";
			resetSearchUi();
			renderTournamentState(state);
		} catch (err) {
			if (errorEl) {
				errorEl.textContent =
					err instanceof Error ? err.message : "Failed to add player";
			}
		} finally {
			addInProgress = false;
			syncGuestButton();
			renderSearchResults();
		}
	}

	async function handleAddGuest(): Promise<void> {
		if (!nameInput) return;
		if (!ensureAddAllowed()) return;
		const alias = nameInput.value.trim();
		if (!alias) {
			if (errorEl) errorEl.textContent = "Name can't be empty";
			return;
		}
		await addParticipantAndRender(alias);
	}

	async function handleAddUser(user: FriendUser): Promise<void> {
		if (!ensureAddAllowed()) return;
		const inviteErr = getInviteErrorForUser(user);
		if (inviteErr) {
			if (errorEl) errorEl.textContent = inviteErr;
			return;
		}
		const alias = getUserDisplayName(user);
		await addParticipantAndRender(alias, user.id);
	}

	const storedFinished = getFinishedTournament<TournamentState>();
	if (storedFinished && storedFinished.status === "finished") {
		// Show final results only once after returning from match.
		latestState = storedFinished;
		renderTournamentState(storedFinished);
		syncGuestButton();
		renderSearchResults();
		clearFinishedTournament();
	} else {
		clearFinishedTournament();
		void loadAndRender();
	}

	if (addForm && nameInput) {
		addForm.addEventListener("submit", async (event) => {
			event.preventDefault();
			if (addInProgress) return;
			if (!ensureAddAllowed()) return;
			await handleAddGuest();
		});

		nameInput.addEventListener("input", () => {
			if (isAddingLocked()) {
				lastQuery = "";
				renderSearchResults();
				return;
			}
			if (errorEl) errorEl.textContent = "";
			lastQuery = nameInput.value.trim();
			syncGuestButton();

			if (lastQuery.length < 2) {
				searchResults = [];
				searchError = "";
				searchLoading = false;
				renderSearchResults();
				return;
			}

			void performSearch(lastQuery);
		});
	}

	renderSearchResults();
	syncGuestButton();

	if (resetBtn) {
		resetBtn.addEventListener("click", async () => {
			if (resetBtn.disabled) return;
			if (errorEl) errorEl.textContent = "";
			try {
				if (latestState) {
					resetTournamentGuests(latestState.id);
				}
				clearFinishedTournament();
				clearTournamentSnapshot();
				const state = await resetTournament();
				latestState = state;
				resetTournamentGuests(state.id);
				renderTournamentState(state);
				syncGuestButton();
				renderSearchResults();
			} catch (err) {
				if (errorEl) {
					errorEl.textContent =
						err instanceof Error ? err.message : "Failed to reset";
				}
			}
		});
	}

	if (prepareBtn) {
		prepareBtn.addEventListener("click", async () => {
			if (errorEl) errorEl.textContent = "";
			try {
				const state = await prepareTournament();
				latestState = state;
				renderTournamentState(state);
				syncGuestButton();
				renderSearchResults();
			} catch (err) {
				if (errorEl) {
					errorEl.textContent =
						err instanceof Error ? err.message : "Failed to prepare";
				}
			}
		});
	}

	if (startBtn) {
		startBtn.addEventListener("click", async () => {
			if (startBtn.disabled) return;
			if (errorEl) errorEl.textContent = "";
			try {
				const state = await startTournament();
				latestState = state;
				renderTournamentState(state);
				syncGuestButton();
				renderSearchResults();
			} catch (err) {
				if (errorEl) {
					errorEl.textContent =
						err instanceof Error ? err.message : "Failed to start";
				}
			}
		});
	}

	async function handleJoin(slot: "p1" | "p2"): Promise<void> {
		if (errorEl) errorEl.textContent = "";
		if (joinMsgEl) joinMsgEl.textContent = "";

		if (!latestState) {
			if (errorEl) errorEl.textContent = "No running match";
			return;
		}

		const state = latestState;
		const { match } = findCurrentMatch(state);
		if (!match || match.status !== "running") {
			if (errorEl) errorEl.textContent = "No running match";
			return;
		}

		const participant = slot === "p1" ? match.p1 : match.p2;
		const participantId = getParticipantId(participant);
		const p1Id = getParticipantId(match.p1);
		const p2Id = getParticipantId(match.p2);

		if (!participant || !participantId || !p1Id || !p2Id) {
			if (errorEl) errorEl.textContent = "No participant in this slot";
			return;
		}

		const meId = me ? String(me.id) : null;
		const canControlP1 = canControlParticipantOnDevice(
			state.id,
			meId,
			match.p1
		);
		const canControlP2 = canControlParticipantOnDevice(
			state.id,
			meId,
			match.p2
		);

		// Local mode is enabled only if both participants are available on the current device.
		const canLocalControl = canControlP1 && canControlP2;

		if (
			!canControlParticipantOnDevice(state.id, meId, participant) &&
			!canLocalControl
		) {
			if (errorEl) {
				errorEl.textContent = "Not available on this device";
			}
			return;
		}

		if (participant.isGuest && !canLocalControl) {
			if (!isTournamentGuestOnThisDevice(state.id, participantId)) {
				if (errorEl) {
					errorEl.textContent =
						"Guest can join only from the device that added them";
				}
				return;
			}
		}

		// Fix the current grid before entering the match to show results without extra requests.
		setTournamentSnapshot(state);
		setTournamentJoin({
			tournamentId: state.id,
			matchId: match.id,
			participantId: participantId,
			alias: participant.alias,
			isGuest: Boolean(participant.isGuest),
			p1: {
				id: String(p1Id),
				alias: getParticipantAlias(match.p1),
				isGuest: Boolean(match.p1?.isGuest),
			},
			p2: {
				id: String(p2Id),
				alias: getParticipantAlias(match.p2),
				isGuest: Boolean(match.p2?.isGuest),
			},
			localControl: canLocalControl,
		});

		if (joinMsgEl) {
			joinMsgEl.textContent = canLocalControl
				? "Opening local match..."
				: `Opening match for ${participant.alias}...`;
		}
		navigate("/game?mode=tournament");
	}

	if (joinP1Btn) {
		joinP1Btn.addEventListener("click", async () => {
			await handleJoin("p1");
		});
	}

	if (joinP2Btn) {
		joinP2Btn.addEventListener("click", async () => {
			await handleJoin("p2");
		});
	}
}
