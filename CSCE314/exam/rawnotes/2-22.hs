---
-- Wed Feb 22 09:04:00 CST 2017
--
import Data.Char
import Prelude hiding ((>>=), return)

type Parser a = String -> [(a, String)]
parse p inp = p inp

symbolColon :: Parser Char
symbolColon = \inp -> case inp of
			[]	-> 	[]
			(x:xs)	-> if (x == ':') then [(x,xs)] else []

digit :: Parser Char
digit = \inp -> case inp of
	[]	-> 	[]
	(x:xs)	-> if isDigit x then [(x,xs)] else []

item :: Parser Char
item = \inp -> case inp of
		[]	-> 	[]
		(x:xs)	-> [(x,xs)]

char :: Char -> Parser Char
char c = \inp -> case inp of
		[]	-> 	[]
		(x:xs)	-> if (x == c) then [(x,xs)] else []

followedByAndValue :: Parser a -> (a -> Parser b) -> Parser b
followedByAndValue p1 p2 = \inp -> case (parse p1 inp) of
					[] -> []
					[(v, out)] -> parse (p2 v) out

returnValue :: a -> Parser a
returnValue v = \inp -> [(v,inp)]

doubleDigit = digit `followedByAndValue` (\d -> digit)

doubleDigitv = 	digit `followedByAndValue` (\d -> 
		digit `followedByAndValue` (\e -> 
			returnValue [d,e]))

(>>=) = followedByAndValue -- The bind operator
return = returnValue

doubleDigitv' = digit >>= \d -> 
		digit >>= \e -> 
		return [d,e]

doubleDigitv'' = digit >>= (\d -> (digit >>= (\e -> (return [d,e]))))

oldetimePn = "55-2356"

quadDigits = 	doubleDigitv' >>= \p ->
		doubleDigitv' >>= \q ->
		return (p ++ q)

hyphen = char '-'

oldPnParser = 	doubleDigitv' >>= \prefix ->
		hyphen 	>>= \_ ->
	      	quadDigits >>= \suffix ->
		return (prefix ++ suffix)

newerPn = "345-2345"

newPnParser =   digit         >>= \d ->	
		oldPnParser  >>= \p ->
		return ([d] ++ p)

-- 55-2345 or 234-5467

(+++) :: Parser a -> Parser a -> Parser a
(+++) p1 p2 = \inp -> case parse p1 inp of
			[] -> parse p2 inp
			[(v, out)] -> [(v, out)]

tripleDigit = 	digit >>= \d1 ->
		digit >>= \d2 ->
		digit >>= \d3 ->
		return [d1,d2,d3]

mixedPnParser = (tripleDigit +++ doubleDigitv' ) >>= \prefix ->
		hyphen 	>>= \_ ->
	      	quadDigits >>= \suffix ->
		return (prefix ++ suffix)

-- Order matters here:
mixedPnParser' = (doubleDigitv' +++ tripleDigit) >>= \prefix ->
		hyphen 	>>= \_ ->
	      	quadDigits >>= \suffix ->
		return (prefix ++ suffix)


