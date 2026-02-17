import { createGameSocketClient } from "../../gameSocket.js";
import { getCurrentUser } from "../../authStore.js";
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
import { getGameWsUrl, getOrCreateGuestName, mapInputKey } from "../../utils.js";
import { getGameRefs, updateGameUI } from "./view.js";
import { resetGameState, subscribeGameState } from "./state.js";

export function mountOnlineGame(
  container: HTMLElement,
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

  startOnlineGame(setNote);

  const readyHandler = () => {
    const client = getActiveClient();
    if (!client) return;
    if (!getHasRoom()) {
      return;
    }
    client.sendReady();
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

function startOnlineGame(setNote: (text: string) => void): void {
  cleanupConnection();

  // Check if we are in a Private Room URL (ex /game/room/1)
  const pathParts = window.location.pathname.split('/');
  const urlParam = pathParts[pathParts.length - 1];
  const privateId = !isNaN(Number(urlParam)) ? Number(urlParam) : null;

  const client = createGameSocketClient();
  setActiveClient(client);

  client.onOpen(() => {
    const user = getCurrentUser();

    const authPayload: any = {};

    if (!user) {
      authPayload.username = getOrCreateGuestName("online");
    }

    if (privateId) {
      authPayload.privateId = privateId;
    }

    client.sendAuth(authPayload);
  });

  const onKeyDown = (event: KeyboardEvent) => {
    if (event.repeat) return;
    const key = mapInputKey(event);
    if (!key) return;
    event.preventDefault();

    client.sendInput({ key, type: "keydown" });
  };

  const onKeyUp = (event: KeyboardEvent) => {
    const key = mapInputKey(event);
    if (!key) return;
    event.preventDefault();
    client.sendInput({ key, type: "keyup" });
  };

  // Attach to window
  window.addEventListener("keydown", onKeyDown);
  window.addEventListener("keyup", onKeyUp);

  // CLEANUP
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

  let wsUrl = getGameWsUrl();

  if (privateId) {
    wsUrl = wsUrl.replace('/ws/game', '/ws/game/private');
    if (!wsUrl.includes('/private')) {
        wsUrl += '/private';
    }
  }

  client.connect(wsUrl);
}
