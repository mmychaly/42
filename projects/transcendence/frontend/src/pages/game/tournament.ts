import { createGameSocketClient } from "../../gameSocket.js";
import { handleServerMessage } from "./channel.js";
import {
  cleanupConnection,
  getActiveClient,
  getHasRoom,
  resetLocalPlayerIds,
  setActiveClient,
  setHasRoom,
  setInputCleanup,
} from "./channel.js";
import {
  getTournamentWsUrl,
  mapInputKey,
  mapLocalInput,
} from "../../utils.js";
import { getGameRefs, updateGameUI } from "./view.js";
import {
  normalizeServerState,
  patchGameState,
  resetGameState,
  subscribeGameState,
} from "./state.js";
import { finishTournamentMatch } from "../../tournamentApi.js";
import type { TournamentJoinInfo } from "../../tournamentSession.js";
import {
  setFinishedTournament,
  clearFinishedTournament,
  getTournamentSnapshot,
  setTournamentSnapshot,
} from "../../tournamentSession.js";
import type { TournamentState } from "../../tournamentTypes.js";

export function mountTournamentGame(
  container: HTMLElement,
  joinInfo: TournamentJoinInfo,
  onContinue: () => void,
): () => void {
  const refs = getGameRefs(container);
  if (!refs) return () => undefined;

  cleanupConnection();
  resetGameState();
  resetLocalPlayerIds();
  setHasRoom(false);
  const localControl = Boolean(joinInfo.localControl);

  // В турнирном режиме кнопка возвращает в лобби турнира.
  const titleEl = container.querySelector<HTMLElement>("#game-title");
  if (titleEl) {
    titleEl.textContent = "Tournament match";
  }

  refs.continueButton.textContent = "Back to tournament";
  refs.exitButton.classList.add("hidden");
  refs.connectionNote.textContent = "";
  patchGameState({
    player1: {
      id: joinInfo.p1.id,
      username: joinInfo.p1.alias,
      ready: false,
      score: 0,
    },
    player2: {
      id: joinInfo.p2.id,
      username: joinInfo.p2.alias,
      ready: false,
      score: 0,
    },
  });

  const unsubscribe = subscribeGameState((state) => {
    updateGameUI(refs, state, {
      hasRoom: getHasRoom(),
      allowReadyBeforeRoom: true,
    });
  });

  // Ready может быть нажато до появления комнаты, держим флаг очереди.
  let pendingReady = false;
  let waitingTimer: ReturnType<typeof setTimeout> | null = null;

  const clearWaitingTimer = () => {
    if (waitingTimer) {
      clearTimeout(waitingTimer);
      waitingTimer = null;
    }
  };

  const setNote = (text: string) => {
    refs.connectionNote.textContent = text;
  };

  const sendReady = (client: ReturnType<typeof getActiveClient>) => {
    if (!client) return;
    if (localControl) {
      // В локальном режиме подтверждаем готовность за обоих игроков.
      client.sendReadyForParticipant(joinInfo.p1.id);
      client.sendReadyForParticipant(joinInfo.p2.id);
      return;
    }
    client.sendReadyForParticipant(joinInfo.participantId);
  };

  startTournamentGame(joinInfo, {
    onWaiting: () => {
      setNote("Waiting for opponent to join...");
      if (!waitingTimer) {
        waitingTimer = setTimeout(() => {
          setNote("Still waiting. You can go back and rejoin if needed.");
        }, 10_000);
      }
    },
    onRoomReady: () => {
      clearWaitingTimer();
      setNote("");
      if (pendingReady) {
        pendingReady = false;
        sendReady(getActiveClient());
      }
    },
    onError: (message) => {
      clearWaitingTimer();
      setNote(message);
    },
  });

  const readyHandler = () => {
    const client = getActiveClient();
    if (!client) return;
    if (!getHasRoom()) {
      // Не теряем клик: сохраняем флаг и отправим ready после roomCreated.
      pendingReady = true;
      setNote("Ready queued. Waiting for opponent...");
      return;
    }
    sendReady(client);
  };

  const handleExit = () => {
    cleanupConnection();
    clearWaitingTimer();
    onContinue();
  };

  refs.readyButton.addEventListener("click", readyHandler);
  refs.continueButton.addEventListener("click", handleExit);
  // Кнопка Back скрыта в турнире, оставляем только Continue.

  return () => {
    refs.readyButton.removeEventListener("click", readyHandler);
    refs.continueButton.removeEventListener("click", handleExit);
    clearWaitingTimer();
    unsubscribe();
    cleanupConnection();
  };
}

function startTournamentGame(
  joinInfo: TournamentJoinInfo,
  handlers: {
    onWaiting: () => void;
    onRoomReady: () => void;
    onError: (message: string) => void;
  },
): void {
  cleanupConnection();

  const client = createGameSocketClient();
  setActiveClient(client);

  const localControl = Boolean(joinInfo.localControl);
  const expectedIds = new Set<string>();
  const joinSent = new Set<string>();
  let finishSent = false;

  client.onOpen(() => {
    if (localControl) {
      // Локальный режим: одним сокетом авторизуем обоих участников.
      [joinInfo.p1, joinInfo.p2].forEach((p) => {
        expectedIds.add(String(p.id));
        client.sendAuth({
          participantId: p.id,
          alias: p.isGuest ? p.alias : undefined,
          isGuest: p.isGuest,
        });
      });
      return;
    }
    expectedIds.add(String(joinInfo.participantId));
    client.sendAuth({
      participantId: joinInfo.participantId,
      alias: joinInfo.isGuest ? joinInfo.alias : undefined,
      isGuest: joinInfo.isGuest,
    });
  });

  const onKeyDown = (event: KeyboardEvent) => {
    if (event.repeat) return;
    if (localControl) {
      const payload = mapLocalInput(event, "keydown", {
        p1: joinInfo.p1.id,
        p2: joinInfo.p2.id,
      });
      if (!payload) return;
      event.preventDefault();
      client.sendInputForParticipant(payload.playerId, payload.input);
      return;
    }
    const key = mapInputKey(event);
    if (!key) return;
    event.preventDefault();
    client.sendInputForParticipant(joinInfo.participantId, {
      key,
      type: "keydown",
    });
  };

  const onKeyUp = (event: KeyboardEvent) => {
    if (localControl) {
      const payload = mapLocalInput(event, "keyup", {
        p1: joinInfo.p1.id,
        p2: joinInfo.p2.id,
      });
      if (!payload) return;
      event.preventDefault();
      client.sendInputForParticipant(payload.playerId, payload.input);
      return;
    }
    const key = mapInputKey(event);
    if (!key) return;
    event.preventDefault();
    client.sendInputForParticipant(joinInfo.participantId, {
      key,
      type: "keyup",
    });
  };

  window.addEventListener("keydown", onKeyDown);
  window.addEventListener("keyup", onKeyUp);
  setInputCleanup(() => {
    window.removeEventListener("keydown", onKeyDown);
    window.removeEventListener("keyup", onKeyUp);
  });

  client.onMessage((message) => {
    if (message.type === "waitingOpponnent") {
      handlers.onWaiting();
    }

    if (
      message.type === "roomCreated" ||
      message.type === "tournamentMatchReady"
    ) {
      handlers.onRoomReady();
    }

    if (message.type === "error") {
      handlers.onError(message.message);
    }

    if (message.type === "authenticated") {
      const id = String(message.data.id);
      if (expectedIds.has(id) && !joinSent.has(id)) {
        joinSent.add(id);
        // Присоединяемся к конкретному матчу турнира.
        client.sendJoinMatch(id, joinInfo.matchId);
      }
    }

    handleServerMessage(client, message);

    if (message.type === "gameFinished") {
      if (finishSent) return;
      finishSent = true;
      const normalized = normalizeServerState(message.data);
      if (normalized.winner) {
        const winner = normalized.winner;
        // Завершаем матч на бэке и получаем обновленный турнир.
        void finishTournamentMatch(joinInfo.matchId, winner)
          .then((state) => {
            if (state.status === "finished") {
              setFinishedTournament(state);
            } else {
              clearFinishedTournament();
            }
          })
          .catch((error) => {
            const fallback = applySnapshotFinish(joinInfo, winner);
            if (fallback) {
              setFinishedTournament(fallback);
            }
            console.warn("Failed to finish tournament match", error);
          });
      }
      // Закрываем сокет после финиша, чтобы игрок мог зайти в следующий матч.
      setTimeout(() => {
        cleanupConnection();
      }, 800);
    }
  });

  client.connect(getTournamentWsUrl(joinInfo.tournamentId));
}


function applySnapshotFinish(
  joinInfo: TournamentJoinInfo,
  winner: "p1" | "p2",
): TournamentState | null {
  // Используем локальный снимок, если finish-запрос не вернул обновленный турнир.
  const snapshot = getTournamentSnapshot<TournamentState>();
  if (!snapshot) return null;
  const match = snapshot.matches.find(
    (m) => String(m.id) === String(joinInfo.matchId),
  );
  if (!match) return null;

  const winnerId = winner === "p1" ? joinInfo.p1.id : joinInfo.p2.id;
  const loserId = winner === "p1" ? joinInfo.p2.id : joinInfo.p1.id;

  match.status = "finished";
  match.winnerId = winnerId;
  match.loserId = loserId;

  const allFinished = snapshot.matches.every((m) => m.status === "finished");
  if (!allFinished) {
    setTournamentSnapshot(snapshot);
    return null;
  }

  snapshot.status = "finished";
  snapshot.currentMatchIndex = null;
  setTournamentSnapshot(snapshot);
  return snapshot;
}
