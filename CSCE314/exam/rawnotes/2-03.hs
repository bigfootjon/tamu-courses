--- Fri Feb  3 09:01:44 CST 2017

-- [a,b,c,d,e]  -> [a, a+b, a+b+c, a+b+c+d, etc.]
--    lst 	->  output

{-
	sumSoFar = 0;
	for (int i = 0; i < lst.size(); i++)
	{
		sumSoFar += lst[i];
		output[i] = sumSoFar;
	}
-}

l = [1..5]

cSum :: [Integer] -> [Integer]
cSum lst = cSumHelper 0 0 lst

cSumHelper sumSoFar i lst = if i < (length lst) then sumSoFar':(cSumHelper sumSoFar' (i+1) lst) else []
					where sumSoFar' = sumSoFar + (lst!!i)


sameLength :: [a] -> [b] -> Bool
sameLength ls ms = length ls == length ms

(~#~) :: [a] -> [b] -> Bool
(~#~) ls ms = length ls == length ms

-- Exercise: write an approx equal for two floating point numbers.


-- String == [Char]
-- type <NewType> = <OldType>
type Polynomial = [Double]

f :: Polynomial
f = [2,0,7,16]

p :: Polynomial
p = [18,0,17,-6]

q :: Polynomial
q = [1,3]

evalPoly :: Polynomial -> Double -> Double
evalPoly [] x = 0.0
evalPoly p x = (head p)*x^e + evalPoly (tail p) x
			where e = (length p)-1
-- Exercise: try write the above without the ^ 

addPoly :: Polynomial -> Polynomial -> Polynomial
addPoly p1 p2 = addPolyHelper (padToLen p1 l) (padToLen p2 l) 
				where l = max (length p1) (length p2)

addPolyHelper p1 p2 = map (\x -> (fst x + snd x))(zip p1 p2)

padToLen :: Polynomial -> Int -> Polynomial
padToLen p len 	| (length p) == len  	=	p
		| otherwise		= 	padToLen (0.0:p) len


