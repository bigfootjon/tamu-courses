import Data.Char
import Prelude hiding (return, (>>=))

type Parser a = String -> [(a, String)]

parse p inp = p inp

(>>=) :: Parser a -> (a -> Parser b) -> Parser b
(>>=) p1 p2 = \inp -> case parse p1 inp of
			[]	-> 	[]
			[(v, out)] -> 	parse (p2 v) out

return :: a -> Parser a
return v = \inp -> [(v, inp)]

sat :: (Char -> Bool) -> Parser Char
sat p = \inp -> case inp of
		[]	-> 	[]
		(x:xs)	-> if (p x) then [(x,xs)] else []

myParser = sat isAlpha >>= \l ->
           sat (toLower l ==) >>= \u ->
           return [l,u]

