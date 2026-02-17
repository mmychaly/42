const fastify = require('fastify');
const proxy = require('@fastify/http-proxy');

const app = fastify({logger:true});

app.register(require('@fastify/cors'), {
	origin:true,
	credentials: true
});

app.register(require('@fastify/cookie'));

app.register(proxy, {
	upstream: 'http://auth-service:3001',
	prefix: '/api/auth',
	rewritePrefix: '/api/auth',
	http2: false
});

app.register(proxy, {
	upstream: 'http://auth-service:3001',
	prefix: '/api/2fa',
	rewritePrefix: '/api/2fa',
	http2: false
});

app.register(proxy, {
	upstream: 'http://auth-service:3001',
	prefix: '/api/presence',
	rewritePrefix: '/api/presence',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/users',
	rewritePrefix: '/api/users',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/tournament',
	rewritePrefix: '/api/tournament',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/matches',
	rewritePrefix: '/api/matches',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/friend-requests',
	rewritePrefix: '/api/friend-requests',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/chats',
	rewritePrefix: '/api/chats',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/game',
	rewritePrefix: '/api/game',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/health',
	rewritePrefix: '/api/health',
	http2: false
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/ws',
	rewritePrefix: '/ws',
	websocket: true
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/api/socket.io',
	rewritePrefix: '/api/socket.io',
	websocket: true
});

app.register(proxy, {
	upstream: 'http://global-service:3002',
	prefix: '/uploads',
	rewritePrefix: '/uploads',
	http2: false
});

app.listen({ port:3000, host:'0.0.0.0'}, (err) => {
	if (err) {
		app.log.error(err);
		process.exit(1);
	}
	console.log('API Gateway is running');
});
