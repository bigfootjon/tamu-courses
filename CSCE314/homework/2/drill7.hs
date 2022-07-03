isPalindrome :: Eq a => [a] -> Bool
isPalindrome xs = and [x == y | (x, y) <- zip xs ys]
                  where ys = reverse xs
