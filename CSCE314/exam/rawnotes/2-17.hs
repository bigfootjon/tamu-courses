---
-- Fri Feb 17 09:09:35 CST 2017

import Data.Char

{-- Consider the URL:
 - 	http://robotics.cs.tamu.edu:80/dshell/test.html
 -
 - 	<URI> := <protocol>://<hostname>[:<port>]<path><filename> 
 - 	<protocol> := "http" | ...
 - 	<hostname> := <host>(<subdomain>)<topleveldomain>
 - 				^-- zero or more.
 -}	

inputString = "http://robotics.cs.tamu.edu:80/dshell/test.html"
data Protocol = Http | Https | Ftp
	deriving Show
type Hostname = String
type Subdomain = String
data TopLevelDomain = Com | Edu | Net
	deriving Show
type Port = Int
type Path = String
type Filename = String

type URI = (Protocol, Hostname, Subdomain, TopLevelDomain, Port, Path, Filename)

{-
uriParser :: String -> URI
uriParser x | (take 5 x) == "https"	=	(Https, "", "", Com, -1, "", "")
	    | (take 4 x) == "http"	=	(Http, "", "", Com, -1, "", "")
            | (take 3 x) == "ftp"	=	(Ftp, "", "", Com, -1, "", "")

First problem: How do we deal with badly formed input?
Solution: Change the type of Parser	
-}
{-
uriParser :: String -> [URI]
uriParser x | (take 5 x) == "https"	=	[(Https, "", "", Com, -1, "", "")]
	    | (take 4 x) == "http"	=	[(Http, "", "", Com, -1, "", "")]
            | (take 3 x) == "ftp"	=	[(Ftp, "", "", Com, -1, "", "")]
	    | otherwise			=	[]

Second problem: This is a monolithic function, what about the rest?
-}

{-
type ProtoParserType = String -> [(Protocol, String)]
protocolParser :: ProtoParserType
protocolParser x 
            | (take 5 x) == "https"	=	[(Https, drop 5 x)]
	    | (take 4 x) == "http"	=	[(Http, drop 4 x)]
            | (take 3 x) == "ftp"	=	[(Ftp, drop 3 x)]
	    | otherwise			=	[]

colonParser :: String -> [(Char,String)]
colonParser [] = []
colonParser (':':xs) = [(':',xs)]

type PortParserType = String -> [(Port, String)]
portParser :: PortParserType
portParser [] = []
-}

type Parser a = String -> [(a, String)]

type ProtoParserType = Parser Protocol
protocolParser :: ProtoParserType
protocolParser x 
            | (take 5 x) == "https"	=	[(Https, drop 5 x)]
	    | (take 4 x) == "http"	=	[(Http, drop 4 x)]
            | (take 3 x) == "ftp"	=	[(Ftp, drop 3 x)]
	    | otherwise			=	[]

colonParser :: Parser Char
colonParser (':':xs) = [(':',xs)]
colonParser _ = []

portParser :: Parser Port
portParser ('8':xs) = [(8,xs)]  -- <-- Will return to this.
portParser _ = []
-- portParser = (\blah -> ( pattern-matching here ))

dotParser1 :: Parser Char
dotParser1 ('.':xs)	=  [('.', xs)]
dotParser1 _		=  []


dotParser :: Parser Char
dotParser inp = case inp of
			('.':xs)	-> [('.', xs)]
			_ -> []

dotParser' :: Parser Char
dotParser' = \inp -> case inp of
			('.':xs)	-> [('.', xs)]
			_ -> []

item :: Parser Char
item = \inp -> case inp of
			(x:xs)	-> [(x, xs)]
			_ -> []
digit :: Parser Char
digit = \inp -> case inp of
			[] -> []	
			(x:xs)	-> if isDigit x then [(x, xs)] else []


{- Want to be able to say: item followedby item 
 - 			   colonParser followedBy slashParser
 - 			   digit followedBy digit
 -  doubleDigit = digit `followedBy` digit
 -}

--followedBy :: Parser Char -> Parser Char -> Parser Char
followedBy :: Parser Char -> Parser Char -> String -> [(Char, String)]
followedBy p1 p2 inp =	case (p1 inp) of
				[]	->	[]
				[(v,out)] -> p2 out


doubleDigit = digit `followedBy` digit

