import { bootRouter } from "./router.js";
import { setCurrentUser } from "./authStore.js";
import { fetchMe } from "./authApi.js";

async function main() {
  try {
    const user = await fetchMe();
    if (user) {
      setCurrentUser(user);
    }
  } catch (error) {
    console.error("Failed to init auth", error);
  }

  bootRouter();
}

main();
