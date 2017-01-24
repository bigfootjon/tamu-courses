getFirsts :: [(a, a)] -> [a]
getFirsts ((a, b):xs) = a : getFirsts xs
getFirsts _ = []
