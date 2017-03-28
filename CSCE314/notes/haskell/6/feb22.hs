import Data.Char
import Prelude hiding ((>>=), return)

type Parser a = String -> [(a, String)]

parse p inp = p inp

{-
symbolColon :: Parser Char
symbolColon = \inp -> case inp of
                         (':':xs) -> [(':',xs)]
                         _        -> []
-}
symbolColon :: Parser Char
symbolColon = item ':'


item :: Char -> Parser Char
item c = \inp -> case inp of
                   (c:xs) -> [(c,xs)]
                   _      -> []

digit :: Parser Char
digit = \inp -> case inp of
                  []     -> []
                  (x:xs) -> if isDigit x then [(x,xs)] else []


followedByAndValue :: Parser a -> (a -> Parser b) -> Parser b
followedByAndValue p1 p2 = \inp -> case (parse p1 inp) of
                                     [] -> []
                                     [(v, out)] -> parse (p2 v) out

returnValue :: a -> Parser a
returnValue v = \inp -> [(v, inp)]

(>>=) = followedByAndValue -- Bind operator (defined in Prelude, we redefine it here, see import statement for hiding)
return = returnValue

doubleDigit = digit `followedByAndValue` (\_ -> digit)
doubleDigitv = digit `followedByAndValue` (\d ->
               digit `followedByAndValue` (\e ->
               returnValue [d,e]))


doubleDigitv' = digit >>= \d ->
                digit >>= \e ->
                return [d,e]

oldetimePn = "55-2356"

quadDigits = doubleDigitv' >>= \p ->
             doubleDigitv' >>= \q ->
             return (p ++ q)

oldPnParser = doubleDigitv' >>= \prefix ->
              item '-'      >>= \_ ->
              quadDigits    >>= \suffix ->
              return (prefix ++ suffix)

tripleDigit = digit >>= \d1 ->
              digit >>= \d2 ->
              digit >>= \d3 ->
              return [d1,d2,d3]

newerPn = "345-2345"

newPnParser = tripleDigit >>= \prefix ->
              item '-'    >>= \_ ->
              quadDigits  >>= \suffix ->
              return (prefix ++ suffix)

(+++) :: Parser a -> Parser a -> Parser a
(+++) p1 p2 = \inp -> case parse p1 inp of
                        [] -> parse p2 inp
                        [(v, out)] -> [(v, out)]
mixedPnParser = (tripleDigit +++ doubleDigitv) >>= \prefix ->
                item '-' >>= \_ ->
                quadDigits >>= \suffix ->
                return (prefix ++ suffix)
