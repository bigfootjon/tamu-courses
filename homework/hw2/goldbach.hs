module Main where

myGcd a 0 = a
myGcd a b = myGcd b (a `mod` b)

isPrime x = and [myGcd i x == 1 | i <- [1..(x-1)]]

primes = [x | x <- [1..], isPrime x]

goldbachWorks n = or [p + 2*x^2 == n | p <- primes, x <- [0..n], p <= n]

goldbachNum = [x | x <- [1..], not (goldbachWorks x)] !! 0

main = do
       print goldbachNum
