myGcd a 0 = a
myGcd a b = myGcd b (a `mod` b)

isPrime x = and [myGcd i x == 1 | i <- [1..(x-1)]]

primes n = [x | x <- [1..n], isPrime x]

goldbachWorks n = or [p + 2*(x^2) == n | p <- primes n, x <- [0..n]]

goldbachNum = [x | x <- [1..], not (goldbachWorks x) && x `mod` 2 == 1] !! 0
