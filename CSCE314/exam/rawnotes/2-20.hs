-- Mon Feb 20 09:35:45 CST 2017
--
--
import Data.Char

type Parser a = String -> [(a, String)]

symbolSlash :: Parser Char
symbolSlash []  = [] 
symbolSlash (x:xs) 	| x == '/'	= [(x,xs)]
			|	otherwise	= []		

parse p inp = p inp

digit :: Parser Char
digit = \inp -> case inp of
		[]	-> 	[]
		(x:xs)	-> 	if isDigit x then [(x,xs)] else []

doubleDigit = digit `followedBy` digit 

--followedBy :: (Parser Char) -> (Parser Char) -> String -> [(Char, String)]
followedBy :: (Parser Char) -> (Parser Char) -> (Parser Char)
followedBy p1 p2 = \inp -> case (parse p1 inp) of
				[] 	-> 	[]
				[(v,out)] -> parse p2 out 

slashFollowedDigit = symbolSlash `followedBy` digit 

--followedByAndValue :: (Parser Char) -> (Char -> Parser Char) -> (Parser Char)
followedByAndValue :: (Parser a) -> (a -> Parser b) -> (Parser b)
followedByAndValue p1 p2 = \inp -> case (parse p1 inp) of
				[] 	-> 	[]
				[(v,out)] -> parse (p2 v) out 

doubleDigit' = digit `followedByAndValue` (\d -> digit)
-- the value output from the first digit goes into d, but then we don't
--  do anything with it.

returnValue :: a -> Parser a
returnValue v = \inp -> [(v,inp)]

doubleDigit'' = digit `followedByAndValue` (\d -> digit `followedByAndValue`  (\e -> returnValue [d,e]))


