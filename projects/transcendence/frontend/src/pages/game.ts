import type { NavigateFn } from "../routerTypes.js";
import { getCurrentUser } from "../authStore.js";
import { setupChatWidget } from "./chatWidget.js";
import {
  renderGameContent,
  renderGameShell,
  renderLocalLobby,
  renderModeSelection,
} from "./game/view.js";
import { resetGameState } from "./game/state.js";
import {
  cleanupConnection,
  resetLocalPlayerIds,
  setSelectedMode,
} from "./game/channel.js";
import { mountOnlineGame } from "./game/online.js";
import { mountTournamentGame } from "./game/tournament.js";
import {
  LOCAL_ENABLED,
  mountLocalGame,
  setupLocalLobby,
} from "./game/local.js";
import { getOrCreateGuestName } from "../utils.js";
import {
  clearTournamentJoin,
  getTournamentJoin,
} from "../tournamentSession.js";

let cleanupPage: (() => void) | null = null;

export const GamePage = () => renderGameShell(renderModeSelection());

export function setupGamePage(
  navigate: NavigateFn,
): void | (() => void) {
  const container = document.getElementById("game-page");
  if (!container) return;

  if (getCurrentUser()) {
    setupChatWidget();
  }

  const params = new URLSearchParams(window.location.search);
  const isTournament = params.get("mode") === "tournament";

  const cleanup = () => {
    cleanupPage?.();
    cleanupPage = null;
    cleanupConnection();
    resetGameState();
    resetLocalPlayerIds();
  };

  // --- 1. TOURNAMENT LOGIC ---
  if (isTournament) {
    const joinInfo = getTournamentJoin();
    if (!joinInfo || !joinInfo.p1 || !joinInfo.p2) {
      clearTournamentJoin();
      navigate("/tournament");
      return cleanup;
    }

    setSelectedMode("tournament");
    renderInto(container, renderGameContent());
    cleanupPage = mountTournamentGame(container, joinInfo, () => {
      clearTournamentJoin();
      navigate("/tournament");
    });
    return cleanup;
  }

  // PRIVATE ROOM
  // Check if URL is /game/room/:id
  const pathParts = window.location.pathname.split('/');
  const roomIndex = pathParts.indexOf("room");
  const hasPrivateId = roomIndex !== -1 && pathParts[roomIndex + 1] && !isNaN(Number(pathParts[roomIndex + 1]));

  if (hasPrivateId) {
    // Define what happens when the private game ends
    const handlePrivateContinue = () => {
        navigate("/game");
    };

    setSelectedMode("online");
    renderInto(container, renderGameContent());

    cleanupPage = mountOnlineGame(container, handlePrivateContinue);
    return cleanup;
  }

  setSelectedMode(null);
  renderInto(container, renderModeSelection());
  setupModeSelection(container);

  return cleanup;
}

function setupModeSelection(container: HTMLElement): void {
  cleanupPage?.();
  cleanupPage = null;
  cleanupConnection();
  resetGameState();
  resetLocalPlayerIds();

  const onlineButton =
    container.querySelector<HTMLButtonElement>("#game-mode-online");
  const localButton =
    container.querySelector<HTMLButtonElement>("#game-mode-local");
  if (!onlineButton || !localButton) return;

  const handleContinue = () => {
    // Возвращаемся к выбору режима после завершения матча.
    setSelectedMode(null);
    renderInto(container, renderModeSelection());
    setupModeSelection(container);
  };

  const handleOnline = () => {
    setSelectedMode("online");
    renderInto(container, renderGameContent());
    cleanupPage = mountOnlineGame(container, handleContinue);
  };

  const handleLocal = () => {
    setSelectedMode("local");
    const user = getCurrentUser();
    const player1Name =
      user?.username?.trim() || getOrCreateGuestName("local-p1");
    const lobbyDefaults = {
      player1Name,
      player2Name: getOrCreateGuestName("local-p2"),
    };
    renderInto(
      container,
      renderLocalLobby({
        localEnabled: LOCAL_ENABLED,
      }),
    );

    const removeLobby = setupLocalLobby(
      container,
      lobbyDefaults,
      () => {
        setSelectedMode(null);
        renderInto(container, renderModeSelection());
        setupModeSelection(container);
      },
      (lobbyData) => {
        removeLobby();
        renderInto(container, renderGameContent());
        cleanupPage = mountLocalGame(container, lobbyData, handleContinue);
      },
    );

    cleanupPage = () => {
      removeLobby();
    };
  };

  onlineButton.addEventListener("click", handleOnline);
  localButton.addEventListener("click", handleLocal);

  cleanupPage = () => {
    onlineButton.removeEventListener("click", handleOnline);
    localButton.removeEventListener("click", handleLocal);
  };
}

function renderInto(container: HTMLElement, html: string): void {
  container.innerHTML = html;
}
