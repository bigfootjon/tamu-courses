data Gate = Closed | Open
          deriving (Show, Eq, Ord)

switch :: Gate -> Gate
switch Closed = Open
switch Open   = Closed

value :: Gate -> Int
value Closed = 0
value Open   = 1

waterGate :: Int -> Int
waterGate n = sum [value g | g <- dailyGrind n n]

dailyGrind :: Int -> Int -> [Gate]
dailyGrind n d | d == 0    = initialState n
               | otherwise = [if i `mod` d == 0 then switch g else g | (g,i) <- zip (dailyGrind n (d - 1)) [1..]]

initialState :: Int -> [Gate]
initialState n = [Closed | x <- [1..n]]
