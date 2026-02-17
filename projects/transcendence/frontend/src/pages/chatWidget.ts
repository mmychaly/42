import { getCurrentUser } from "../authStore.js";
import { connectSocket } from "../socket.js";
import { createChat, getMyChats, getChatMessages, sendMessage, Chat, Message } from "../chatApi.js";

let currentCleanup: (() => void) | null = null;

export const ChatWidget = () => `
	<!-- Chat Widget -->
	<div class="fixed bottom-6 right-6 z-[100] flex flex-col items-end gap-4">
	  <div id="chat-window" class="hidden w-80 h-96 bg-slate-900 border border-slate-700 rounded-lg shadow-2xl flex flex-col overflow-hidden transition-all">
		<div class="p-3 bg-slate-800 border-b border-slate-700 flex items-center justify-between shrink-0">
		  <div class="flex items-center gap-2">
			<button id="chat-back-btn" class="hidden text-slate-400 hover:text-white">
			  <svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="m15 18-6-6 6-6"/></svg>
			</button>
			<h3 id="chat-title" class="font-bold text-sm text-slate-100">Chats</h3>
		  </div>
		  <button id="chat-close-btn" class="text-slate-400 hover:text-white">
			<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M18 6 6 18"/><path d="m6 6 12 12"/></svg>
		  </button>
		</div>
		<div class="relative flex-1 overflow-hidden bg-slate-900">
		  <div id="chat-list-view" class="absolute inset-0 overflow-y-auto p-2 space-y-1"></div>
		  <div id="chat-conversation-view" class="absolute inset-0 flex flex-col bg-slate-900 translate-x-full transition-transform duration-200">
			<div id="chat-messages" class="flex-1 overflow-y-auto p-3 space-y-2 bg-slate-950/30"></div>
			<form id="chat-form" class="p-2 border-t border-slate-700 flex gap-2 bg-slate-900 shrink-0">
			  <input type="text" id="chat-input" class="flex-1 bg-slate-800 border border-slate-600 rounded px-2 py-1 text-sm text-slate-100 focus:outline-none focus:border-blue-500" placeholder="Type..." autocomplete="off">
			  <button type="submit" class="bg-blue-600 hover:bg-blue-500 text-white px-3 py-1 rounded text-sm">Send</button>
			</form>
		  </div>
		</div>
	  </div>
	  <button id="chat-toggle-btn" class="h-14 w-14 rounded-full bg-blue-600 hover:bg-blue-500 text-white shadow-lg flex items-center justify-center transition-transform hover:scale-105">
		<span id="chat-notification-badge" class="hidden absolute top-0 right-0 h-3 w-3 bg-red-500 rounded-full border-2 border-white z-50"></span>		
	 	<svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
		  <path d="M21 15a2 2 0 0 1-2 2H7l-4 4V5a2 2 0 0 1 2-2h14a2 2 0 0 1 2 2z"/>
		</svg>
	  </button>
	</div>
`;

export function setupChatWidget(options?: { onUserClick?: (userId: number) => void }) {
	
	if (currentCleanup) {
        currentCleanup();
        currentCleanup = null;
    }

	const me = getCurrentUser();

	// Html elements
	const chatWindow = document.getElementById("chat-window");
	const chatToggleBtn = document.getElementById("chat-toggle-btn");
	const chatCloseBtn = document.getElementById("chat-close-btn");
	const chatBackBtn = document.getElementById("chat-back-btn");
	const chatTitle = document.getElementById("chat-title");
	const chatListView = document.getElementById("chat-list-view");
	const chatConversationView = document.getElementById("chat-conversation-view");
	const chatMessages = document.getElementById("chat-messages");
	const chatForm = document.getElementById("chat-form") as HTMLFormElement;
	const chatInput = document.getElementById("chat-input") as HTMLInputElement;
	const chatNotificationBadge = document.getElementById("chat-notification-badge");

	let activeChatId: number | null = null;
	const renderedMessageIds = new Set<number>();
	const unreadChatIds = new Set<number>();
	let socket: any = null;

	// Scrolls to the bottom in order to display the most recent messages
	const scrollToBottom = () => {
		if(chatMessages) chatMessages.scrollTop = chatMessages.scrollHeight;
	};

	// Creates the html for a single message (a div containing the "bubble") and appends it to the converstaion
	const appendMessage = (msg: Message) => {
		if(!chatMessages || renderedMessageIds.has(msg.id)) return;
		renderedMessageIds.add(msg.id);

		const isMe = me ? msg.sender_id === Number(me.id) : false;
		const div = document.createElement("div");
		div.className = `flex flex-col ${isMe ? "items-end" : "items-start"}`;

		const bubble = document.createElement("div");
		bubble.className = `max-w-[85%] px-3 py-2 rounded-lg text-sm break-words ${isMe ? "bg-blue-600 text-white" : "bg-slate-700 text-slate-200"
			}`;
		bubble.textContent = msg.content;

		const meta = document.createElement("span");
		meta.className = "text-[10px] text-slate-500 mt-1";
		meta.textContent = new Date(msg.created_at).toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' });

		div.appendChild(bubble);
		div.appendChild(meta);
		chatMessages.appendChild(div);
	};

	// Updates the list of messages in the conversation (given the new messages)
	const renderMessages = (messages: Message[]) => {
		if(!chatMessages) return;
		chatMessages.innerHTML = "";
		renderedMessageIds.clear();
		messages.forEach(appendMessage);
		scrollToBottom();
	};

	// Updates the list of conversations (givent the new ones)
	const renderChatList = (chats: Chat[]) => {
		if(!chatListView) return;
		chatListView.innerHTML = "";
		if(chats.length === 0) {
			chatListView.innerHTML = `<p class="text-xs text-slate-500 text-center mt-4">No chats found.</p>`;
			return;
		}

		// for each conversation theres a button (inside a div)
		chats.forEach(chat => {
			const btn = document.createElement("div");
			btn.className = "relative w-full text-left p-2 rounded hover:bg-slate-800 flex items-center gap-2 transition-colors cursor-pointer group";

			const avatar = document.createElement("div");
			avatar.className = "w-8 h-8 rounded-full bg-slate-700 flex items-center justify-center text-xs font-bold text-slate-300 shrink-0 overflow-hidden";

			if(options?.onUserClick) {
				avatar.classList.add("cursor-pointer", "hover:opacity-80");
				avatar.onclick = (e) => {
					e.stopPropagation(); //to not open the chat (like clicking on the rest of the row)
					options.onUserClick!(chat.other_user_id);
				};
			}

			if(chat.other_avatar_url) {
				const img = document.createElement("img");
				img.src = chat.other_avatar_url;
				img.className = "w-full h-full object-cover";
				avatar.appendChild(img);
			} else {
				avatar.textContent = (chat.other_display_name || chat.other_username || "?")[0].toUpperCase();
			}

			const info = document.createElement("div");
			info.className = "flex-1 min-w-0";
			const name = document.createElement("p");
			const isUnread = unreadChatIds.has(chat.id);
			name.className = "text-sm font-semibold text-slate-200 truncate";
			name.textContent = chat.other_display_name || chat.other_username;

			info.appendChild(name);
			btn.appendChild(avatar);
			btn.appendChild(info);

			if(isUnread) {
				const unreadDot = document.createElement("div");
				unreadDot.className = "w-2.5 h-2.5 bg-red-500 rounded-full shrink-0 mr-2";
				btn.appendChild(unreadDot);
			}

			if(!chat.blocked_by_me && !chat.blocked_by_other) {
				const inviteBtn = document.createElement("button");
				inviteBtn.className = "px-2 py-1 rounded text-xs font-semibold bg-yellow-600 hover:bg-yellow-500 text-white opacity-0 group-hover:opacity-100 transition-opacity";
				inviteBtn.textContent = "Invite";
				inviteBtn.onclick = async (e) => {
					e.stopPropagation();
					inviteBtn.disabled = true;
					inviteBtn.textContent = "...";
					try {
						const res = await fetch("/api/game/private", {
							method: "POST",
							headers: { "Content-Type": "application/json" },
							credentials: "include",
							body: JSON.stringify({ invited_id: chat.other_user_id }),
						});
						if(!res.ok) throw new Error();
						inviteBtn.textContent = "Sent";
						const data = await res.json();
						window.location.href = `/game/room/${data.privateMatchId}`;
						setTimeout(() => { inviteBtn.disabled = false; inviteBtn.textContent = "Invite"; }, 2000);
					} catch {
						inviteBtn.textContent = "Error";
						setTimeout(() => { inviteBtn.disabled = false; inviteBtn.textContent = "Invite"; }, 2000);
					}
				};
				btn.appendChild(inviteBtn);
			}

			btn.onclick = () => selectChat(chat);
			chatListView.appendChild(btn);
		});
	};

	// Opens the chat after you click on a user from the lsit
	const selectChat = async (chat: Chat) => {
		unreadChatIds.delete(chat.id);
		activeChatId = chat.id;
		if(chatTitle) chatTitle.textContent = chat.other_display_name || chat.other_username;
		if(chatBackBtn) chatBackBtn.classList.remove("hidden");
		if(chatConversationView) chatConversationView.classList.remove("translate-x-full");

		const isBlockedByMe = !!chat.blocked_by_me;
		const isBlockedByOther = !!chat.blocked_by_other;
		const isBlocked = isBlockedByMe || isBlockedByOther;

		const sendBtn = chatForm?.querySelector("button");

		if(chatInput) {
			chatInput.value = ""; // Clear text
			if(isBlockedByMe) {
				chatInput.disabled = true;
				chatInput.classList.add("opacity-50", "cursor-not-allowed");
				chatInput.placeholder = "You blocked this user..";
			} else if(isBlockedByOther) {
				chatInput.disabled = true;
				chatInput.classList.add("opacity-50", "cursor-not-allowed");
				chatInput.placeholder = "This user blocked you..";
			} else {
				chatInput.disabled = false;
				chatInput.classList.remove("opacity-50", "cursor-not-allowed");
				chatInput.placeholder = "Type...";
				chatInput.focus();
			}
		}

		if(sendBtn) {
			sendBtn.disabled = isBlocked;
			if(isBlocked) sendBtn.classList.add("opacity-50", "cursor-not-allowed");
			else sendBtn.classList.remove("opacity-50", "cursor-not-allowed");
		}

		if(chatMessages) chatMessages.innerHTML = `<div class="text-slate-500 text-xs text-center mt-4">Loading messages...</div>`;

		try {
			const messages = await getChatMessages(chat.id);
			renderMessages(messages);
		} catch(err) {
			console.error("Failed to load messages:", err);
			if(chatMessages) chatMessages.innerHTML = `<div class="text-red-400 text-xs text-center mt-4">Failed to load messages</div>`;
		}
	};

	// Gets the new chats from API and passes to renderChatList
	const loadChats = async () => {
		if(!chatListView) return;
		try {
			const chats = await getMyChats();
			renderChatList(chats);
		} catch(err) {
			console.error(err);
			chatListView.innerHTML = `<p class="text-red-400 text-xs text-center mt-4">Error loading chats</p>`;
		}
	};


	// called by the socket.on(private_message)
	const handlePrivateMessage = (payload: any) => {
		// Check if the user has the chat already open
		const isChatOpen = !chatWindow?.classList.contains("hidden");
		const isLookingAtChat = activeChatId === payload.chatId;

		if(isLookingAtChat && isChatOpen) {
			appendMessage({
				id: payload.id || Date.now(),
				chat_id: payload.chatId,
				sender_id: payload.senderId,
				content: payload.message,
				created_at: payload.timestamp,
				username: "...",
				display_name: "...",
				avatar_url: null
			});
			scrollToBottom();
		} else {
			// Show the notification badge if user not on chat
			if(chatNotificationBadge) chatNotificationBadge.classList.remove("hidden");
			unreadChatIds.add(payload.chatId);
			if(chatWindow && !chatWindow.classList.contains("hidden")) {
				void loadChats();
			}
		}
	}

	// Event Listener for Game Invites
	const handleGameInvite = (payload: any) => {
		// Sets up a simple HTML popup notification
		const popup = document.createElement("div");
		popup.className = "fixed top-16 right-6 z-[200] w-72 bg-slate-800 border border-slate-600 rounded-lg shadow-xl p-4 animate-in fade-in slide-in-from-right-5";

		const inviterName =
			typeof payload.inviterName === "string" && payload.inviterName.trim().length > 0
				? payload.inviterName
				: "Unknown";
		const inviterInitial = inviterName.trim().charAt(0).toUpperCase() || "?";

		const wrapper = document.createElement("div");
		wrapper.className = "flex items-start gap-3";

		const avatar = document.createElement("div");
		avatar.className = "h-10 w-10 rounded-full bg-blue-600 flex items-center justify-center text-white font-bold shrink-0";
		avatar.textContent = inviterInitial;

		const body = document.createElement("div");
		body.className = "flex-1";

		const title = document.createElement("h4");
		title.className = "text-sm font-bold text-white";
		title.textContent = inviterName;

		const subtitle = document.createElement("p");
		subtitle.className = "text-xs text-slate-300 mb-3";
		subtitle.textContent = "Challenged you to Pong!";

		const actions = document.createElement("div");
		actions.className = "flex gap-2";

		const acceptBtn = document.createElement("button");
		acceptBtn.type = "button";
		acceptBtn.className = "flex-1 bg-green-600 hover:bg-green-500 text-white text-xs font-bold py-1.5 rounded transition-colors";
		acceptBtn.textContent = "Accept";

		const declineBtn = document.createElement("button");
		declineBtn.type = "button";
		declineBtn.className = "px-3 py-1.5 text-xs text-slate-400 hover:text-white transition-colors";
		declineBtn.textContent = "Decline";

		actions.appendChild(acceptBtn);
		actions.appendChild(declineBtn);
		body.appendChild(title);
		body.appendChild(subtitle);
		body.appendChild(actions);
		wrapper.appendChild(avatar);
		wrapper.appendChild(body);
		popup.appendChild(wrapper);
		document.body.appendChild(popup);

		// Handle Accept
		acceptBtn.addEventListener("click", () => {
			// Redirect to the game page with the private ID
			window.location.href = `/game/room/${payload.roomId}`;
			popup.remove();
		});

		// Handle Decline
		declineBtn.addEventListener("click", () => {
			socket.emit("game_decline", {
				inviterId: payload.inviterId,
				roomId: payload.roomId
			});
			popup.remove();
		});

		// Auto-remove after 15 seconds
		setTimeout(() => {
			if(document.body.contains(popup)) popup.remove();
		}, 15000);
	}

	// Tournament notification
	const handleTournamentNotif = (payload: any) => {
		const popup = document.createElement("div");
				popup.className = "fixed top-16 right-6 z-[200] w-72 bg-purple-900 border border-purple-600 rounded-lg shadow-xl p-4 animate-in fade-in slide-in-from-right-5";

				const closeBtn = document.createElement("button");
				closeBtn.className = "absolute top-2 right-2 text-purple-300 hover:text-white transition-colors";
		closeBtn.innerHTML = `
			<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
				<path d="M18 6 6 18"/><path d="m6 6 12 12"/>
			</svg>
		`;
		closeBtn.onclick = () => popup.remove();
		popup.appendChild(closeBtn);

		const wrapper = document.createElement("div");
		wrapper.className = "flex items-start gap-3";

		const iconDiv = document.createElement("div");
		iconDiv.className = "h-10 w-10 rounded-full bg-purple-500 flex items-center justify-center text-white font-bold shrink-0";
		iconDiv.innerHTML = `<svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M6 9H4.5a2.5 2.5 0 0 1 0-5H6"/><path d="M18 9h1.5a2.5 2.5 0 0 0 0-5H18"/><path d="M4 22h16"/><path d="M10 14.66V17c0 .55-.47.98-.97 1.21C7.85 18.75 7 20.24 7 22"/><path d="M14 14.66V17c0 .55.47.98.97 1.21C16.15 18.75 17 20.24 17 22"/><path d="M18 2H6v7a6 6 0 0 0 12 0V2Z"/></svg>`;
		wrapper.appendChild(iconDiv);

		const contentDiv = document.createElement("div");
		contentDiv.className = "flex-1";

		const title = document.createElement("h4");
		title.className = "text-sm font-bold text-white";
		title.textContent = "Tournament Match!";

		const message = document.createElement("p");
		message.className = "text-xs text-purple-200 mb-3";

		const subject = payload.summonedName === "You" ? "You are" : `${payload.summonedName} is`;

		message.appendChild(document.createTextNode(`${subject} up next against `));

		const opponentSpan = document.createElement("span");
		opponentSpan.className = "font-bold text-white";
		opponentSpan.textContent = payload.opponentName;
		message.appendChild(opponentSpan);

		const goBtn = document.createElement("button");
		goBtn.className = "w-full bg-purple-500 hover:bg-purple-400 text-white text-xs font-bold py-1.5 rounded transition-colors";
		goBtn.textContent = "Go to Lobby";

		contentDiv.appendChild(title);
		contentDiv.appendChild(message);
		contentDiv.appendChild(goBtn);
		wrapper.appendChild(contentDiv);
		popup.appendChild(wrapper);
		document.body.appendChild(popup);

		goBtn.addEventListener("click", () => {
			window.location.href = "/tournament";
			popup.remove();
		});
	}

	const handleGameDeclined = (payload: any) => {
		// we send alert only if the user is waiting in the game room
		if(window.location.pathname.includes("/game/room/")) {
			alert("Your invitation was declined.");
			window.location.href = "/game";
		}
	}

	const cleanup = () => {
        if (socket) {
            console.log("Cleaning up old Chat Widget listeners...");
            socket.off("private_message", handlePrivateMessage);
            socket.off("game_invite", handleGameInvite);
            socket.off("tournament_notif", handleTournamentNotif);
            socket.off("game_declined", handleGameDeclined);
        }
    };

	currentCleanup = cleanup;

	// EVENT LISTENERS
	// Initialise the socket
	void connectSocket().then(s => {
		socket = s;
		if(socket) {
			// we close them first to make sure we dont have 2 open at the same time
			socket.off("private_message");
			socket.on("private_message", handlePrivateMessage);

			socket.off("game_invite");
			socket.on("game_invite", handleGameInvite);				

			socket.off("tournament_notif");
			socket.on("tournament_notif", handleTournamentNotif);

			socket.off("game_declined");
			// Listen for declined invites
			socket.on("game_declined", handleGameDeclined);
		}
	});

	// Chat "toggle button" logic, to open it and close
	if(chatToggleBtn) {
		chatToggleBtn.addEventListener("click", () => {
			if(chatWindow) chatWindow.classList.toggle("hidden");

			// When you open the chat you take out the red dot
			if(chatNotificationBadge && !chatWindow?.classList.contains("hidden")) {
				chatNotificationBadge.classList.add("hidden");
			}

			if(chatWindow && !chatWindow.classList.contains("hidden")) {
				void loadChats();
			}
		});
	}

	if(chatCloseBtn) {
		chatCloseBtn.addEventListener("click", () => {
			if(chatWindow) chatWindow.classList.add("hidden");
		});
	}

	// Back button hides the conversation "tab"
	if(chatBackBtn) {
		chatBackBtn.addEventListener("click", () => {
			activeChatId = null;
			if(chatConversationView) chatConversationView.classList.add("translate-x-full");
			if(chatBackBtn) chatBackBtn.classList.add("hidden");
			if(chatTitle) chatTitle.textContent = "Chats";
			void loadChats();
		});
	}

	// Submit a message, sends it to API and appends it in conversation
	if(chatForm) {
		chatForm.addEventListener("submit", async (e) => {
			e.preventDefault(); //to stop the page from regfreshing
			if(!activeChatId || !chatInput.value.trim()) return;

			const content = chatInput.value;
			chatInput.value = "";

			try {
				const sentMsg = await sendMessage(activeChatId, content);
				appendMessage(sentMsg);
				scrollToBottom();
			} catch(err) {
				console.error("Failed to send", err);
			}
		});
	}

	return {
		// Function made just for that "Message" button in Friedns.ts
		openChatWithUser: async (userId: number) => {
			const chat = await createChat(userId);
			if(chatWindow) chatWindow.classList.remove("hidden");
			void loadChats();
			void selectChat(chat);
		},

		cleanup: () => {
			cleanup();
			currentCleanup = null;
		}
	};
}
