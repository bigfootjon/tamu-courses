coprime :: Integral a => a -> a -> Bool
coprime x y = 1 == myGcd x y

myGcd :: Integral a => a -> a -> a
myGcd a 0 = a
myGcd a b = myGcd b (a `mod` b)
