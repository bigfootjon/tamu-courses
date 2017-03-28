-- this is a comment

{- Multi line comment
   See?
 - Nice to have matching indention, so convention is to use a " -" to match
 -}

-- Variable definitions
a = 88; -- Semicolons are optional
b = 4

tripler :: Integer -> Integer -- This is the definition of what types the arguments can be
tripler x = 3 * x -- Notice how terse the definition of a function is

{- Typing system prevents Floats * Integers:
 - f :: Integer -> Float
 - f a = a * 0.25
 -}

-- Interactive compiler is not a strict compiler for Haskell

-- This will tell the type of `foo` in the interpreter
-- :type foo

pow3 x = x^3

pow9 :: Integer -> Integer
pow9 x = pow3 (pow3 x)

pow9' :: Int -> Int
pow9' x = x^9

-- Int != Integer
-- Int is one machine word integer
-- Integer is arbitrary precision

-- :! foo (run shell command foo)
-- :cd path (change dir)

-- (see limerick):

dozen = 12
gross = 144
score = 20

lim = (dozen + gross + score + 3 * sqrt(4.0)) / 7 + 5 * 11
lim' = 9^2 + 0.0

poem = (lim == lim')
