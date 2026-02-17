import type { NavigateFn } from "../routerTypes.js";
import { getCurrentUser, setCurrentUser } from "../authStore.js";
import { patchMe, uploadMyAvatar, getMe } from "../usersApi.js";
import { disableTwofa, setupTwofa, verifyTwofaSetup } from "../authApi.js";
import { refreshNavUserUI } from "./layout.js";
import { ChatWidget, setupChatWidget } from "./chatWidget.js";
import { getUserInitial, updateAvatarImage } from "../utils.js";

export const ProfilePage = () => `
  <section class="p-4 max-w-4xl w-full mx-auto">
    <h2 class="text-2xl font-bold mb-4">Profile</h2>
    <div class="border border-slate-700 rounded p-4 mb-4">
      <div class="flex flex-col lg:flex-row items-start gap-8">
        <div class="flex flex-col items-center sm:items-start gap-3 w-full lg:w-64 shrink-0">
          <div class="w-24 h-24 rounded-full overflow-hidden bg-slate-700 flex items-center justify-center text-3xl font-semibold text-slate-100">
            <img
              id="profile-avatar-img"
              alt="avatar"
              class="w-full h-full object-cover hidden"
            />
            <span id="profile-avatar-fallback">?</span>
          </div>

          <div class="w-full max-w-sm">
            <button
              id="avatar-edit-btn"
              type="button"
              class="w-full px-3 py-1 rounded bg-slate-800 hover:bg-slate-700 text-sm"
            >
              Change avatar
            </button>

            <div id="avatar-edit-controls" class="hidden mt-2 space-y-2 w-full">
              <input
                id="avatar-file-input"
                type="file"
                accept="image/png,image/jpeg"
                class="block w-full text-sm text-slate-300 file:mr-3 file:px-3 file:py-1 file:rounded file:border-0 file:bg-slate-800 file:text-slate-100 hover:file:bg-slate-700"
              />
              <div class="flex flex-col sm:flex-row gap-2 w-full">
                <button
                  id="avatar-save-btn"
                  type="button"
                  class="w-full sm:flex-1 px-3 py-1 rounded bg-blue-600 hover:bg-blue-500 text-sm disabled:opacity-50 disabled:cursor-not-allowed"
                  disabled
                >
                  Save
                </button>
                <button
                  id="avatar-cancel-btn"
                  type="button"
                  class="w-full sm:flex-1 px-3 py-1 rounded bg-slate-700 hover:bg-slate-600 text-sm"
                >
                  Cancel
                </button>
              </div>
              <p id="avatar-error" class="text-xs text-red-400 min-h-[1rem]"></p>
              <p class="text-xs text-slate-500">PNG / JPG, up to 5 MB</p>
            </div>
          </div>
        </div>

        <div class="flex-1 min-w-0">
          <div class="space-y-3">
            <div class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4 items-center">
              <span class="font-semibold sm:text-right">Username:</span>
              <span id="profile-username" class="text-slate-200 break-words">—</span>
            </div>

            <div class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4 items-center">
              <span class="font-semibold sm:text-right">Status:</span>
              <span id="profile-status" class="text-slate-200 break-words">—</span>
            </div>

            <div
              id="displayname-view"
              class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4 items-center w-full"
            >
              <span class="font-semibold sm:text-right">Display name:</span>
              <div class="flex flex-col sm:flex-row sm:items-center sm:justify-between gap-2 sm:gap-4 w-full">
                <span id="profile-displayname" class="text-slate-200 break-words flex-1 min-w-0">—</span>
                <button
                  id="displayname-edit-btn"
                  type="button"
                  class="px-3 py-1 rounded bg-slate-800 hover:bg-slate-700 text-sm w-full sm:w-auto sm:shrink-0"
                >
                  Edit
                </button>
              </div>
            </div>

            <div id="displayname-edit" class="hidden w-full">
              <div class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4">
                <span class="font-semibold sm:text-right sm:pt-2">Display name:</span>

                <div class="flex flex-col gap-2 w-full min-w-0">
                  <input
                    id="displayname-input"
                    type="text"
                    maxlength="30"
                    placeholder="Set your display name (2..30)"
                    class="w-full min-w-0 px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
                  />

                  <div class="flex flex-col sm:flex-row sm:flex-wrap gap-2">
                    <button
                      id="displayname-save-btn"
                      type="button"
                      class="w-full sm:w-auto sm:flex-1 px-3 py-2 rounded bg-blue-600 hover:bg-blue-500 text-sm disabled:opacity-50 disabled:cursor-not-allowed"
                      disabled
                    >
                      Save
                    </button>
                    <button
                      id="displayname-cancel-btn"
                      type="button"
                      class="w-full sm:w-auto sm:flex-1 px-3 py-2 rounded bg-slate-700 hover:bg-slate-600 text-sm"
                    >
                      Cancel
                    </button>
                  </div>

                  <div id="displayname-meta" class="hidden flex justify-between flex-wrap gap-2 text-xs text-slate-500">
                    <p id="displayname-error" class="text-red-400 min-h-[1rem] flex-1"></p>
                    <p id="displayname-counter">0/30</p>
                  </div>
                </div>
              </div>
            </div>

            <div
              id="statusmessage-view"
              class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4 items-start w-full"
            >
              <span class="font-semibold sm:text-right pt-1">Status message:</span>

              <div class="flex flex-col sm:flex-row sm:items-center sm:justify-between gap-2 w-full">
                <div class="flex-1 min-w-0 w-full">
                  <span id="profile-statusmessage" class="text-slate-200 break-words hidden"></span>

                  <input
                    id="statusmessage-empty-input"
                    type="text"
                    disabled
                    maxlength="30"
                    placeholder="Set a status message (max 30 chars)"
                    class="w-full min-w-0 px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100 disabled:opacity-70"
                  />
                </div>

                <button
                  id="statusmessage-edit-btn"
                  type="button"
                  class="px-3 py-1 rounded bg-slate-800 hover:bg-slate-700 text-sm w-full sm:w-auto sm:shrink-0"
                >
                  Edit
                </button>
              </div>
            </div>

            <div id="statusmessage-edit" class="hidden w-full">
              <div class="grid grid-cols-1 sm:grid-cols-[10rem,minmax(0,1fr)] gap-2 sm:gap-4">
                <span class="font-semibold sm:text-right sm:pt-2">Status message:</span>

                <div class="flex flex-col gap-2 w-full min-w-0">
                  <input
                    id="statusmessage-input"
                    type="text"
                    maxlength="30"
                    placeholder="Set a status message (max 30 chars)"
                    class="w-full min-w-0 px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100"
                  />

                  <div class="flex flex-col sm:flex-row sm:flex-wrap gap-2">
                    <button
                      id="statusmessage-save-btn"
                      type="button"
                      class="w-full sm:w-auto sm:flex-1 px-3 py-2 rounded bg-blue-600 hover:bg-blue-500 text-sm disabled:opacity-50 disabled:cursor-not-allowed"
                      disabled
                    >
                      Save
                    </button>
                    <button
                      id="statusmessage-cancel-btn"
                      type="button"
                      class="w-full sm:w-auto sm:flex-1 px-3 py-2 rounded bg-slate-700 hover:bg-slate-600 text-sm"
                    >
                      Cancel
                    </button>
                  </div>

                  <div id="statusmessage-meta" class="hidden flex justify-between flex-wrap gap-2 text-xs text-slate-500">
                    <p id="statusmessage-error" class="text-red-400 min-h-[1rem] flex-1"></p>
                    <p id="statusmessage-counter">0/30</p>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>

    <div class="border border-slate-700 rounded p-4 mb-4">
      <h3 class="font-semibold mb-2">Two-factor authentication</h3>
      <p class="text-sm text-slate-300 mb-3">
        Status:
        <span id="twofa-status" class="font-medium text-slate-100">—</span>
      </p>

      <div id="twofa-disabled" class="space-y-3">
        <button
          id="twofa-enable-btn"
          type="button"
          class="px-3 py-2 rounded bg-blue-600 hover:bg-blue-500 text-sm"
        >
          Enable 2FA
        </button>

        <div id="twofa-setup-panel" class="hidden space-y-3 border border-slate-700 rounded p-3">
          <p class="text-sm text-slate-300">
            Scan the QR code in your authenticator app or enter the key manually.
          </p>
          <div class="flex flex-col sm:flex-row gap-4 items-start">
            <img
              id="twofa-qr"
              alt="2FA QR"
              class="w-40 h-40 rounded bg-slate-800"
            />
            <div class="text-sm text-slate-300 space-y-2">
              <p class="text-xs uppercase tracking-wide text-slate-500">Manual key</p>
              <p id="twofa-manual-key" class="font-mono text-slate-100 break-all">—</p>
            </div>
          </div>

          <div class="flex flex-col gap-2">
            <label class="text-sm text-slate-300" for="twofa-setup-code">
              Confirm setup with 6-digit code
            </label>
            <input
              id="twofa-setup-code"
              type="text"
              inputmode="numeric"
              autocomplete="one-time-code"
              class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100 tracking-[0.3em]"
            />
          </div>

          <p id="twofa-setup-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>

          <div class="flex flex-col sm:flex-row gap-2">
            <button
              id="twofa-setup-confirm"
              type="button"
              class="px-3 py-2 rounded bg-blue-600 hover:bg-blue-500 text-sm"
            >
              Confirm 2FA
            </button>
            <button
              id="twofa-setup-cancel"
              type="button"
              class="px-3 py-2 rounded bg-slate-800 hover:bg-slate-700 text-sm"
            >
              Cancel
            </button>
          </div>
        </div>
      </div>

      <div id="twofa-enabled" class="hidden space-y-3">
        <p class="text-sm text-slate-300">
          Enter a code from your authenticator app to disable 2FA.
        </p>
        <button
          id="twofa-disable-toggle"
          type="button"
          class="px-3 py-2 rounded bg-red-600 hover:bg-red-500 text-sm"
        >
          Disable 2FA
        </button>

        <div id="twofa-disable-panel" class="hidden space-y-3 border border-slate-700 rounded p-3">
          <div class="flex flex-col gap-2">
            <label class="text-sm text-slate-300" for="twofa-disable-code">
              6-digit code
            </label>
            <input
              id="twofa-disable-code"
              type="text"
              inputmode="numeric"
              autocomplete="one-time-code"
              class="px-3 py-2 rounded border border-slate-600 bg-slate-900 text-slate-100 tracking-[0.3em]"
            />
          </div>
          <p id="twofa-disable-error" class="text-sm text-red-400 min-h-[1.25rem]"></p>
          <div class="flex flex-col sm:flex-row gap-2">
            <button
              id="twofa-disable-btn"
              type="button"
              class="px-3 py-2 rounded bg-red-600 hover:bg-red-500 text-sm"
            >
              Confirm disable
            </button>
            <button
              id="twofa-disable-cancel"
              type="button"
              class="px-3 py-2 rounded bg-slate-800 hover:bg-slate-700 text-sm"
            >
              Cancel
            </button>
          </div>
        </div>
      </div>
    </div>
    
    ${ChatWidget()}
  </section>
`;

export function setupProfilePage(navigate: NavigateFn): void {
  const user = getCurrentUser();

  if (!user) {
    navigate("/login");
    return;
  }

  // Initialize Chat Widget
  setupChatWidget();

  // base fields
  const usernameEl = document.getElementById("profile-username");
  const statusEl = document.getElementById("profile-status");

  // avatar elements
  const avatarImgEl = document.getElementById(
    "profile-avatar-img",
  ) as HTMLImageElement | null;
  const avatarFallbackEl = document.getElementById("profile-avatar-fallback");
  const avatarEditBtn = document.getElementById(
    "avatar-edit-btn",
  ) as HTMLButtonElement | null;
  const avatarEditControls = document.getElementById("avatar-edit-controls");
  const avatarFileInput = document.getElementById(
    "avatar-file-input",
  ) as HTMLInputElement | null;
  const avatarSaveBtn = document.getElementById(
    "avatar-save-btn",
  ) as HTMLButtonElement | null;
  const avatarCancelBtn = document.getElementById(
    "avatar-cancel-btn",
  ) as HTMLButtonElement | null;
  const avatarErrorEl = document.getElementById("avatar-error");

  // display name elements
  const displayNameView = document.getElementById("displayname-view");
  const displayNameEdit = document.getElementById("displayname-edit");
  const displayNameSpan = document.getElementById("profile-displayname");

  const displayNameInput = document.getElementById(
    "displayname-input",
  ) as HTMLInputElement | null;
  const displayNameEditBtn = document.getElementById(
    "displayname-edit-btn",
  ) as HTMLButtonElement | null;
  const displayNameSaveBtn = document.getElementById(
    "displayname-save-btn",
  ) as HTMLButtonElement | null;
  const displayNameCancelBtn = document.getElementById(
    "displayname-cancel-btn",
  ) as HTMLButtonElement | null;
  const displayNameErrorEl = document.getElementById("displayname-error");
  const displayNameCounterEl = document.getElementById("displayname-counter");
  const displayNameMeta = document.getElementById("displayname-meta");

  // status message elements
  const statusMsgView = document.getElementById("statusmessage-view");
  const statusMsgEdit = document.getElementById("statusmessage-edit");
  const statusMsgSpan = document.getElementById("profile-statusmessage");
  const statusMsgEmptyInput = document.getElementById(
    "statusmessage-empty-input",
  ) as HTMLInputElement | null;

  const statusMsgInput = document.getElementById(
    "statusmessage-input",
  ) as HTMLInputElement | null;
  const statusMsgEditBtn = document.getElementById(
    "statusmessage-edit-btn",
  ) as HTMLButtonElement | null;
  const statusMsgSaveBtn = document.getElementById(
    "statusmessage-save-btn",
  ) as HTMLButtonElement | null;
  const statusMsgCancelBtn = document.getElementById(
    "statusmessage-cancel-btn",
  ) as HTMLButtonElement | null;
  const statusMsgErrorEl = document.getElementById("statusmessage-error");
  const statusMsgCounterEl = document.getElementById("statusmessage-counter");
  const statusMsgMeta = document.getElementById("statusmessage-meta");

  // 2FA elements
  const twofaStatusEl = document.getElementById("twofa-status");
  const twofaEnabledPanel = document.getElementById("twofa-enabled");
  const twofaDisabledPanel = document.getElementById("twofa-disabled");
  const twofaEnableBtn = document.getElementById(
    "twofa-enable-btn",
  ) as HTMLButtonElement | null;
  const twofaSetupPanel = document.getElementById("twofa-setup-panel");
  const twofaQrImg = document.getElementById(
    "twofa-qr",
  ) as HTMLImageElement | null;
  const twofaManualKeyEl = document.getElementById("twofa-manual-key");
  const twofaSetupCodeInput = document.getElementById(
    "twofa-setup-code",
  ) as HTMLInputElement | null;
  const twofaSetupConfirmBtn = document.getElementById(
    "twofa-setup-confirm",
  ) as HTMLButtonElement | null;
  const twofaSetupCancelBtn = document.getElementById(
    "twofa-setup-cancel",
  ) as HTMLButtonElement | null;
  const twofaSetupErrorEl = document.getElementById("twofa-setup-error");

  const twofaDisableCodeInput = document.getElementById(
    "twofa-disable-code",
  ) as HTMLInputElement | null;
  const twofaDisableToggleBtn = document.getElementById(
    "twofa-disable-toggle",
  ) as HTMLButtonElement | null;
  const twofaDisablePanel = document.getElementById("twofa-disable-panel");
  const twofaDisableBtn = document.getElementById(
    "twofa-disable-btn",
  ) as HTMLButtonElement | null;
  const twofaDisableCancelBtn = document.getElementById(
    "twofa-disable-cancel",
  ) as HTMLButtonElement | null;
  const twofaDisableErrorEl = document.getElementById("twofa-disable-error");

  if (usernameEl) usernameEl.textContent = user.username;
  if (statusEl) statusEl.textContent = user.status;

  // --- Avatar render ---
  const renderAvatar = (url: string | null) => {
    const current = getCurrentUser();
    const initial = current ? getUserInitial(current) : "?";
    updateAvatarImage(avatarImgEl, avatarFallbackEl, url, initial);
  };

  renderAvatar(user.avatarUrl);

  // --- View render helpers ---
  const renderDisplayNameView = (value: string) => {
    if (displayNameSpan) displayNameSpan.textContent = value || "—";
  };

  const renderStatusMessageView = (value: string) => {
    const hasValue = value.trim().length > 0;

    if (statusMsgSpan) {
      statusMsgSpan.textContent = hasValue ? value : "—";
      statusMsgSpan.classList.toggle("hidden", !hasValue);
    }
    if (statusMsgEmptyInput) {
      statusMsgEmptyInput.classList.toggle("hidden", hasValue);
      statusMsgEmptyInput.value = "";
    }
  };

  // =========================
  // DISPLAY NAME (view <-> edit)
  // =========================
  let displayNameOriginal = user.displayName ?? "";
  renderDisplayNameView(displayNameOriginal);

  const setDisplayNameMode = (isEditing: boolean) => {
    if (!displayNameView || !displayNameEdit || !displayNameMeta) return;

    displayNameView.classList.toggle("hidden", isEditing);
    displayNameEdit.classList.toggle("hidden", !isEditing);
    displayNameMeta.classList.toggle("hidden", !isEditing);

    if (displayNameErrorEl) displayNameErrorEl.textContent = "";
    if (!isEditing && displayNameSaveBtn) displayNameSaveBtn.disabled = true;
  };

  const validateDisplayName = (value: string, original: string) => {
    const len = value.length;
    const trimmed = value.trim();

    if (displayNameCounterEl) displayNameCounterEl.textContent = `${len}/30`;
    if (displayNameErrorEl) displayNameErrorEl.textContent = "";

    const okLen = len <= 30;
    const okMin = trimmed.length >= 2;
    const changed = trimmed !== original.trim();

    if (!okLen && displayNameErrorEl)
      displayNameErrorEl.textContent = "Max 30 characters";
    if (okLen && !okMin && displayNameErrorEl)
      displayNameErrorEl.textContent = "Min 2 characters";

    if (displayNameSaveBtn)
      displayNameSaveBtn.disabled = !(okLen && okMin && changed);
  };

  if (displayNameEditBtn) {
    displayNameEditBtn.addEventListener("click", () => {
      setDisplayNameMode(true);
      if (displayNameInput) {
        displayNameInput.value = displayNameOriginal;
        displayNameInput.focus();
        validateDisplayName(displayNameInput.value, displayNameOriginal);
      }
    });
  }

  if (displayNameInput) {
    displayNameInput.addEventListener("input", () => {
      validateDisplayName(displayNameInput.value, displayNameOriginal);
    });
  }

  if (displayNameCancelBtn) {
    displayNameCancelBtn.addEventListener("click", () => {
      if (displayNameInput) displayNameInput.value = displayNameOriginal;
      setDisplayNameMode(false);
    });
  }

  if (displayNameSaveBtn) {
    displayNameSaveBtn.addEventListener("click", async () => {
      if (!displayNameInput) return;
      const next = displayNameInput.value.trim();

      try {
        displayNameSaveBtn.disabled = true;

        const updated = await patchMe({ displayName: next });
        setCurrentUser(updated);

        refreshNavUserUI(); // шапка: имя/аватар
        renderAvatar(updated.avatarUrl); // если фоллбек-аватар — обновит букву

        displayNameOriginal = updated.displayName ?? next;
        renderDisplayNameView(displayNameOriginal);

        setDisplayNameMode(false);
      } catch (err) {
        if (displayNameErrorEl) {
          displayNameErrorEl.textContent =
            err instanceof Error ? err.message : "Failed to save display name";
        }
        validateDisplayName(displayNameInput.value, displayNameOriginal);
      }
    });
  }

  setDisplayNameMode(false);

  // =========================
  // STATUS MESSAGE (view <-> edit)
  // =========================
  let statusMsgOriginal = user.statusMessage ?? "";
  renderStatusMessageView(statusMsgOriginal);

  const setStatusMessageMode = (isEditing: boolean) => {
    if (!statusMsgView || !statusMsgEdit || !statusMsgMeta) return;

    statusMsgView.classList.toggle("hidden", isEditing);
    statusMsgEdit.classList.toggle("hidden", !isEditing);
    statusMsgMeta.classList.toggle("hidden", !isEditing);

    if (statusMsgErrorEl) statusMsgErrorEl.textContent = "";
    if (!isEditing && statusMsgSaveBtn) statusMsgSaveBtn.disabled = true;
  };

  const validateStatusMessage = (value: string, original: string) => {
    const len = value.length;

    if (statusMsgCounterEl) statusMsgCounterEl.textContent = `${len}/30`;
    if (statusMsgErrorEl) statusMsgErrorEl.textContent = "";

    const okLen = len <= 30;
    const changed = value !== original;

    if (!okLen && statusMsgErrorEl)
      statusMsgErrorEl.textContent = "Max 30 characters";
    if (statusMsgSaveBtn) statusMsgSaveBtn.disabled = !(okLen && changed);
  };

  if (statusMsgEditBtn) {
    statusMsgEditBtn.addEventListener("click", () => {
      setStatusMessageMode(true);
      if (statusMsgInput) {
        statusMsgInput.value = statusMsgOriginal;
        statusMsgInput.focus();
        validateStatusMessage(statusMsgInput.value, statusMsgOriginal);
      }
    });
  }

  if (statusMsgInput) {
    statusMsgInput.addEventListener("input", () => {
      validateStatusMessage(statusMsgInput.value, statusMsgOriginal);
    });
  }

  if (statusMsgCancelBtn) {
    statusMsgCancelBtn.addEventListener("click", () => {
      if (statusMsgInput) statusMsgInput.value = statusMsgOriginal;
      setStatusMessageMode(false);
      renderStatusMessageView(statusMsgOriginal);
    });
  }

  if (statusMsgSaveBtn) {
    statusMsgSaveBtn.addEventListener("click", async () => {
      if (!statusMsgInput) return;
      const next = statusMsgInput.value;

      try {
        statusMsgSaveBtn.disabled = true;

        const updated = await patchMe({ statusMessage: next });
        setCurrentUser(updated);
        refreshNavUserUI();

        statusMsgOriginal = updated.statusMessage ?? "";
        renderStatusMessageView(statusMsgOriginal);

        setStatusMessageMode(false);
      } catch (err) {
        if (statusMsgErrorEl) {
          statusMsgErrorEl.textContent =
            err instanceof Error
              ? err.message
              : "Failed to save status message";
        }
        validateStatusMessage(statusMsgInput.value, statusMsgOriginal);
      }
    });
  }

  setStatusMessageMode(false);

  // =========================
  // AVATAR (edit/save/cancel)
  // =========================
  let avatarOriginalUrl = user.avatarUrl;
  let avatarSelectedFile: File | null = null;
  let avatarPreviewUrl: string | null = null;

  const setAvatarMode = (isEditing: boolean) => {
    if (!avatarEditBtn || !avatarEditControls) return;
    avatarEditBtn.classList.toggle("hidden", isEditing);
    avatarEditControls.classList.toggle("hidden", !isEditing);
    if (avatarErrorEl) avatarErrorEl.textContent = "";
    if (avatarSaveBtn) avatarSaveBtn.disabled = true;
  };

  const validateAvatarFile = (file: File | null) => {
    if (!avatarSaveBtn) return;
    if (avatarErrorEl) avatarErrorEl.textContent = "";

    if (!file) {
      avatarSaveBtn.disabled = true;
      return;
    }

    const maxBytes = 5 * 1024 * 1024;
    const okType = file.type === "image/png" || file.type === "image/jpeg";
    const okSize = file.size <= maxBytes;

    if (!okType && avatarErrorEl) avatarErrorEl.textContent = "Only PNG or JPG";
    if (!okSize && avatarErrorEl)
      avatarErrorEl.textContent = "Max file size is 5 MB";

    avatarSaveBtn.disabled = !(okType && okSize);
  };

  if (avatarEditBtn) {
    avatarEditBtn.addEventListener("click", () => {
      avatarOriginalUrl = getCurrentUser()?.avatarUrl ?? null;
      avatarSelectedFile = null;
      setAvatarMode(true);
      if (avatarFileInput) avatarFileInput.value = "";
      validateAvatarFile(null);
    });
  }

  if (avatarFileInput) {
    avatarFileInput.addEventListener("change", () => {
      const file = avatarFileInput.files?.[0] ?? null;
      avatarSelectedFile = file;
      validateAvatarFile(file);

      if (file && (file.type === "image/png" || file.type === "image/jpeg")) {
        if (avatarPreviewUrl) {
          try {
            URL.revokeObjectURL(avatarPreviewUrl);
          } catch {
            // ignore
          }
        }
        avatarPreviewUrl = URL.createObjectURL(file);
        renderAvatar(avatarPreviewUrl);
      }
    });
  }

  if (avatarCancelBtn) {
    avatarCancelBtn.addEventListener("click", () => {
      if (avatarPreviewUrl) {
        try {
          URL.revokeObjectURL(avatarPreviewUrl);
        } catch {
          // ignore
        }
        avatarPreviewUrl = null;
      }

      avatarSelectedFile = null;
      if (avatarFileInput) avatarFileInput.value = "";
      renderAvatar(avatarOriginalUrl);
      setAvatarMode(false);
    });
  }

  if (avatarSaveBtn) {
    avatarSaveBtn.addEventListener("click", async () => {
      if (!avatarSelectedFile) return;

      try {
        avatarSaveBtn.disabled = true;

        // 1) загружаем файл
        await uploadMyAvatar(avatarSelectedFile);

        // 2) забираем свежего пользователя
        const fresh = await getMe();

        // 3) обновляем store + UI
        setCurrentUser(fresh);
        refreshNavUserUI();
        renderAvatar(fresh.avatarUrl ?? null);

        setAvatarMode(false);
      } catch (err) {
        if (avatarErrorEl) {
          avatarErrorEl.textContent =
            err instanceof Error ? err.message : "Failed to upload avatar";
        }
        // если ошибка — пусть Save снова станет доступной после re-validate
        validateAvatarFile(avatarSelectedFile);
      }
    });
  }

  // =========================
  // TWO-FACTOR AUTHENTICATION
  // =========================
  const setTwofaSetupVisible = (visible: boolean) => {
    if (!twofaSetupPanel) return;
    twofaSetupPanel.classList.toggle("hidden", !visible);
    if (!visible) {
      if (twofaSetupErrorEl) twofaSetupErrorEl.textContent = "";
      if (twofaSetupCodeInput) twofaSetupCodeInput.value = "";
    }
  };

  const setTwofaDisableVisible = (visible: boolean) => {
    if (!twofaDisablePanel) return;
    twofaDisablePanel.classList.toggle("hidden", !visible);
    if (!visible) {
      if (twofaDisableErrorEl) twofaDisableErrorEl.textContent = "";
      if (twofaDisableCodeInput) twofaDisableCodeInput.value = "";
    }
  };

  const renderTwofaStatus = (enabled: boolean) => {
    if (twofaStatusEl) {
      twofaStatusEl.textContent = enabled ? "Enabled" : "Disabled";
      twofaStatusEl.classList.toggle("text-green-400", enabled);
      twofaStatusEl.classList.toggle("text-slate-100", !enabled);
    }
    if (twofaEnabledPanel)
      twofaEnabledPanel.classList.toggle("hidden", !enabled);
    if (twofaDisabledPanel)
      twofaDisabledPanel.classList.toggle("hidden", enabled);
    if (!enabled) {
      setTwofaSetupVisible(false);
      setTwofaDisableVisible(false);
    }
    if (twofaDisableErrorEl) twofaDisableErrorEl.textContent = "";
    if (twofaDisableCodeInput) twofaDisableCodeInput.value = "";
  };

  renderTwofaStatus(Boolean(user.twofaEnabled));

  if (twofaEnableBtn) {
    twofaEnableBtn.addEventListener("click", async () => {
      if (twofaSetupErrorEl) twofaSetupErrorEl.textContent = "";
      if (twofaEnableBtn) twofaEnableBtn.disabled = true;
      try {
        const setup = await setupTwofa();
        if (twofaManualKeyEl)
          twofaManualKeyEl.textContent = setup.manualEntryKey;
        if (twofaQrImg) {
          const qrUrl = `https://api.qrserver.com/v1/create-qr-code/?size=200x200&data=${encodeURIComponent(
            setup.otpauthUrl,
          )}`;
          twofaQrImg.src = qrUrl;
        }
        setTwofaSetupVisible(true);
        if (twofaSetupCodeInput) twofaSetupCodeInput.focus();
      } catch (err) {
        if (twofaSetupErrorEl) {
          twofaSetupErrorEl.textContent =
            err instanceof Error ? err.message : "Failed to start 2FA setup";
        }
      } finally {
        if (twofaEnableBtn) twofaEnableBtn.disabled = false;
      }
    });
  }

  if (twofaSetupConfirmBtn) {
    twofaSetupConfirmBtn.addEventListener("click", async () => {
      if (!twofaSetupCodeInput) return;
      if (twofaSetupErrorEl) twofaSetupErrorEl.textContent = "";

      const codeValue = twofaSetupCodeInput.value.trim();
      if (!codeValue) {
        if (twofaSetupErrorEl) twofaSetupErrorEl.textContent = "Enter the code";
        return;
      }

      try {
        if (twofaSetupConfirmBtn) twofaSetupConfirmBtn.disabled = true;
        await verifyTwofaSetup(codeValue);

        const fresh = await getMe();
        setCurrentUser(fresh);
        renderTwofaStatus(Boolean(fresh.twofaEnabled));
        refreshNavUserUI();
        setTwofaSetupVisible(false);
      } catch (err) {
        if (twofaSetupErrorEl) {
          twofaSetupErrorEl.textContent =
            err instanceof Error ? err.message : "Failed to enable 2FA";
        }
      } finally {
        if (twofaSetupConfirmBtn) twofaSetupConfirmBtn.disabled = false;
      }
    });
  }

  if (twofaSetupCancelBtn) {
    twofaSetupCancelBtn.addEventListener("click", () => {
      setTwofaSetupVisible(false);
    });
  }

  if (twofaDisableToggleBtn) {
    twofaDisableToggleBtn.addEventListener("click", () => {
      setTwofaDisableVisible(true);
      if (twofaDisableCodeInput) twofaDisableCodeInput.focus();
    });
  }

  if (twofaDisableCancelBtn) {
    twofaDisableCancelBtn.addEventListener("click", () => {
      setTwofaDisableVisible(false);
    });
  }

  if (twofaDisableBtn) {
    twofaDisableBtn.addEventListener("click", async () => {
      if (!twofaDisableCodeInput) return;
      if (twofaDisableErrorEl) twofaDisableErrorEl.textContent = "";

      const codeValue = twofaDisableCodeInput.value.trim();
      if (!codeValue) {
        if (twofaDisableErrorEl)
          twofaDisableErrorEl.textContent = "Enter the code";
        return;
      }

      try {
        if (twofaDisableBtn) twofaDisableBtn.disabled = true;
        await disableTwofa(codeValue);

        const fresh = await getMe();
        setCurrentUser(fresh);
        renderTwofaStatus(Boolean(fresh.twofaEnabled));
        refreshNavUserUI();
        setTwofaDisableVisible(false);
      } catch (err) {
        if (twofaDisableErrorEl) {
          twofaDisableErrorEl.textContent =
            err instanceof Error ? err.message : "Failed to disable 2FA";
        }
      } finally {
        if (twofaDisableBtn) twofaDisableBtn.disabled = false;
      }
    });
  }
}
