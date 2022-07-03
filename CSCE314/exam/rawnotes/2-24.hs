-- Fri Feb 24 08:57:30 CST 2017--
import Data.Char
import Prelude hiding ((>>=), return)

type Parser a = String -> [(a, String)]
parse p inp = p inp

(>>=) :: Parser a -> (a -> Parser b) -> Parser b
(>>=) p1 p2 = \inp -> case (parse p1 inp) of
			[]		->	[]
			[(v, out)]	->	parse (p2 v) out


(+++) :: Parser a -> Parser a -> Parser a
(+++) p1 p2 = \inp -> case (parse p1 inp) of
			[] 		-> parse p2 inp
			[(v,out)] 	-> [(v,out)]

item :: Parser Char
item = \inp -> case inp of
		[]	->	[]
		(x:xs)	->	[(x,xs)]

return :: a -> Parser a
return v = \inp -> [(v,inp)]

failure :: Parser a
failure = \_ -> []

digit' :: Parser Char
digit' = \inp -> case inp of
		[]	->	[]
		(x:xs)	-> if (isDigit x) then [(x,xs)] else []

char' :: Char -> Parser Char
char' c = \inp-> case inp of
		[]	->	[]
		(x:xs)	-> if (x == c) then [(x,xs)] else []

sat :: (Char -> Bool) -> Parser Char
sat pr = \inp	-> case inp of
		[]	->	[]
		(x:xs)	-> if (pr x) then [(x,xs)] else []

digit = sat isDigit  
notDigit = sat (not.isDigit) -- not.isDigit = \blah -> not(isDigit blah)
char c = sat (== c) 

hyphen = char '-'

-- 24-5466   556-3456

doubleDigit = 	digit >>= \d1 ->
	 	digit >>= \d2 ->
		return [d1,d2]

phoneNum = 	((digit >>= \d -> doubleDigit >>= \dd -> return (d:dd))
			+++ doubleDigit 
		 )>>= \pfx ->
		hyphen >>= \_ ->
		doubleDigit >>= \sfx1 ->
		doubleDigit >>= \sfx2 ->
		return (pfx ++ sfx1 ++ sfx2)

--- How to match ints like this: 61389641, +12323, -13
	
many :: Parser a -> Parser [a]
many p = many1 p +++ return [] -- matches zero or more p's
			-- return [] \= failure

many1 :: Parser a -> Parser [a]  -- matches at least one p's
many1 p = 	p >>= \x ->
		many p >>= \xs ->
		return (x:xs)	

stringToInt :: String -> Int
stringToInt ls | length ls == 1	=	digitToInt (head ls)
	       | otherwise 	= (digitToInt (head ls)) * 10^(length (tail ls)) + (stringToInt (tail ls))
					

plainInt :: Parser Int -- "45" "243334" "3" should not ""
plainInt = (many1 digit) >>= \v -> return (stringToInt v)

ourInt = plainInt +++ (char '+' >>= \_ ->
			plainInt >>= \v ->
			return v) +++ 
		      (char '-' >>= \_ ->
			plainInt >>= \v2 ->
			return (-v2))




