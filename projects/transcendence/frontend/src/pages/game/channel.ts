import type { GameServerMessage, GameSocketClient } from "../../gameSocket.js";
import type { GameState, ServerGameState } from "../../gameTypes.js";
import {
  getGameState,
  normalizeServerState,
  patchGameState,
} from "./state.js";

export type GameMode = "online" | "local" | "tournament" | null;
export type LocalPlayerIds = {
  p1: number | string | null;
  p2: number | string | null;
};

let selectedMode: GameMode = null;
let hasRoom = false;
let activeClient: GameSocketClient | null = null;
let removeInputListeners: (() => void) | null = null;
let localPlayerIds: LocalPlayerIds = { p1: null, p2: null };

export function getSelectedMode(): GameMode {
  return selectedMode;
}

export function setSelectedMode(mode: GameMode): void {
  selectedMode = mode;
}

export function getHasRoom(): boolean {
  return hasRoom;
}

export function setHasRoom(value: boolean): void {
  hasRoom = value;
}

export function getActiveClient(): GameSocketClient | null {
  return activeClient;
}

export function setActiveClient(client: GameSocketClient | null): void {
  activeClient = client;
}

export function setInputCleanup(cleanup: (() => void) | null): void {
  removeInputListeners = cleanup;
}

export function cleanupConnection(): void {
  if (removeInputListeners) {
    removeInputListeners();
    removeInputListeners = null;
  }
  if (activeClient) {
    activeClient.disconnect();
    activeClient = null;
  }
}

export function getLocalPlayerIds(): LocalPlayerIds {
  return localPlayerIds;
}

export function setLocalPlayerIds(ids: LocalPlayerIds): void {
  localPlayerIds = ids;
}

export function resetLocalPlayerIds(): void {
  localPlayerIds = { p1: null, p2: null };
}

export function handleServerMessage(
  client: GameSocketClient,
  message: GameServerMessage,
): void {
  const applyRoomState = (state: ServerGameState) => {
    // Фиксируем комнату и сохраняем актуальные id игроков для local input.
    setHasRoom(true);
    patchGameState(normalizeServerState(state));
    setLocalPlayerIds({
      p1: state.player1.id,
      p2: state.player2.id,
    });
  };

  switch (message.type) {
    case "authenticated":
      if (getSelectedMode() === "online") {
        client.sendJoinQueue();
      }
      break;
    case "tournamentMatchReady":
    case "roomCreated":
      // Турнирный матч и обычный матч отдают одинаковый payload состояния.
      applyRoomState(message.data);
      break;
    case "playerReady": {
      const current = getGameState();
      // Обновляем только одного игрока, чтобы не потерять остальные поля состояния.
      const target =
        message.data.playerId === current.player1.id ? "player1" : "player2";
      const updated = {
        [target]: {
          ...current[target],
          ready: true,
        },
      } as Partial<typeof current>;
      patchGameState(updated);
      break;
    }
    case "playerDisconnected": {
      const current = getGameState();
      const winner = message.data.winner;
      const scorePatch =
        winner === "p1"
          ? {
              player1: {
                ...current.player1,
                score: Math.max(current.player1.score, 11),
              },
            }
          : {
              player2: {
                ...current.player2,
                score: Math.max(current.player2.score, 11),
              },
            };
      patchGameState({
        ...scorePatch,
        status: "finished",
        winner,
      });
      break;
    }
    case "gameStarted":
    case "gameState":
    case "gameFinished":
      patchGameState(normalizeServerState(message.data));
      break;
    case "error":
      console.warn("Game WS error:", message.message);
      break;
    default:
      break;
  }
}
