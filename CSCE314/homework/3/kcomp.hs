kcomposite :: Integral t => Int -> [t]
kcomposite x = [a | a <- [1..], length (factors a) - 2 == x]

factors x = [a | a <- [1..x], b <- [1..x], a * b == x]
