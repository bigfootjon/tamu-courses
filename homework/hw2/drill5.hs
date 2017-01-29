rotate :: [a] -> Int -> [a]
rotate xs i = drop i xs ++ take i xs
