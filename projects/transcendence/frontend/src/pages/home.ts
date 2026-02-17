import { getCurrentUser } from "../authStore.js";
import { ChatWidget, setupChatWidget } from "./chatWidget.js";

export const HomePage = () => `
  <section class="p-4">
    <h2 class="text-2xl font-bold mb-4">Home</h2>
    <p class="text-slate-300">
      Welcome to our lovely ft_transcendence BUMAGA!
    </p>
    ${getCurrentUser() ? ChatWidget() : ""}
  </section>
`;

export function setupHomePage() {
  if (getCurrentUser()) {
    setupChatWidget();
  }
}
