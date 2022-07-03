countChar :: Char -> String -> Int
countChar c s | length s == 0 = 0
              | head s == c = 1 + countChar c (tail s)
              | otherwise = 0 + countChar c (tail s)
