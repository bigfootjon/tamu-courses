altSeries :: Num a => [a] -> a
altSeries (x:xs) = x - altSeries xs
altSeries [] = 0
