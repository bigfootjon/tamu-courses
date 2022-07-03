-- Mon Feb 13 09:00:01 CST 2017

data Gate = Ajar | Shut
--	deriving (Show)
	deriving (Read, Eq, Ord)

g1 = Ajar
g2 = Shut

prettyPrinter :: Gate -> String
prettyPrinter Ajar = "open"
prettyPrinter Shut = "closed"

-- show :: Gate -> String
-- show Ajar = "a"
-- show Shut = "b"

instance Show Gate where
	show g = prettyPrinter g

flipGate :: Gate -> Gate
flipGate Ajar = Shut
flipGate _ = Ajar


data Color = Red | Orange | Yellow | Green | Blue | Indigo | Violet
	deriving (Show, Read, Eq, Ord, Enum, Bounded)
c1 = Orange
c2 = Blue

lc = [Red .. Blue] -- Enum
rainbow = [( minBound :: Color ) .. ( maxBound :: Color )]

-- flipList :: Int -> [Bool] -> [Bool]
-- flipList :: Int -> [Gate] -> [Gate]
-- flipList :: (Flippable a) => Int -> [a] -> [a]

flipWholeList :: (Flippable a) => [a] -> [a]
flipWholeList = map flp

class Flippable a where
	flp :: a -> a

instance Flippable Gate where
	flp = flipGate

instance Flippable Bool where
	flp = not

instance Flippable Color where
	flp Red = Violet
	flp Violet = Red 

------
data OwnList a = Nil | Cons a (OwnList a)

instance (Show a) => Show (OwnList a) where
	show Nil = "<>"	
	show (Cons x xs) = (show x) ++ " ; " ++ (show xs)
	
ol1 = Cons 56 (Cons 4 (Cons 9 Nil))

ownHead :: (OwnList a) -> a
ownHead (Cons x xs) = x

sumOwnList :: (OwnList Integer) -> Integer
sumOwnList Nil = 0
sumOwnList (Cons x xs) = x + (sumOwnList xs)

data DList a b = DNil | DConsA a (DList a b) | DConsB b (DList a b) 
instance (Show a, Show b) => Show (DList a b) where
	show DNil = "[]"	
	show (DConsA x xs) = (show x) ++ "_A ; " ++ (show xs)
	show (DConsB y ys) = (show y) ++ "_B ; " ++ (show ys)
	
dl1 = DConsA 'h' (DConsA 'e' (DConsB Ajar (DConsA 'l' (DConsB Shut DNil))))

-- This is where we want to get to:
-- define a type to represent the expression 
--   5 + 6 * 8
data Expr 	= Val Int
		| Add Expr Expr
		| Mul Expr Expr
	-- deriving (Show)

e1 = Add (Val 1) (Mul (Val 2) (Val 3))
e2 = Mul (Val 9) (Add (Val 8) (Val 6))

instance Show Expr where
	show (Val v) = show v
	show (Add s1 s2) = (show s1) ++ "+" ++ (show s2)
	show (Mul s1 s2) = (show s1) ++ "*" ++ (show s2)

