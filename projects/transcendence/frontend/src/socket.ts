type Socket = any;

let socket: Socket | null = null;

export function getSocket(): Socket | null {
	return socket;
}

export async function connectSocket(): Promise<Socket | null> {
	if (socket && socket.connected) {
		return socket;
	}

	try {
		// We import the socket directly from the URL because the normal way was not working wtf, ts ignore is for typescript to allow us
		// @ts-ignore
		const module = await import("https://cdn.socket.io/4.7.5/socket.io.esm.min.js");
		const io = module.io;

		// Initialize the socket connection
		socket = io("/", {
			path: "/api/socket.io",
			withCredentials: true,
			autoConnect: false,
			reconnection: true,
			transports: ["polling"],
			upgrade: false
		}) as Socket;

		socket.on("connect", () => {
			console.log("Chat socket connected successfully:", socket.id);
		});
		// socket.on("connect_error", (err: any) => {
		// 	console.error("Chat socket connection error:", err.message);
		// });
		// socket.on("disconnect", (reason: any) => {
		// 	console.log("Chat socket disconnected:", reason);
		// });

		socket.connect();
		return socket;

	} catch (error) {
		console.error("Failed to load socket.io client:", error);
		return null;
	}
}

export function disconnectSocket() {
	if (socket) {
		socket.disconnect();
		socket = null;
	}
}
