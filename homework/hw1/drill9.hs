halfList :: [a] -> [a]
halfList xs | length xs >= 2 = head xs : halfList (tail (tail xs))
            | length xs == 1 = xs
            | otherwise = []
