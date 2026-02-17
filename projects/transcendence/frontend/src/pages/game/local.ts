import { createGameSocketClient } from "../../gameSocket.js";
import { getCurrentUser } from "../../authStore.js";
import { handleServerMessage } from "./channel.js";
import {
  cleanupConnection,
  getActiveClient,
  getHasRoom,
  getLocalPlayerIds,
  resetLocalPlayerIds,
  setActiveClient,
  setHasRoom,
  setInputCleanup,
} from "./channel.js";
import { getLocalWsUrl, mapLocalInput } from "../../utils.js";
import { getGameRefs, updateGameUI } from "./view.js";
import { resetGameState, subscribeGameState } from "./state.js";

export const LOCAL_ENABLED = true;

export type LocalLobbyData = {
  player1Name: string;
  player2Name: string;
};

const LOCAL_NAME_MIN_LEN = 2;
const LOCAL_NAME_MAX_LEN = 20;

function sanitizeLocalName(value: string): string {
  return value.replace(/[<>'"]/g, "").trim().slice(0, LOCAL_NAME_MAX_LEN);
}

export function setupLocalLobby(
  container: HTMLElement,
  defaults: LocalLobbyData,
  onBack: () => void,
  onStart: (data: LocalLobbyData) => void,
): () => void {
  const backButton = container.querySelector<HTMLButtonElement>("#local-back");
  const startButton =
    container.querySelector<HTMLButtonElement>("#local-start");
  const player1Input =
    container.querySelector<HTMLInputElement>("#local-player1");
  const player2Input =
    container.querySelector<HTMLInputElement>("#local-player2");
  const errorEl = container.querySelector<HTMLParagraphElement>("#local-error");

  if (
    !backButton ||
    !startButton ||
    !player1Input ||
    !player2Input ||
    !errorEl
  ) {
    return () => undefined;
  }

  player1Input.value = sanitizeLocalName(defaults.player1Name);
  player2Input.value = sanitizeLocalName(defaults.player2Name);

  const setError = (message: string) => {
    errorEl.textContent = message;
  };

  const handleBack = () => {
	onBack();
  };

  const handleStart = () => {
    if (!LOCAL_ENABLED) return;
    const rawPlayer1 = player1Input.value;
    const rawPlayer2 = player2Input.value;
    const player1Name = sanitizeLocalName(rawPlayer1);
    const player2Name = sanitizeLocalName(rawPlayer2);

    if (player1Name !== rawPlayer1) {
      player1Input.value = player1Name;
    }
    if (player2Name !== rawPlayer2) {
      player2Input.value = player2Name;
    }

    if (
      player1Name.length < LOCAL_NAME_MIN_LEN ||
      player2Name.length < LOCAL_NAME_MIN_LEN
    ) {
      setError("Username must be least 2 chars");
      return;
    }

    setError("");
    onStart({ player1Name, player2Name });
  };

  const handleInput = () => {
    if (errorEl.textContent) {
      setError("");
    }
  };

  backButton.addEventListener("click", handleBack);
  startButton.addEventListener("click", handleStart);
  player1Input.addEventListener("input", handleInput);
  player2Input.addEventListener("input", handleInput);

  return () => {
    backButton.removeEventListener("click", handleBack);
    startButton.removeEventListener("click", handleStart);
    player1Input.removeEventListener("input", handleInput);
    player2Input.removeEventListener("input", handleInput);
  };
}

export function mountLocalGame(
  container: HTMLElement,
  lobbyData: LocalLobbyData,
  onContinue: () => void,
): () => void {
  const refs = getGameRefs(container);
  if (!refs) return () => undefined;

  cleanupConnection();
  resetGameState();
  resetLocalPlayerIds();
  setHasRoom(false);

  const unsubscribe = subscribeGameState((state) => {
	updateGameUI(refs, state, { hasRoom: getHasRoom() });
  });

  const setNote = (text: string) => {
    refs.connectionNote.textContent = text;
  };

  startLocalGame(lobbyData, setNote);

  const readyHandler = () => {
	const client = getActiveClient();
	if (!client) return;
	if (!getHasRoom()) {
	  return;
	}
	const ids = getLocalPlayerIds();
	// В локальном режиме отправляем ready сразу за обоих участников.
	if (ids.p1 && ids.p2) {
	  client.sendReadyForLocalPlayer(ids.p1);
	  client.sendReadyForLocalPlayer(ids.p2);
	} else {
	  client.sendReady();
	}
  };

  refs.readyButton.addEventListener("click", readyHandler);
  refs.continueButton.addEventListener("click", onContinue);

  return () => {
    refs.readyButton.removeEventListener("click", readyHandler);
    refs.continueButton.removeEventListener("click", onContinue);
    unsubscribe();
    cleanupConnection();
  };
}

function startLocalGame(
  lobbyData: LocalLobbyData,
  setNote: (text: string) => void,
): void {
  cleanupConnection();

  const client = createGameSocketClient();
  setActiveClient(client);

  client.onOpen(() => {
	const user = getCurrentUser();
	if (user) {
	  // Авторизованный игрок + гость на одном устройстве.
	  client.sendAuth({ guestUsername: lobbyData.player2Name });
	  return;
	}
	// Два гостя на одном устройстве.
	client.sendAuth({
	  player1Username: lobbyData.player1Name,
	  player2Username: lobbyData.player2Name,
	});
  });

  const onKeyDown = (event: KeyboardEvent) => {
	if (event.repeat) return;
	const payload = mapLocalInput(event, "keydown", getLocalPlayerIds());
	if (!payload) return;
	event.preventDefault();
	client.sendInputForLocalPlayer(payload.playerId, payload.input);
  };

  const onKeyUp = (event: KeyboardEvent) => {
	const payload = mapLocalInput(event, "keyup", getLocalPlayerIds());
	if (!payload) return;
	event.preventDefault();
	client.sendInputForLocalPlayer(payload.playerId, payload.input);
  };

  window.addEventListener("keydown", onKeyDown);
  window.addEventListener("keyup", onKeyUp);
  setInputCleanup(() => {
	window.removeEventListener("keydown", onKeyDown);
	window.removeEventListener("keyup", onKeyUp);
  });

  client.onMessage((message) => {
    if (message.type === "error") {
      setNote(message.message);
    }

    if (
      message.type === "roomCreated" ||
      message.type === "gameStarted" ||
      message.type === "gameState" ||
      message.type === "gameFinished"
    ) {
      setNote("");
    }

    handleServerMessage(client, message);
  });

  client.connect(getLocalWsUrl());
}
