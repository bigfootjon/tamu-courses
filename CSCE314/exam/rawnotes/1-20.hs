-- Fri Jan 20 09:18:57 CST 2017

{- Multi line comment
   continues here.
 -}

a = 88; -- semicolon not needed
b = 4

tripler :: Integer -> Integer
tripler x = 3*x

{-
f :: Integer -> Float   -- 
f a = a * 0.25  	-- Won't do this, since it doesn't like Int and Float 
			-- multiplication
			-}

pow3 x = x^3

pow9 :: Integer -> Integer
pow9 x = pow3 (pow3 x)
 			   
pow9' :: Int -> Int
pow9' x = x^9 

{-
The following is by Jon Saxton:


	A Dozen, a Gross, and a Score,
	plus three times the square root of four,
	divided by seven,
	plus five times eleven,
	equals nine squared and not a bit more.

-}

dozen = 12
gross = 144
score = 20

lim = (dozen + gross + score + 3 * sqrt(4.0) ) / 7 + 5 * 11 
lim' = 9^2 + 0.0

poem = (lim == lim')

r1 :: double
r1 = 3.0

r2 :: float
r2 = 3.0

-- compare = (r1 == r2) -- Haskell is strict about comparing double and float too.

