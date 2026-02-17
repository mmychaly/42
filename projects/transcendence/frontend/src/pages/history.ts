import type { NavigateFn } from "../routerTypes.js";
import { getCurrentUser } from "../authStore.js";
import { getUserMatches, type UserMatch } from "../usersApi.js";
import {
  formatDateTime,
  formatMatchResult,
  formatModeLabel,
  parseTimestamp,
} from "../utils.js";
import { ChatWidget, setupChatWidget } from "./chatWidget.js";

type PeriodFilter = "all" | "day" | "week" | "month";
type ModeFilter = "all" | "quick" | "tournament";

export const HistoryPage = () => `
  <section class="p-4 max-w-6xl w-full mx-auto space-y-6">
    <header class="flex flex-col sm:flex-row sm:items-center sm:justify-between gap-2">
      <div>
        <h2 class="text-2xl font-bold">History</h2>
      </div>
      <span id="history-count" class="text-xs text-slate-400">-</span>
    </header>

    <div class="flex flex-col lg:flex-row lg:items-end gap-4">
      <label class="text-sm text-slate-300">
        Period
        <select
          id="history-period"
          class="mt-1 block w-full rounded border border-slate-700 bg-slate-900 px-3 py-2 text-sm text-slate-100"
        >
          <option value="all">All time</option>
          <option value="day">Day</option>
          <option value="week">Week</option>
          <option value="month">Month</option>
        </select>
      </label>

      <label class="text-sm text-slate-300">
        Mode
        <select
          id="history-mode"
          class="mt-1 block w-full rounded border border-slate-700 bg-slate-900 px-3 py-2 text-sm text-slate-100"
        >
          <option value="all">All modes</option>
          <option value="quick">Quick</option>
          <option value="tournament">Tournament</option>
        </select>
      </label>
    </div>

    <div class="grid grid-cols-2 lg:grid-cols-3 gap-3 text-sm text-slate-200">
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Total games</p>
        <p id="history-total" class="text-lg font-semibold text-slate-100">-</p>
      </div>
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Wins</p>
        <p id="history-wins" class="text-lg font-semibold text-slate-100">-</p>
      </div>
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Losses</p>
        <p id="history-losses" class="text-lg font-semibold text-slate-100">-</p>
      </div>
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Win rate</p>
        <p id="history-winrate" class="text-lg font-semibold text-slate-100">-</p>
      </div>
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Avg score</p>
        <p id="history-avg-score" class="text-lg font-semibold text-slate-100">-</p>
      </div>
      <div class="p-3 rounded bg-slate-900/60 border border-slate-800">
        <p class="text-xs text-slate-400">Current streak</p>
        <p id="history-streak" class="text-lg font-semibold text-slate-100">-</p>
      </div>
    </div>

    <div class="p-4 rounded bg-slate-950/60 border border-slate-800">
      <div class="flex items-center justify-between">
        <h3 class="font-semibold">Wins / losses / win rate</h3>
        <span class="text-xs text-slate-500">Filtered</span>
      </div>
      <div id="history-chart" class="mt-4 min-h-[9rem] flex flex-wrap items-end gap-6 text-xs text-slate-400">
        <span class="text-slate-500">Loading...</span>
      </div>
    </div>

    <div class="rounded border border-slate-800 bg-slate-950/60 overflow-x-auto">
      <table class="min-w-full text-sm">
        <thead class="text-xs uppercase text-slate-400 border-b border-slate-800">
          <tr>
            <th class="px-3 py-2 text-left">Date</th>
            <th class="px-3 py-2 text-left">Mode</th>
            <th class="px-3 py-2 text-left">Opponent</th>
            <th class="px-3 py-2 text-left">Score</th>
            <th class="px-3 py-2 text-left">Result</th>
          </tr>
        </thead>
        <tbody id="history-table-body" class="divide-y divide-slate-800">
          <tr>
            <td class="px-3 py-3 text-slate-400" colspan="5">Loading...</td>
          </tr>
        </tbody>
      </table>
    </div>

    <p id="history-error" class="text-sm text-rose-400"></p>
    ${ChatWidget()}
  </section>
`;

export function setupHistoryPage(navigate: NavigateFn): void {
  const user = getCurrentUser();
  if (!user) {
    navigate("/login");
    return;
  }

  setupChatWidget();

  const periodSelect = document.getElementById(
    "history-period",
  ) as HTMLSelectElement | null;
  const modeSelect = document.getElementById(
    "history-mode",
  ) as HTMLSelectElement | null;
  const countEl = document.getElementById("history-count");
  const totalEl = document.getElementById("history-total");
  const winsEl = document.getElementById("history-wins");
  const lossesEl = document.getElementById("history-losses");
  const winRateEl = document.getElementById("history-winrate");
  const avgScoreEl = document.getElementById("history-avg-score");
  const streakEl = document.getElementById("history-streak");
  const chartEl = document.getElementById("history-chart");
  const tableBodyEl = document.getElementById("history-table-body");
  const errorEl = document.getElementById("history-error");

  let allMatches: UserMatch[] = [];

  const getPeriodCutoff = (period: PeriodFilter) => {
    if (period === "all") return null;
    const days =
      period === "day"
        ? 1
        : period === "week"
          ? 7
          : period === "month"
            ? 30
            : 0;
    if (days === 0) return null;
    return Date.now() - days * 24 * 60 * 60 * 1000;
  };

  const applyFilters = () => {
    const period = (periodSelect?.value || "all") as PeriodFilter;
    const mode = (modeSelect?.value || "all") as ModeFilter;
    const cutoff = getPeriodCutoff(period);

    const filtered = allMatches.filter((match) => {
      if (mode !== "all" && match.mode !== mode) return false;
      if (!cutoff) return true;
      const ts = parseTimestamp(match.startedAt);
      if (Number.isNaN(ts)) return false;
      return ts >= cutoff;
    });

    filtered.sort((a, b) => {
      const aTime = parseTimestamp(a.startedAt);
      const bTime = parseTimestamp(b.startedAt);
      const safeA = Number.isNaN(aTime) ? 0 : aTime;
      const safeB = Number.isNaN(bTime) ? 0 : bTime;
      return safeB - safeA;
    });

    renderStats(filtered);
    renderChart(filtered);
    renderTable(filtered);

    if (countEl) {
      countEl.textContent = `${filtered.length} matches`;
    }
  };

  const renderStats = (matches: UserMatch[]) => {
    const wins = matches.filter((m) => m.result === "win").length;
    const losses = matches.filter((m) => m.result === "loss").length;
    const total = wins + losses;
    const winRate = total > 0 ? Math.round((wins / total) * 100) : 0;

    const scored = matches.filter((m) => m.score);
    const scoreSum = scored.reduce(
      (acc, match) => {
        if (!match.score) return acc;
        return {
          me: acc.me + match.score.me,
          opponent: acc.opponent + match.score.opponent,
        };
      },
      { me: 0, opponent: 0 },
    );
    const avgMe = scored.length > 0 ? scoreSum.me / scored.length : 0;
    const avgOpp = scored.length > 0 ? scoreSum.opponent / scored.length : 0;

    let streak = 0;
    for (const match of matches) {
      if (match.result === "win") {
        streak += 1;
      } else if (match.result === "loss") {
        break;
      }
    }

    if (totalEl) totalEl.textContent = String(matches.length);
    if (winsEl) winsEl.textContent = String(wins);
    if (lossesEl) lossesEl.textContent = String(losses);
    if (winRateEl) winRateEl.textContent = `${winRate}%`;
    if (avgScoreEl)
      avgScoreEl.textContent = `${avgMe.toFixed(1)} - ${avgOpp.toFixed(1)}`;
    if (streakEl) streakEl.textContent = `${streak}`;
  };

  const renderChart = (matches: UserMatch[]) => {
    if (!chartEl) return;
    chartEl.innerHTML = "";

    const wins = matches.filter((m) => m.result === "win").length;
    const losses = matches.filter((m) => m.result === "loss").length;
    const total = wins + losses;
    const winRatePercent = total > 0 ? Math.round((wins / total) * 100) : 0;
    const maxValue = Math.max(1, wins, losses, winRatePercent);
    const maxHeight = 84;

    const bars = [
      { label: "Wins", value: wins, color: "bg-emerald-500" },
      { label: "Losses", value: losses, color: "bg-orange-400" },
      { label: "Win rate", value: winRatePercent, color: "bg-sky-500" },
    ];

    bars.forEach((barDef) => {
      const wrap = document.createElement("div");
      wrap.className = "flex flex-col items-center gap-2";

      const value = document.createElement("span");
      value.className = "text-slate-300";
      value.textContent =
        barDef.label === "Win rate" ? `${barDef.value}%` : `${barDef.value}`;

      const bar = document.createElement("div");
      bar.className = `${barDef.color} w-10 rounded-t`;
      const height = Math.round((barDef.value / maxValue) * maxHeight);
      bar.style.height = `${height}px`;

      const label = document.createElement("span");
      label.textContent = barDef.label;
      label.className = "text-xs text-slate-400";

      wrap.appendChild(value);
      wrap.appendChild(bar);
      wrap.appendChild(label);
      chartEl.appendChild(wrap);
    });
  };

  const renderTable = (matches: UserMatch[]) => {
    if (!tableBodyEl) return;
    tableBodyEl.innerHTML = "";

    if (matches.length === 0) {
      const row = document.createElement("tr");
      const cell = document.createElement("td");
      cell.colSpan = 5;
      cell.className = "px-3 py-3 text-slate-400";
      cell.textContent = "No matches for selected filters.";
      row.appendChild(cell);
      tableBodyEl.appendChild(row);
      return;
    }

    matches.forEach((match) => {
      const row = document.createElement("tr");

      const dateCell = document.createElement("td");
      dateCell.className = "px-3 py-3";
      dateCell.textContent = formatDateTime(match.startedAt);

      const modeCell = document.createElement("td");
      modeCell.className = "px-3 py-3";
      modeCell.textContent = formatModeLabel(match.mode);

      const oppCell = document.createElement("td");
      oppCell.className = "px-3 py-3";
      oppCell.textContent =
        match.opponentName && match.opponentName.trim().length > 0
          ? match.opponentName
          : "-";

      const scoreCell = document.createElement("td");
      scoreCell.className = "px-3 py-3";
      scoreCell.textContent = match.score
        ? `${match.score.me}:${match.score.opponent}`
        : "-";

      const resultCell = document.createElement("td");
      const result = formatMatchResult(match.result);
      resultCell.className = `px-3 py-3 font-semibold ${result.className}`;
      resultCell.textContent = result.label;

      row.appendChild(dateCell);
      row.appendChild(modeCell);
      row.appendChild(oppCell);
      row.appendChild(scoreCell);
      row.appendChild(resultCell);
      tableBodyEl.appendChild(row);
    });
  };

  const loadMatches = async () => {
    if (errorEl) errorEl.textContent = "";
    try {
      allMatches = await getUserMatches();
      applyFilters();
    } catch (error) {
      if (errorEl) {
        errorEl.textContent =
          error instanceof Error ? error.message : "Failed to load matches";
      }
      if (tableBodyEl) {
        tableBodyEl.innerHTML = "";
        const row = document.createElement("tr");
        const cell = document.createElement("td");
        cell.colSpan = 5;
        cell.className = "px-3 py-3 text-slate-400";
        cell.textContent = "Unable to load matches.";
        row.appendChild(cell);
        tableBodyEl.appendChild(row);
      }
    }
  };

  if (periodSelect) {
    periodSelect.addEventListener("change", applyFilters);
  }
  if (modeSelect) {
    modeSelect.addEventListener("change", applyFilters);
  }

  void loadMatches();
}
