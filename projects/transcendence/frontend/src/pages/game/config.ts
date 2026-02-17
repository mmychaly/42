import type { GameStatus } from "../../gameTypes.js";

export const GAME_W = 800;
export const GAME_H = 400;
export const PADDLE_W = 10;
export const PADDLE_H = 60;
export const BALL_SIZE = 10;

export const STATUS_LABELS: Record<GameStatus, string> = {
  waiting: "Waiting",
  running: "Running",
  finished: "Finished",
};
