-- 6.1
palindrome :: Eq a => [a] -> Bool
palindrome xs = reverse xs == xs

-- 6.2
fls :: [[a] -> [a]]
fls = [take 12]

-- 6.3
tripler :: (a -> a) -> a -> a
tripler f x = f ( f ( f x ) )

