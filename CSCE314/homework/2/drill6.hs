flatten :: [[a]] -> [a]
flatten xss = [x | xs <- xss, x <- xs]
