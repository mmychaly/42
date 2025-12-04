export const TournamentPage = () => `
  <section class="p-4 max-w-xl mx-auto">
    <h2 class="text-2xl font-bold mb-4">Tournament</h2>

    <!-- форма регистрации алиасов -->
    <form class="flex gap-2 mb-4">
      <input
        type="text"
        placeholder="Player alias"
        class="flex-1 px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
      />
      <button
        type="submit"
        class="px-4 py-2 rounded bg-blue-600 hover:bg-blue-500 text-white font-medium"
      >
        Add player
      </button>
    </form>

    <!-- список игроков (пока заглушка) -->
    <div class="mb-4">
      <h3 class="font-semibold mb-2">Registered players (stub)</h3>
      <ul class="space-y-1 text-slate-200 text-sm">
        <li>GayboY 1</li>
        <li>Kazin 2</li>
        <li>Bumazhnik 3</li>
      </ul>
    </div>

    <!-- текущий и следующий матч (заглушка) -->
    <div class="border border-slate-600 rounded p-3 text-sm">
      <p class="mb-1"><span class="font-semibold">Current match:</span> Player_1 vs Player_2</p>
      <p><span class="font-semibold">Next up:</span> Player_3 vs Player_4</p>
    </div>
  </section>
`;
