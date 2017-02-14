removeDuplicate :: Eq a => [a] -> [a]
removeDuplicate [] = []
removeDuplicate (x:xs) = x : removeDuplicate (filter (/=x) xs)
