data RPS = Rock | Paper | Scissors
    deriving Eq

rps :: RPS -> RPS -> Int

rps Rock Rock = 0
rps Paper Paper = 0
rps Scissors Scissors = 0
rps Rock Scissors = 1
rps Rock Paper = 2
rps Paper Rock = 1
rps Paper Scissors = 2
rps Scissors Paper = 1
rps Scissors Rock = 2

rps' :: RPS -> RPS -> Int

rps' p1 p2 | p1 == Rock && p2 == Rock = 0
           | p1 == Paper && p2 == Paper = 0
           | p1 == Scissors && p2 == Scissors = 0
           | p1 == Rock && p2 == Scissors = 1
           | p1 == Rock && p2 == Paper = 2
           | p1 == Paper && p2 == Rock = 1
           | p1 == Paper && p2 == Scissors = 2
           | p1 == Scissors && p2 == Rock = 1
           | p1 == Scissors && p2 == Rock = 2
