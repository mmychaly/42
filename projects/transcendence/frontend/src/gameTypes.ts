export type GameStatus = "waiting" | "running" | "finished";

export type GameBall = {
  x: number;
  y: number;
  vx?: number;
  vy?: number;
};

export type GamePaddle = {
  y: number;
};

export type GamePaddles = {
  p1: GamePaddle;
  p2: GamePaddle;
};

export type GamePlayer = {
  id: string;
  username: string;
  ready: boolean;
  score: number;
  isGuest?: boolean;
};

export type GameWinner = "p1" | "p2" | null;

export type GameState = {
  status: GameStatus;
  ball: GameBall;
  paddles: GamePaddles;
  player1: GamePlayer;
  player2: GamePlayer;
  winner: GameWinner;
};

export type GameInput = {
  key: "up" | "down";
  type: "keydown" | "keyup";
};

export type ServerWinner = { player: "p1" | "p2"; username?: string } | null;

export type ServerGameState = {
  status: GameState["status"];
  ball: GameState["ball"];
  paddles: GameState["paddles"];
  player1: GameState["player1"];
  player2: GameState["player2"];
  winner: GameState["winner"] | ServerWinner;
  roomId?: number | string;
  mode?: string;
};
