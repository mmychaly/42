export const GamePage = () => `
  <section class="p-4">
    <h2 class="text-2xl font-bold mb-4">Game 1v1</h2>
    <p class="text-sm text-slate-400 mb-4">
      Пока просто заглушка.
    </p>

    <div
      class="relative mx-auto border border-slate-600 rounded-lg"
      style="width: 640px; height: 360px;"
    >
      <!-- левая ракетка -->
      <div class="absolute left-2 top-1/2 -translate-y-1/2 w-2 h-20 bg-slate-100 rounded"></div>
      <!-- правая ракетка -->
      <div class="absolute right-2 top-1/2 -translate-y-1/2 w-2 h-20 bg-slate-100 rounded"></div>
      <!-- мяч -->
      <div class="absolute left-1/2 top-1/2 -translate-x-1/2 -translate-y-1/2 w-4 h-4 bg-yellow-400 rounded-full"></div>
    </div>

    <div class="mt-4 flex items-center justify-center gap-6 text-lg">
      <span>Player 1: <span class="font-bold">0</span></span>
      <span>–</span>
      <span>Player 2: <span class="font-bold">0</span></span>
    </div>

    <div class="mt-4 flex justify-center gap-3">
      <button class="px-4 py-2 rounded bg-green-600 hover:bg-green-500 text-white text-sm">
        Start
      </button>
      <button class="px-4 py-2 rounded bg-slate-700 hover:bg-slate-600 text-white text-sm">
        Pause
      </button>
    </div>
  </section>
`;
