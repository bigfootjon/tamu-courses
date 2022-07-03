-- Mon Feb  6 09:03:30 CST 2017

{-
 	Last time: "type Polynomial = [Float]
	Today: "data <TypeName> = A|...
 -}

-- data Bool = False | True

data Colors = R | O | Y | G | B | I | V

-- Kleene's "3-valued" logic

data Tern = F | U | T

tNot :: Tern -> Tern
tNot F = T
tNot T = F
tNot U = U

tAnd :: Tern -> Tern -> Tern
tAnd F _ = F
tAnd _ F = F
tAnd T T = T
tAnd _ _ = U

tOr :: Tern -> Tern -> Tern
tOr F F = F
tOr T _ = T
tOr _ T = T
tOr _ _ = U

s :: Tern -> String
s F = "False"
s U = "Unknown"
s T = "True"

{- 
  sum, product, or*, length
 -}
ln = [4,8,2,56,8]
lb = [True, True, False]

sum' :: [Integer] -> Integer
sum' [] = 0
sum' (x:xs) = x + sum' xs

prod' :: [Integer] -> Integer
prod' [] = 1
prod' (x:xs) = x * prod' xs

or' :: [Bool] -> Bool
or' [] = False
or' (x:xs) = x || (or' xs)

gen op base [] = base
gen op base (x:xs) = x `op` (gen op base xs)

sum2 ls = gen (+) 0 ls
prod2 ls = gen (\x -> (\y -> x*y)) 1 ls

-- gen == foldr
-- [4,8,56,2] == 4:(8:(56:(2:[]))) == 4:8:56:2:[]
-- foldr # v 4:8:56:2:[] --> 4#(8#(56#(2#v))) --> 4#8#56#2#v

-- foldr (+) 0 4:8:56:2:[] -> 4+8+56+2+0

-- and2 [b1, b2, b3 ..., bn] = b1 ^ b2 ^ b3 ^ ... ^ bn ^ True
and2 :: [Bool] -> Bool
and2 ls = foldr (&&) True ls

andop x y = x && y
and2' ls = foldr andop True ls
-- A consequence of our defns here is that and2' [] == True

{- Given: A non-empty list of non-negative numbers.
 - Computer: the maximum element.
 - Approach: using foldr
 -}

myMax :: [Integer] -> Integer
myMax ls = foldr maxop 0 ls

maxop x y = if x > y then x else y

myMax' ls = foldr maxo' 0 ls
			where maxo' = \x -> (\y -> (if x > y then x else y))

-- foldr # v 4:8:56:2:[] --> 4#(8#(56#(2#v))) --> 4#8#56#2#v
-- foldl # v 4:8:56:2:[] --> (((v#4)#8)#56)#2 

-- Question: What is the type of foldr?
-- foldr :: (x -> x -> x) -> x -> [x] -> x (almost, but not quite)

op2 ch sofar = (sofar + 1)

myLength ls = foldr (op2) 0 ls

-- "abc" -> ['a','b','c'] -> 'a':'b':'c':[]
-- op2 ('a' op2('b' op2('c' 0)))

-- Next time: "seq"


