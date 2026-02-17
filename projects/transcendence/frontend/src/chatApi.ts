// Chat Types
export interface Chat {
	id: number;
	created_at: string;
	other_user_id: number;
	other_username: string;
	other_display_name: string;
	other_avatar_url: string | null;
	last_message_content: string | null;
	last_message_at: string | null;
	blocked_by_me: number | boolean;
	blocked_by_other: number | boolean;
}

export interface Message {
	id: number;
	chat_id: number;
	sender_id: number;
	content: string;
	created_at: string;
	username: string;
	display_name: string;
	avatar_url: string | null;
}

// --- API Functions ---
export async function getMyChats(): Promise<Chat[]> {
	const res = await fetch("/api/chats", {
		method: "GET",
		credentials: "include",
	});
	if(!res.ok) throw new Error("Failed to fetch chats");
	return res.json();
}

export async function getChatMessages(
	chatId: number,
	limit = 50,
	offset = 0
): Promise<Message[]> {
	const res = await fetch(
		`/api/chats/${chatId}/messages?limit=${limit}&offset=${offset}`,
		{
			method: "GET",
			credentials: "include",
		}
	);
	if(!res.ok) throw new Error("Failed to fetch messages");
	return res.json();
}

export async function createChat(otherUserId: number): Promise<Chat> {
	const res = await fetch(`/api/chats/with/${otherUserId}`, {
		method: "POST",
		credentials: "include",
	});
	if(!res.ok) {
		const err = await res.json();
		throw new Error(err.message || "Failed to create chat");
	}
	return res.json();
}

export async function sendMessage(
	chatId: number,
	content: string
): Promise<Message> {
	const res = await fetch(`/api/chats/${chatId}/messages`, {
		method: "POST",
		headers: { "Content-Type": "application/json" },
		credentials: "include",
		body: JSON.stringify({ content }),
	});

	if(!res.ok) {
		const err = await res.json();
		throw new Error(err.message || "Failed to send message");
	}
	return res.json();
}
