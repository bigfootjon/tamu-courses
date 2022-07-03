midList :: [a] -> [a]
midList xs = drop 1 (reverse (drop 1 (reverse xs)))
