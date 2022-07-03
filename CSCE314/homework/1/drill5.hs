isRight :: Int -> Int -> Int -> Bool
isRight a b c | a == 0 || b == 0 || c == 0 = False
              | a < 0 || b < 0 || c < 0 = False
              | otherwise = a^2 + b^2 == c^2
