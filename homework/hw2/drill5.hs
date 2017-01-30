rotate :: [a] -> Int -> [a]
rotate xs i = drop j xs ++ take j xs
            where j | length xs > 0 = i `mod` (length xs)
                    | otherwise = 0
