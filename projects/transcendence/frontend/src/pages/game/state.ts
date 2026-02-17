import type { GameState, ServerGameState } from "../../gameTypes.js";
import { BALL_SIZE, GAME_H, GAME_W, PADDLE_H } from "./config.js";

export const initialGameState: GameState = {
  status: "waiting",
  ball: {
    x: GAME_W / 2 - BALL_SIZE / 2,
    y: GAME_H / 2 - BALL_SIZE / 2,
  },
  paddles: {
    p1: { y: GAME_H / 2 - PADDLE_H / 2 },
    p2: { y: GAME_H / 2 - PADDLE_H / 2 },
  },
  player1: {
    id: "p1",
    username: "Player 1",
    ready: false,
    score: 0,
  },
  player2: {
    id: "p2",
    username: "Player 2",
    ready: false,
    score: 0,
  },
  winner: null,
};

let currentState = initialGameState;
const subscribers = new Set<(state: GameState) => void>();

export function getGameState(): GameState {
  return currentState;
}

export function subscribeGameState(
  listener: (state: GameState) => void,
): () => void {
  subscribers.add(listener);
  listener(currentState);
  return () => {
    subscribers.delete(listener);
  };
}

export function setGameState(nextState: GameState): void {
  currentState = nextState;
  subscribers.forEach((listener) => listener(currentState));
}

export function resetGameState(): void {
  setGameState(initialGameState);
}

export function patchGameState(partial: Partial<GameState>): void {
  setGameState(mergeGameState(currentState, partial));
}

export function normalizeServerState(state: ServerGameState): GameState {
  if (state.winner && typeof state.winner === "object") {
    return { ...state, winner: state.winner.player };
  }
  return state as GameState;
}

function mergeGameState(prev: GameState, next: Partial<GameState>): GameState {
  const hasWinner = Object.prototype.hasOwnProperty.call(next, "winner");
  return {
    ...prev,
    ...next,
    status: next.status ?? prev.status,
    winner: hasWinner ? (next.winner ?? null) : prev.winner,
    ball: { ...prev.ball, ...(next.ball ?? {}) },
    paddles: {
      p1: { ...prev.paddles.p1, ...(next.paddles?.p1 ?? {}) },
      p2: { ...prev.paddles.p2, ...(next.paddles?.p2 ?? {}) },
    },
    player1: { ...prev.player1, ...(next.player1 ?? {}) },
    player2: { ...prev.player2, ...(next.player2 ?? {}) },
  };
}
