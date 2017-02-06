{- 
 - Last time: type Polynomial = [Double]
 - This time: data <TypeName = A | B | ...
 -}

-- data Bool = False | True
data Color = Red | Orange | Yellow | Green | Blue | Indigo | Violet

data Tern = F | U | T

s :: Tern -> String
s F = "False"
s T = "True"
s U = "Unknown"

tNot :: Tern -> Tern
tNot F = T
tNot U = U
tNot T = F

tAnd :: Tern -> Tern -> Tern
tAnd F _ = F
tAnd _ F = F
tAnd T T = T
tAnd _ _ = U

tOr :: Tern -> Tern -> Tern
tOr T _ = T
tOr _ T = T
tOr F F = F
tOr _ _ = U

{-
 - sum, product, or, length
 -}

ln = [4,8,2,56,8]
lb = [True, True, False]

-- or lb == True

sum' :: [Integer] -> Integer
sum' [] = 0
sum' (x:xs) = x + sum' xs

product' :: [Integer] -> Integer
product' [] = 1
product' (x:xs) = x * product' xs

or' :: [Bool] -> Bool
or' [] = False
or' (x:xs) = x || or' xs

gen op base [] = base
gen op base (x:xs) = x `op` (gen op base xs)

sum'gen ls = gen (+) 0 ls
product'gen ls = gen (\x -> (\y -> x * y)) 1 ls -- Example of using Lambda expressions instead of uncurried multiply: (*)
or'gen ls = gen (||) False ls

-- gen is the same as foldr

-- We write:    but,Actually stored as:
-- [4, 8, 56, 2] == 4:8:56:2:[]

-- foldr # v 4:8:56:2:[] --> 4#(8#(56#(2#(v))))
-- foldl # v 4:8:56:2:[] --> (((v#4)#8)#56)#2
--    where # is an operator, v is the base case

and'foldr ls = foldr (&&) True ls

maxOp x y | x > y = x
          | otherwise = y

myMax ls = foldr (maxOp) 0 ls

-- foldr :: (a -> b -> b) -> b -> [a] -> b

op2 ch sofar = (sofar + 1)
myLength ls = foldr (op2) 0 ls
