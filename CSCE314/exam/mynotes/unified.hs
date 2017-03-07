import Prelude hiding ((>>=), return)

a = 88; -- semicolon optional
b = 4

pow3 x = x^3 -- ^ is power

myHead ls = ls !! 0 -- get first element

prepend x ls = x : ls

signOf x = if x == 0 then 0 else
              if x < 0 then -1 else 1

tupleEx = (4, "hello", True)

-- curry:
adder x y = x + y

incr  = adder 1 -- half applied function

incr' = (+1) -- operator section

sq_list  ls = map (\x -> x^2) ls -- lambda
sq_list' ls = map (^2)        ls -- op section

{-
someOnes k = map (\_ -> 1) [1..k]
someOnes k = [1 | _<-[1..k]]
someOnes k = take k (repeat 1)
someOnes k = replicate k 1

someOnes 0 = []
someOnes k = 1 : someOnes (k-1) -- prepend
someOnes k = [1] ++ someOnes (k-1) -- concat
-}

truncLists n ls = map (take n) ls

myZip (l:ls) (m:ms) = (l, m) : myZip ls ms

llength ls ms = length ls == length ms
(~#~) ls ms = ls `llength` ms

type Polynomial = [Double]

data RPS = Rock | Paper | Scissors
         deriving (Eq)

instance Show RPS where
    show Rock = "Rock"
    show Paper = "Paper"
    show Scissors = "Scissors"

sum' [] = 0
sum' (x:xs) = x + sum' xs
-- sum `equiv` foldrSum
foldrSum ls = foldr (+) 0 ls

-- foldr # v [1,2,3] --> 1#(2#(3#v))
-- foldl # v [1,2,3] --> ((v#1)#2)#3

class Flippable a where
     flp :: a -> a

flipWholeList :: (Flippable a) => [a] -> [a]
flipWholeList = map flp

instance Flippable Bool where
        flp = not

data OwnList a = Nil | Cons a (OwnList a)

instance (Show a) => Show (OwnList a) where
    show Nil = "<>"
    show (Cons x xs) = (show x) ++ " ; " ++ (show xs)
