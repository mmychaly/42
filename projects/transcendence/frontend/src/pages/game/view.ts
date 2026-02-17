import { getCurrentUser } from "../../authStore.js";
import { ChatWidget } from "../chatWidget.js";
import type { GameState, GameStatus } from "../../gameTypes.js";
import {
	BALL_SIZE,
	GAME_H,
	GAME_W,
	PADDLE_H,
	PADDLE_W,
	STATUS_LABELS,
} from "./config.js";

export type GameRefs = {
	statusBadge: HTMLSpanElement;
	statusMessage: HTMLParagraphElement;
	waitingOverlay: HTMLDivElement;
	waitingP1Title: HTMLSpanElement;
	waitingP1Status: HTMLSpanElement;
	waitingP1Loader: HTMLSpanElement;
	waitingP2Title: HTMLSpanElement;
	waitingP2Status: HTMLSpanElement;
	waitingP2Loader: HTMLSpanElement;
	player1Name: HTMLSpanElement;
	player1Ready: HTMLSpanElement;
	player2Name: HTMLSpanElement;
	player2Ready: HTMLSpanElement;
	score1: HTMLSpanElement;
	score2: HTMLSpanElement;
	paddle1: HTMLDivElement;
	paddle2: HTMLDivElement;
	ball: HTMLDivElement;
	readyButton: HTMLButtonElement;
	exitButton: HTMLButtonElement;
	connectionNote: HTMLParagraphElement;
	finishedOverlay: HTMLDivElement;
	winner: HTMLSpanElement;
	continueButton: HTMLButtonElement;
};

export type GameViewState = {
	hasRoom: boolean;
	allowReadyBeforeRoom?: boolean;
};

export function renderGameShell(content: string): string {
	return `
    <section id="game-page" class="p-4 max-w-5xl mx-auto">
      ${content}
    </section>
    ${getCurrentUser() ? ChatWidget() : ""}
  `;
}

export function renderModeSelection(): string {
	return `
    <div class="flex flex-col gap-6">
      <div>
        <h2 class="text-2xl font-bold">Choose mode</h2>
      </div>
      <div class="grid gap-4 sm:grid-cols-2">
        <button
          id="game-mode-online"
          class="group rounded-xl border border-emerald-500/50 bg-emerald-500/10 p-5 text-left transition hover:bg-emerald-500/20"
        >
          <p class="text-base font-semibold text-emerald-100">Online 1v1</p>
          <p class="mt-2 text-sm text-emerald-200/80">
            Two devices, one match on the server.
          </p>
        </button>
        <button
          id="game-mode-local"
          class="group rounded-xl border border-slate-600 bg-slate-900/40 p-5 text-left transition hover:bg-slate-800/40"
        >
          <p class="text-base font-semibold text-slate-100">Local</p>
          <p class="mt-2 text-sm text-slate-300/70">
            One device, two players, no network.
          </p>
        </button>
      </div>
    </div>
  `;
}

export function renderLocalLobby(options: {
	localEnabled: boolean;
}): string {
	const disabledAttr = options.localEnabled ? "" : "disabled";
	const disabledClass = options.localEnabled
		? ""
		: "opacity-50 cursor-not-allowed";
	const noteClass = options.localEnabled ? "hidden" : "text-amber-200";

	return `
    <div class="flex flex-col gap-6">
      <div>
        <h2 class="text-2xl font-bold">Local lobby</h2>
        <p class="text-sm text-slate-400">
          Pick names for both players. Controls: left = W/S, right = Arrow keys.
        </p>
      </div>
      <div class="grid gap-4 sm:grid-cols-2">
        <label class="flex flex-col gap-2 text-sm">
          <span class="text-slate-300">Player 1</span>
          <input
            id="local-player1"
            class="rounded border border-slate-700 bg-slate-900/60 px-3 py-2 text-slate-100"
          />
        </label>
        <label class="flex flex-col gap-2 text-sm">
          <span class="text-slate-300">Player 2</span>
          <input
            id="local-player2"
            class="rounded border border-slate-700 bg-slate-900/60 px-3 py-2 text-slate-100"
          />
        </label>
      </div>
      <p
        id="local-error"
        class="text-sm text-red-400 min-h-[1.2rem]"
      ></p>
      <div class="flex flex-wrap items-center gap-3">
        <button
          id="local-start"
          class="px-4 py-2 rounded bg-emerald-600 hover:bg-emerald-500 text-white text-sm ${disabledClass}"
          ${disabledAttr}
        >
          Start local match
        </button>
        <button
          id="local-back"
          class="px-4 py-2 text-sm rounded border border-slate-600 text-slate-200 hover:bg-slate-800/40"
        >
          Back
        </button>
        <span id="local-disabled-note" class="text-xs ${noteClass}">
          Local backend is not enabled yet.
        </span>
      </div>
    </div>
  `;
}

export function renderGameContent(): string {
	const statusClass = getStatusBadgeClass("waiting");
	const readyClass = getReadyBadgeClass(false);
	const initialPaddleY = GAME_H / 2 - PADDLE_H / 2;
	const initialBallX = GAME_W / 2 - BALL_SIZE / 2;
	const initialBallY = GAME_H / 2 - BALL_SIZE / 2;

	return `
    <div class="flex flex-col gap-2 sm:flex-row sm:items-center sm:justify-between">
      <div>
        <h2 id="game-title" class="text-2xl font-bold">Game 1v1</h2>
        <p id="game-status-message" class="text-sm text-slate-400">
          Waiting for players to get ready.
        </p>
      </div>
      <span id="game-status" class="${statusClass}">
        ${getStatusLabel("waiting")}
      </span>
    </div>

    <div class="mt-4 grid gap-3 sm:grid-cols-2 text-sm">
      <div class="flex items-center gap-2">
        <span class="text-slate-400">Player 1</span>
        <span id="game-player1-name" class="font-semibold">Player 1</span>
        <span id="game-player1-ready" class="${readyClass}">
          ${getReadyLabel(false)}
        </span>
      </div>
      <div class="flex items-center gap-2 sm:justify-end">
        <span class="text-slate-400">Player 2</span>
        <span id="game-player2-name" class="font-semibold">Player 2</span>
        <span id="game-player2-ready" class="${readyClass}">
          ${getReadyLabel(false)}
        </span>
      </div>
    </div>

    <div
      class="relative mx-auto mt-4 border border-slate-600 rounded-lg bg-slate-950/50 overflow-hidden"
      style="width: ${GAME_W}px; height: ${GAME_H}px;"
    >
      <div
        id="game-waiting-overlay"
        class="absolute inset-0 grid grid-cols-2 text-slate-200 text-sm"
      >
        <div
          class="flex items-center justify-center bg-slate-900/60 backdrop-blur-sm transition-opacity duration-300"
        >
          <div class="flex flex-col items-center gap-1 text-center">
            <span id="game-waiting-p1-title" class="font-semibold">P1 connected</span>
            <span id="game-waiting-p1-status" class="text-xs text-slate-300">
              Waiting for ready<span id="game-waiting-p1-loader" class="ml-1 animate-pulse">...</span>
            </span>
          </div>
        </div>
        <div
          class="flex items-center justify-center bg-slate-900/60 backdrop-blur-sm transition-opacity duration-300"
        >
          <div class="flex flex-col items-center gap-1 text-center">
            <span id="game-waiting-p2-title" class="font-semibold">P2 connected</span>
            <span id="game-waiting-p2-status" class="text-xs text-slate-300">
              Waiting for ready<span id="game-waiting-p2-loader" class="ml-1 animate-pulse">...</span>
            </span>
          </div>
        </div>
      </div>
      <div
        id="game-finished-overlay"
        class="absolute inset-0 bg-slate-900/80 backdrop-blur-sm hidden flex items-center justify-center text-center"
      >
        <div>
          <p class="text-lg font-semibold">Match finished</p>
          <p class="text-sm text-slate-300">
            Winner: <span id="game-winner">-</span>
          </p>
          <button
            id="game-continue"
            class="mt-3 px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white text-sm disabled:opacity-40 disabled:cursor-not-allowed"
            disabled
          >
            Continue
          </button>
        </div>
      </div>
      <div
        id="game-paddle-p1"
        class="absolute left-0 top-0 bg-slate-100 rounded"
        style="width: ${PADDLE_W}px; height: ${PADDLE_H}px; transform: translateY(${initialPaddleY}px);"
      ></div>
      <div
        id="game-paddle-p2"
        class="absolute right-0 top-0 bg-slate-100 rounded"
        style="width: ${PADDLE_W}px; height: ${PADDLE_H}px; transform: translateY(${initialPaddleY}px);"
      ></div>
      <div
        id="game-ball"
        class="absolute left-0 top-0 bg-yellow-400 rounded-full"
        style="width: ${BALL_SIZE}px; height: ${BALL_SIZE}px; transform: translate(${initialBallX}px, ${initialBallY}px);"
      ></div>
    </div>

    <div class="mt-4 flex items-center justify-center gap-6 text-lg">
      <span id="game-score-p1" class="font-bold">0</span>
      <span class="text-slate-400">-</span>
      <span id="game-score-p2" class="font-bold">0</span>
    </div>

    <div class="mt-4 flex items-center justify-center gap-3">
      <button
        id="game-ready"
        class="px-4 py-2 rounded bg-emerald-600 hover:bg-emerald-500 text-white text-sm disabled:opacity-40 disabled:cursor-not-allowed"
      >
        Ready
      </button>
      <button
        id="game-exit"
        class="px-3 py-2 rounded border border-slate-600 text-sm text-slate-200 hover:bg-slate-800/40 hidden"
      >
        Back
      </button>
    </div>
    <p
      id="game-connection-note"
      class="mt-2 text-center text-xs text-amber-200 min-h-[1.1rem]"
    ></p>
    <p class="mt-3 text-center text-xs text-slate-500">
      Input: W/S or ArrowUp/ArrowDown.
    </p>
  `;
}

export function getGameRefs(container: HTMLElement): GameRefs | null {
	const statusBadge = container.querySelector<HTMLSpanElement>("#game-status");
	const statusMessage =
		container.querySelector<HTMLParagraphElement>("#game-status-message");
	const waitingOverlay =
		container.querySelector<HTMLDivElement>("#game-waiting-overlay");
	const waitingP1Title =
		container.querySelector<HTMLSpanElement>("#game-waiting-p1-title");
	const waitingP1Status =
		container.querySelector<HTMLSpanElement>("#game-waiting-p1-status");
	const waitingP1Loader =
		container.querySelector<HTMLSpanElement>("#game-waiting-p1-loader");
	const waitingP2Title =
		container.querySelector<HTMLSpanElement>("#game-waiting-p2-title");
	const waitingP2Status =
		container.querySelector<HTMLSpanElement>("#game-waiting-p2-status");
	const waitingP2Loader =
		container.querySelector<HTMLSpanElement>("#game-waiting-p2-loader");
	const player1Name =
		container.querySelector<HTMLSpanElement>("#game-player1-name");
	const player1Ready =
		container.querySelector<HTMLSpanElement>("#game-player1-ready");
	const player2Name =
		container.querySelector<HTMLSpanElement>("#game-player2-name");
	const player2Ready =
		container.querySelector<HTMLSpanElement>("#game-player2-ready");
	const score1 = container.querySelector<HTMLSpanElement>("#game-score-p1");
	const score2 = container.querySelector<HTMLSpanElement>("#game-score-p2");
	const paddle1 = container.querySelector<HTMLDivElement>("#game-paddle-p1");
	const paddle2 = container.querySelector<HTMLDivElement>("#game-paddle-p2");
	const ball = container.querySelector<HTMLDivElement>("#game-ball");
	const readyButton = container.querySelector<HTMLButtonElement>("#game-ready");
	const exitButton = container.querySelector<HTMLButtonElement>("#game-exit");
	const connectionNote = container.querySelector<HTMLParagraphElement>(
		"#game-connection-note"
	);
	const finishedOverlay = container.querySelector<HTMLDivElement>(
		"#game-finished-overlay"
	);
	const winner = container.querySelector<HTMLSpanElement>("#game-winner");
	const continueButton =
		container.querySelector<HTMLButtonElement>("#game-continue");

	if (
		!statusBadge ||
		!statusMessage ||
		!waitingOverlay ||
		!waitingP1Title ||
		!waitingP1Status ||
		!waitingP1Loader ||
		!waitingP2Title ||
		!waitingP2Status ||
		!waitingP2Loader ||
		!player1Name ||
		!player1Ready ||
		!player2Name ||
		!player2Ready ||
		!score1 ||
		!score2 ||
		!paddle1 ||
		!paddle2 ||
		!ball ||
		!readyButton ||
		!exitButton ||
		!connectionNote ||
		!finishedOverlay ||
		!winner ||
		!continueButton
	) {
		return null;
	}

	return {
		statusBadge,
		statusMessage,
		waitingOverlay,
		waitingP1Title,
		waitingP1Status,
		waitingP1Loader,
		waitingP2Title,
		waitingP2Status,
		waitingP2Loader,
		player1Name,
		player1Ready,
		player2Name,
		player2Ready,
		score1,
		score2,
		paddle1,
		paddle2,
		ball,
		readyButton,
		exitButton,
		connectionNote,
		finishedOverlay,
		winner,
		continueButton,
	};
}

export function updateGameUI(
	refs: GameRefs,
	state: GameState,
	viewState: GameViewState
): void {
	refs.statusBadge.textContent = getStatusLabel(state.status);
	refs.statusBadge.className = getStatusBadgeClass(state.status);
	refs.statusMessage.textContent = getStatusMessage(state);

	refs.player1Name.textContent = getPlayerLabel(state.player1, "Player 1");
	refs.player2Name.textContent = getPlayerLabel(state.player2, "Player 2");

	refs.player1Ready.textContent = getReadyLabel(state.player1.ready);
	refs.player1Ready.className = getReadyBadgeClass(state.player1.ready);
	refs.player2Ready.textContent = getReadyLabel(state.player2.ready);
	refs.player2Ready.className = getReadyBadgeClass(state.player2.ready);

	refs.score1.textContent = String(state.player1.score);
	refs.score2.textContent = String(state.player2.score);

	const paddle1Y = clamp(state.paddles.p1.y, 0, GAME_H - PADDLE_H);
	const paddle2Y = clamp(state.paddles.p2.y, 0, GAME_H - PADDLE_H);
	refs.paddle1.style.transform = `translateY(${paddle1Y}px)`;
	refs.paddle2.style.transform = `translateY(${paddle2Y}px)`;

	const ballX = clamp(state.ball.x, 0, GAME_W - BALL_SIZE);
	const ballY = clamp(state.ball.y, 0, GAME_H - BALL_SIZE);
	refs.ball.style.transform = `translate(${ballX}px, ${ballY}px)`;

	// In a tournament, one can press Ready before the room is created (queueing).
	const allowReadyBeforeRoom = Boolean(viewState.allowReadyBeforeRoom);
	refs.readyButton.disabled =
		state.status !== "waiting" || (!viewState.hasRoom && !allowReadyBeforeRoom);

	refs.winner.textContent = getWinnerLabel(state);
	refs.finishedOverlay.classList.toggle("hidden", state.status !== "finished");
	refs.continueButton.disabled = state.status !== "finished";

	updateWaitingOverlay(refs, state, viewState.hasRoom);
}

function updateWaitingOverlay(
	refs: GameRefs,
	state: GameState,
	hasRoom: boolean
): void {
	const showWaiting = state.status === "waiting";
	refs.waitingOverlay.classList.toggle("hidden", !showWaiting);

	const p1Title = !hasRoom
		? "You connected"
		: state.player1.ready
			? "P1 ready"
			: "P1 connected";
	const p2Title = !hasRoom
		? "Waiting for opponent"
		: state.player2.ready
			? "P2 ready"
			: "P2 connected";

	refs.waitingP1Title.textContent = p1Title;
	refs.waitingP2Title.textContent = p2Title;

	const p1Waiting = hasRoom && !state.player1.ready;
	const p2Waiting = hasRoom && !state.player2.ready;

	refs.waitingP1Status.classList.toggle("hidden", !p1Waiting);
	refs.waitingP1Loader.classList.toggle("hidden", !p1Waiting);
	refs.waitingP2Status.classList.toggle("hidden", !p2Waiting);
	refs.waitingP2Loader.classList.toggle("hidden", !p2Waiting);
}

function getStatusLabel(status: GameStatus): string {
	return STATUS_LABELS[status];
}

function getPlayerLabel(
	player: GameState["player1"],
	fallback: string
): string {
	const name = player.username?.trim();
	return name ? name : fallback;
}

function getWinnerLabel(state: GameState): string {
	if (!state.winner) return "-";
	const player = getPlayerBySide(state, state.winner);
	return getPlayerLabel(player, state.winner === "p1" ? "Player 1" : "Player 2");
}

function getStatusMessage(state: GameState): string {
	if (state.status === "waiting") {
		return "Waiting for players to get ready.";
	}
	if (state.status === "running") {
		return "Match in progress.";
	}
	if (state.status === "finished") {
		const winner = getWinnerLabel(state);
		return winner === "-"
			? "Match finished."
			: `Match finished. Winner: ${winner}.`;
	}
	return "Status unknown.";
}

function getReadyLabel(isReady: boolean): string {
	return isReady ? "Ready" : "Not ready";
}

function getReadyBadgeClass(isReady: boolean): string {
	const base = "text-xs px-2 py-0.5 rounded-full border transition-colors";
	const variant = isReady
		? "border-emerald-500/50 bg-emerald-500/20 text-emerald-200"
		: "border-slate-600/60 bg-slate-800/70 text-slate-300";
	return `${base} ${variant}`;
}

function getStatusBadgeClass(status: GameStatus): string {
	const base =
		"px-2 py-1 text-xs font-semibold rounded-full border transition-colors";
	const variant = {
		waiting: "border-amber-500/50 bg-amber-500/20 text-amber-200",
		running: "border-emerald-500/50 bg-emerald-500/20 text-emerald-200",
		finished: "border-slate-500/50 bg-slate-600/20 text-slate-200",
	}[status];
	return `${base} ${variant}`;
}

function getPlayerBySide(
	state: GameState,
	side: "p1" | "p2"
): GameState["player1"] {
	return side === "p1" ? state.player1 : state.player2;
}

function clamp(value: number, min: number, max: number): number {
	return Math.max(min, Math.min(max, value));
}
