import Data.Char

uppercaseList :: String -> [(Bool, Bool, Bool)]
uppercaseList s | length s > 0 = (isUpper (head s), isLower (head s), isDigit (head s)) : uppercaseList (tail s)
                | otherwise = []
