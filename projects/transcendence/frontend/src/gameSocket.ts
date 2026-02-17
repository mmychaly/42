import type { GameInput, ServerGameState } from "./gameTypes.js";

type GameStatusPayload =
  | { status: "in game"; room: ServerGameState }
  | { status: "in queue"; position: number }
  | { status: "player not found in queue and room" };

export type GameServerMessage =
  | {
      type: "authenticated";
      data: {
        id: number | string;
        username: string;
        isGuest: boolean;
        tournamentId?: number;
      };
    }
  | { type: "joinedQueue"; data: { position: number; status: string } }
  | {
      type: "waitingOpponnent";
      data: { matchId: number; tournamentId: number };
    }
  | { type: "tournamentMatchReady"; data: ServerGameState }
  | { type: "status"; data: GameStatusPayload }
  | { type: "error"; message: string }
  | {
      type: "playerReady";
      data: { playerId: number | string; bothReady: boolean };
    }
  | { type: "roomCreated"; data: ServerGameState }
  | { type: "gameStarted"; data: ServerGameState }
  | { type: "gameState"; data: ServerGameState }
  | { type: "gameFinished"; data: ServerGameState }
  | {
      type: "playerDisconnected";
      data: { disconnectedPlayer: number | string; winner: "p1" | "p2" };
    };

export type GameAuthPayload = {
  //token?: string; вроде договорились чекать на беке
  username?: string; // Для гостя в online
  guestUsername?: string; // для local user+guest
  player1Username?: string; // для local user1+user2
  player2Username?: string; // для local user1+user2
  participantId?: number | string; // для tournament auth
  alias?: string; // для tournament guest
  isGuest?: boolean; // флаг гостя для tournament auth
};

type GameClientMessage =
  | ({ type: "auth" } & GameAuthPayload)
  | { type: "joinQueue" }
  | {
      type: "joinMatch";
      participantId: number | string;
      matchId: number | string;
    }
  | { type: "ready"; playerId?: number | string; participantId?: number | string }
  | {
      type: "input";
      input: GameInput;
      playerId?: number | string;
      participantId?: number | string;
    };

export type GameSocketClient = {
  connect: (url: string) => void;
  onOpen: (cb: () => void) => void;

  sendAuth: (payload: GameAuthPayload) => void;
  sendJoinQueue: () => void;
  sendJoinMatch: (
    participantId: number | string,
    matchId: number | string,
  ) => void;
  sendReady: () => void;
  sendInput: (input: GameInput) => void;
  sendReadyForLocalPlayer: (playerId: number | string) => void;
  sendInputForLocalPlayer: (
    playerId: number | string,
    input: GameInput,
  ) => void;
  sendReadyForParticipant: (participantId: number | string) => void;
  sendInputForParticipant: (
    participantId: number | string,
    input: GameInput,
  ) => void;

  onMessage: (cb: (message: GameServerMessage) => void) => void;
  disconnect: () => void;
};

export function createGameSocketClient(): GameSocketClient {
  let socket: WebSocket | null = null;
  let messageHandler: ((message: GameServerMessage) => void) | null = null;
  let openHandler: (() => void) | null = null;

  const safeSend = (payload: GameClientMessage) => {
    // Не шлем сообщения, пока сокет не в состоянии OPEN.
    if (!socket || socket.readyState !== WebSocket.OPEN) return;
    socket.send(JSON.stringify(payload));
  };

  return {
    connect: (url: string) => {
      if (socket) socket.close();

      socket = new WebSocket(url);

      socket.addEventListener("open", () => {
        openHandler?.();
      });

      socket.addEventListener("message", (event) => {
        try {
          const data = JSON.parse(event.data) as GameServerMessage;
          messageHandler?.(data);
        } catch (error) {
          console.warn("Failed to parse game WS message", error);
        }
      });
    },

    onOpen: (cb) => {
      openHandler = cb;
    },

    sendAuth: (payload) => {
      // Один формат для разных режимов: online/local/tournament.
      safeSend({ type: "auth", ...payload });
    },

    sendJoinQueue: () => {
      safeSend({ type: "joinQueue" });
    },

    sendJoinMatch: (participantId, matchId) => {
      // Турнирный матч требует matchId и participantId.
      safeSend({ type: "joinMatch", participantId, matchId });
    },

    sendReady: () => {
      safeSend({ type: "ready" });
    },

    sendInput: (input: GameInput) => {
      safeSend({ type: "input", input });
    },

    sendReadyForLocalPlayer: (playerId) => {
      safeSend({ type: "ready", playerId });
    },

    sendInputForLocalPlayer: (playerId, input) => {
      safeSend({ type: "input", playerId, input });
    },

    sendReadyForParticipant: (participantId) => {
      safeSend({ type: "ready", participantId });
    },

    sendInputForParticipant: (participantId, input) => {
      safeSend({ type: "input", participantId, input });
    },

    onMessage: (cb) => {
      messageHandler = cb;
    },

    disconnect: () => {
      if (socket) socket.close();
      socket = null;
    },
  };
}
