const { checkAuth } = require('../middleware/checkAuth.js');
const jwt = require('jsonwebtoken');
const { getUserById,
	createTournament,
	createMatch,
	prepareTournament,
	startTournament,
	updateMatch,
	getActiveTournament,
	getAllParticipants,
	getParticipant,
	getAllMatches,
	finishedTournament,
	addGuest,
	addUser,
	updateMatchParticipant,
	updateIndexMatch,
	createPrivateMatch,
	getAllUserPrivateMatches
} = require('../database.js');

function takeplayers(players) {
	const result = [...players];

	for (let i = result.length - 1; i > 0; i--) {
		const j = Math.floor(Math.random() * (i + 1));
		[result[i], result[j]] = [result[j], result[i]];
	}

	return result;
}

function formatParticipant(p) {
	return {
		participantId: p.participant_id,
		alias: p.alias,
		createdBy: p.created_by,
		isGuest: Boolean(p.is_guest)
	};
}

function formatMatch(m) {
	return {
		id: m.id,
		round: m.round,
		order: m.match_order,
		type: m.type,
		status: m.status,
		p1: m.p1 ? formatParticipant(getParticipant(m.p1)) : null,
		p2: m.p2 ? formatParticipant(getParticipant(m.p2)) : null,
		winnerId: m.winner || undefined
	};
}

function formatTournamentResponse(tournament) {
	const participants_list = getAllParticipants(tournament.id);
	const participants = participants_list.map(formatParticipant);

	const matches_list = getAllMatches(tournament.id);
	const matches = matches_list.map(formatMatch);


	return {
		tournament: {
			id: tournament.id,
			status: tournament.status,
			participants: participants,
			matches: matches,
			currentMatchIndex: tournament.currentMatchIndex
		}
	};
}

function getWinner(match, winnerPositoon) {
	if (winnerPositoon === 'p1')
		return match.p1;
	else if (winnerPositoon === 'p2')
		return match.p2;

	return null;
}

function getLoser(match, winnerPositoon) {
	if (winnerPositoon === 'p1')
		return match.p2;
	else if (winnerPositoon === 'p2')
		return match.p1;

	return null;
}

function findNextMatch(matches, currentRound, type) {
	return matches.find(m =>
		m.round === currentRound + 1 &&
		m.type === type &&
		m.status === 'pending'
	);
}

function notifyNextPlayers(tournamentId, io) {
	const matches = getAllMatches(tournamentId);

	let targetMatch = matches.find(m => m.status === 'running');
	if (!targetMatch) {
		targetMatch = matches.find(m => m.status === 'pending' && m.p1 && m.p2);
	}

	if (targetMatch) {
		const p1 = getParticipant(targetMatch.p1);
		const p2 = getParticipant(targetMatch.p2);

		const sendNotification = (player, opponent) => {
			if (!player) return;

			let recipientId = null;
			let summonedName = "You";

			if (!player.is_guest) {
				recipientId = player.participant_id;
			} else {
				recipientId = player.created_by;
				summonedName = player.alias;
			}

			let opponentName = "Opponent";
			if (opponent) {
				opponentName = opponent.alias;
			}

			if (recipientId) {
				io.to(`user_${recipientId}`).emit('tournament_notif', {
					tournamentId: tournamentId,
					opponentName: opponentName,
					summonedName: summonedName
				});
			}
		};

		sendNotification(p1, p2);
		sendNotification(p2, p1);
	}
}
module.exports = async function tournamentRoutes(fastify, options) {

	fastify.get('/api/tournament', async (req, reply) => { //{ preHandler: checkAuth } не был добавлен так как турнир может быть и у не авторизованных пользователей
		let tournament = getActiveTournament();

		if (!tournament) {
			createTournament();
			tournament = getActiveTournament();
		}

		return formatTournamentResponse(tournament);
	});

	fastify.post('/api/tournament/reset', async (req, reply) => {
		const tournament = getActiveTournament();

		if (tournament)
			finishedTournament(tournament.id);//Здесь просто заканчиваем турнир без cбора статы так как мы просто rest не начатый турнир

		createTournament();
		const newTournament = getActiveTournament();

		return formatTournamentResponse(newTournament);
	});


	fastify.post('/api/tournament/participants', async (req, reply) => {
		let currentUserId = null;
		// added authentication via cookie because i couldnt receive the correct "creatorId" used for creating guests
		try {
			const cookieHeader = req.headers.cookie;
			if (cookieHeader) {
				const cookies = fastify.parseCookie ? fastify.parseCookie(cookieHeader) : {};
				const token = cookies['token'] || (req.cookies && req.cookies.token);
				if (token) {
					const decoded = jwt.verify(token, process.env.JWT_SECRET);
					currentUserId = decoded.userId || decoded.id;
				}
			}
		} catch (err) {
			console.log("Error during auth:", err.message);
		}

		const { alias, userId = null } = req.body;

		if (!alias || typeof alias !== 'string') {
			reply.code(400);
			return { error: 'Alias is required' };
		}
		const tournament = getActiveTournament();

		if (!tournament) {
			reply.code(404);
			return { error: "Not have active tournament" };
		}

		if (tournament.status !== 'waiting') {
			reply.code(400);
			return { error: "Tournament not in waiting state" };
		}

		const participants_list = getAllParticipants(tournament.id);

		if (userId !== null) {
			const userAlreadAdd = participants_list.find(m => m.participant_id === userId);
			if (userAlreadAdd) {
				reply.code(400);
				return { error: "This user already add to tournament" }
			}
		} else {
			const aliasExists = participants_list.find(m => m.alias === alias && m.is_guest === 1);
			if (aliasExists) {
				reply.code(400);
				return { error: "This user already add to tournament" }
			}
		}

		if (userId === null) {
			addGuest(alias, tournament.id, currentUserId);
		} else {
			addUser(alias, userId, tournament.id);
		}

		return formatTournamentResponse(tournament);
	});

	fastify.post('/api/tournament/prepare', async (req, reply) => {
		const tournament = getActiveTournament();

		if (!tournament || tournament.status !== 'waiting') {
			reply.code(400);
			return { error: "Tournament not in waiting state" };
		}

		const participants = getAllParticipants(tournament.id);

		if (![4].includes(participants.length)) //ACCEPTED ONLY 4 players
		{
			reply.code(400);
			return { error: "You can game only wath 4 players" };
		}

		const players = takeplayers(participants);
		if (players.length === 4) {
			createMatch(tournament.id, 0, 0, 'regular', players[0].participant_id, players[1].participant_id);
			createMatch(tournament.id, 0, 1, 'regular', players[2].participant_id, players[3].participant_id);

			createMatch(tournament.id, 1, 0, 'third_place', null, null);
			createMatch(tournament.id, 1, 1, 'final', null, null);
		}

		prepareTournament(tournament.id);

		const tournament_upd = getActiveTournament();

		return formatTournamentResponse(tournament_upd);

	});

	fastify.post('/api/tournament/start', async (req, reply) => {
		const tournament = getActiveTournament();

		if (!tournament) {
			reply.code(404);
			return { error: "Not have active tournament" };
		}

		if (tournament.status !== 'prepared') {
			reply.code(400);
			return { error: "Tournament not in prepared state" };
		}

		const matches_list = getAllMatches(tournament.id);

		if (!matches_list || matches_list.length === 0) {
			reply.code(400);
			return { error: 'No matches prepared' };
		}

		const first_match = matches_list.find(m =>
			m.round === 0 && m.match_order === 0
		);

		if (!first_match) {
			reply.code(400)
			return { error: 'First match not found' };
		}

		startTournament(tournament.id, first_match.id);

		const tournament_upd = getActiveTournament(); // Делаем еще раз дабы получить актульные данные
		notifyNextPlayers(tournament_upd.id, fastify.io);
		return formatTournamentResponse(tournament_upd);
	});

	fastify.post('/api/matches/:matchId/finish', async (req, reply) => {
		const matchId = parseInt(req.params.matchId, 10); //Из за того что id стал числом на backend а на фронте все так же string. Конвентируем в число
		const { winner, type } = req.body;

		if (!winner || !['p1', 'p2'].includes(winner)) {
			reply.code(400);
			return { error: 'winner must be p1 or p2' };
		}

		if (!type || type !== 'tournament') {
			reply.code(400);
			return { error: 'Type must to be "tournament"' };
		}

		const tournament = getActiveTournament();
		if (!tournament) {
			reply.code(404);
			return { error: "Not have active tournament" };
		}
		if (tournament.status !== 'running') {
			reply.code(400);
			return { error: "Tournament not in prepared state" };
		}

		const matches_list = getAllMatches(tournament.id);
		if (!matches_list || matches_list.length === 0) {
			reply.code(400);
			return { error: 'No matches found' };
		}

		const current_match = matches_list.find(m =>
			m.id === matchId
		);
		if (!current_match) {
			reply.code(404);
			return { error: 'This match not found in tournament' };
		}

		if (current_match.status !== 'running') {
			reply.code(400);
			return { error: 'This match is not running' };
		}

		const winnerParticipantId = getWinner(current_match, winner);
		const loserParticipantId = getLoser(current_match, winner);
		if (!winnerParticipantId || !loserParticipantId) {
			reply.code(400);
			return { error: 'Invalid participants in match' };
		}

		await updateMatch(matchId, winnerParticipantId, 'finished');

		if (current_match.type === 'regular') //проверяю наличие следущих матчей
		{
			const finalMatch = findNextMatch(matches_list, current_match.round, 'final');
			const thirdplaceMatch = findNextMatch(matches_list, current_match.round, 'third_place')

			if (finalMatch && thirdplaceMatch) {
				if (!finalMatch.p1) //Заполняем участников финального матча
					await updateMatchParticipant(finalMatch.id, 'p1', winnerParticipantId);
				else
					await updateMatchParticipant(finalMatch.id, 'p2', winnerParticipantId);

				if (!thirdplaceMatch.p1) //Заполняем участников финального матча
					await updateMatchParticipant(thirdplaceMatch.id, 'p1', loserParticipantId);
				else
					await updateMatchParticipant(thirdplaceMatch.id, 'p2', loserParticipantId);
			}

			if (tournament.currentMatchIndex == 0)//Переходим ко втрому матчу
			{
				await updateIndexMatch(tournament.id, 1);
				const next_match = matches_list.find(m =>
					m.round === current_match.round && m.match_order === current_match.match_order + 1);
				await updateMatch(next_match.id, null, 'running');
			}
			else if (tournament.currentMatchIndex == 1)//Переходим к матчу за 3е место
			{
				await updateIndexMatch(tournament.id, 2);
				await updateMatch(thirdplaceMatch.id, null, 'running');
			}
		}
		else if (current_match.type === 'third_place') {
			const finalMatch = matches_list.find(m =>
				m.round === current_match.round &&
				m.type === 'final'
			);

			if (finalMatch) //Переходим к финальному матчу
			{
				await updateIndexMatch(tournament.id, 3);
				await updateMatch(finalMatch.id, null, 'running');
			}
		}
		else if (current_match.type === 'final') {
			await updateIndexMatch(tournament.id, null);
			await finishedTournament(tournament.id);
		}

		if (tournament.status === 'running') {
			notifyNextPlayers(tournament.id, fastify.io);
		}

		const tournament_upd = getActiveTournament(); // Делаем еще раз дабы получить актульные данные

		if (!tournament_upd) {
			return {
				tournament: {
					id: tournament.id,
					status: 'finished',
					participants: getAllParticipants(tournament.id).map(formatParticipant),
					matches: getAllMatches(tournament.id).map(formatMatch),
					currentMatchIndex: null
				}
			};
		}

		return formatTournamentResponse(tournament_upd);

	});

	fastify.post('/api/game/private', { preHandler: checkAuth }, async (req, reply) => {
		const inviter_id = req.user.id;
		const { invited_id } = req.body;

		const inviter = getUserById(inviter_id);
		const inviterName = inviter ? inviter.username : "Player";

		if (!invited_id) {
			reply.code(400);
			return { error: 'invited_id is required' };
		}
		if (inviter_id === invited_id) {
			reply.code(400);
			return { error: 'You cannot invite yourself' };
		}

		// Create the match in DB
		const privateMatchId = createPrivateMatch(inviter_id, invited_id);

		// We send a message to the invited user's
		fastify.io.to(`user_${invited_id}`).emit('game_invite', {
			roomId: privateMatchId,
			inviterId: inviter_id,
			inviterName: inviterName
		});
		return { privateMatchId };
	});

	// I havent used this
	fastify.get('/api/game/private', { preHandler: checkAuth }, async (req, reply) => {
		const userId = req.user.id;

		const allprivateMatches = getAllUserPrivateMatches(userId);

		return { allprivateMatches };
	});
}

/*
1 match reg
-winer final /p1
-loser 3eme/p1

2 match reg
-winer final /p2
-loser 3eme/p2

3 match 3eme
- winer

4 match final
- winer

*/
