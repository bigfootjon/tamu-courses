--define a new infix operator
(~#~) :: [a] -> [b] -> Bool
(~#~) ls ms = length ls == length ms

(aeq) ls ms = ls ~#~ ms -- not really dependant on anything

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

addPoly :: Polynomial -> Polynomial -> Polynomial
addPoly p1 p2 = addPolyHelper (padToLen p1 l) (padToLen p2 l) 
              where l = max (length p1) (length p2)

addPolyHelper p1 p2 = map (\x -> (fst x + snd x))(zip p1 p2)

padToLen :: Polynomial -> Int -> Polynomial
padToLen p len | (length p) == len = p
               | otherwise         = padToLen (0.0:p) len
