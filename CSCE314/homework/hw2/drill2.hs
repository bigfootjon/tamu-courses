isElement :: Eq a => a -> [a] -> Bool
isElement a xs = 0 < length [x | x <- xs, a == x]
