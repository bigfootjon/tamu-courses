altSeries :: Num a => [a] -> a
altSeries xs | mod (length xs) 2 == 0 && length xs > 0 = head xs - altSeries (tail xs)
             | mod (length xs) 2 == 1 && length xs > 0 = head xs - altSeries (tail xs)
             | otherwise = 0
