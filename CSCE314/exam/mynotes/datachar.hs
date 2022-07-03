isControl :: Char -> Bool -- Char is non-printed
isSpace :: Char -> Bool -- Char is a space (' ', \t, \r, ...)
isLower :: Char -> Bool -- Char is lowercase
isUpper :: Char -> Bool -- Char is uppercase
isAlpha :: Char -> Bool -- Char is a letter of alphabet (same as isLetter)
isAlphaNum :: Char -> Bool -- Char is a letter or number
isPrint :: Char -> Bool -- Char can be printed (Unicode)
isDigit :: Char -> Bool -- Char is numeric (0 - 9)
isOctDigit :: Char -> Bool -- Char is octal numeric (0 - 7)
isHexDigit :: Char -> Bool -- Char is hex numeric (0 - 9, a - f, A - F)
isLetter :: Char -> Bool -- Char is a latter of alphabet (same as isAlpha)
isMark :: Char -> Bool -- Char is a unicode combining mark
isNumber :: Char -> Bool -- Char is a decimal in any script (0 - 9, roman, etc.)
isPunctuation :: Char -- Char is any type of punctuation
isSymbol :: Char -> Bool -- Char is a mathy-type symbol
isSeparator :: Char -> Bool -- Char separates things
isAscii :: Char -> Bool -- Char is from ASCII set
isLatin1 :: Char -> Bool -- Char is from Latin-1 set
isAsciiUpper :: Char -> Bool -- Char is ASCII uppercase
isAsciiLower :: Char -> Bool -- Char is ASCII lowercase

toUpper :: Char -> Char -- a -> A, A -> A, ? -> ?
toLower :: Char -> Char -- A -> a, a -> a, ? -> ?
toTitle :: Char -> Char -- same as toUpper, can differ for some scripts

digitToInt :: Char -> Int -- '1' -> 1, 'f' -> 15, 'c' -> Exception
intToDigit :: Int -> Char -- 1 -> '1', 15 -> 'f' (not possible to get 'F')


