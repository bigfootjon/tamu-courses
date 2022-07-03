import Data.Char
import Prelude hiding (return, (>>=))

type Parser a = String -> [(a, String)]

parse p inp = p inp

(>>=) :: Parser a -> (a -> Parser b) -> Parser b
(>>=) p1 p2 = \inp -> case (parse p1 inp) of
                        []         -> []
                        [(v, out)] -> parse (p2 v) out

return :: a -> Parser a
return v = \inp -> [(v,inp)]

(+++) :: Parser a -> Parser a -> Parser a
(+++) p1 p2 = \inp -> case (parse p1 inp) of
                        []        -> parse p2 inp
                        [(v,out)] -> [(v,out)]

item :: Parser Char
item = \inp -> case inp of
                 [] -> []
                 (x:xs) -> [(x,xs)]

failure :: Parser a
failure =  \_ -> []

digitOld :: Parser Char
digitOld = \inp -> case inp of
                    [] -> []
                    (x:xs) -> if isDigit x then [(x,xs)] else []

charOld :: Char -> Parser Char
charOld  c = \inp -> case inp of
                       [] -> []
                       (x:xs) -> if x == c then [(x,xs)] else []

-- Checks if the element satisfies a given function
sat :: (Char -> Bool) -> Parser Char
sat pr = \inp -> case inp of
                   [] -> []
                   (x:xs) -> if pr x then [(x,xs)] else []

digit = sat isDigit
notDigit = sat (not . isDigit)

char c = sat (==c)

doubleDigit = digit >>= \d1 ->
              digit >>= \d2 ->
              return [d1, d2]

phoneNum = ((doubleDigit >>= \s ->
                   digit >>= \t ->
                   return (t:s)) +++ doubleDigit) >>= \pfx  ->
           char '-'    >>= \_    ->
           doubleDigit >>= \sfx1 ->
           doubleDigit >>= \sfx2 ->
           return (pfx ++ sfx1 ++ sfx2)

many :: Parser a -> Parser [a]
many p = many1 p +++ return []

many1 :: Parser a -> Parser [a]
many1 p = p      >>= \x ->
          many p >>= \xs ->
          return (x:xs)

stringToInt :: String -> Int
stringToInt xs = read xs

plainInt :: Parser Int
plainInt = (many1 digit) >>= \v -> return (stringToInt v)

outInt = (plainInt) +++
         (char '+' >>= \_ ->
          plainInt >>= \v ->
          return v) +++
         (char '-' >>= \_ ->
          plainInt >>= \v2 ->
          return (-v2))
