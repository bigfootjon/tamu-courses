class WrongNumberOfPlayersError < StandardError ; end
class NoSuchStrategyError < StandardError ; end

def rps_game_winner(game)
	raise WrongNumberOfPlayersError unless game.length == 2
	raise NoSuchStrategyError unless game[0].length == 2 and game[1].length == 2
	p1 = game[0][1].downcase()
	p2 = game[1][1].downcase()
	raise NoSuchStrategyError unless p1 == 'r' or p1 == 'p' or p1 == 's'
	raise NoSuchStrategyError unless p2 == 'r' or p2 == 'p' or p2 == 's'
	if p1 == p2
		return game[0]
	elsif p1 == "r" and p2 == "s"
		return game[0]
	elsif p1 == "p" and p2 == "r"
		return game[0]
	elsif p1 == "s" and p2 == "p"
		return game[0]
	end
	return game[1]
end

def rps_tournament_winner(tournament)
	raise WrongNumberOfPlayersError unless tournament.length == 2
	if tournament[0][0].is_a?(String) and tournament[0][1].is_a?(String)
		return rps_game_winner(tournament)
	else
		winner1 = rps_tournament_winner(tournament[0])
		winner2 = rps_tournament_winner(tournament[1])
		return rps_game_winner([winner1, winner2])
	end
end

puts(rps_tournament_winner(
[
	[
		[ ["Kristen", "P"], ["Dave", "S"] ],
		[ ["Richard", "R"], ["Michael", "S"] ],
	], [
		[ ["Allen", "S"], ["Omer", "P"] ],
		[ ["David E.", "R"], ["Richard X.", "P"] ]
	]
]))

