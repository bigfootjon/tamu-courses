data Gate = Ajar | Shut
        --deriving Show -- see 'instance' clause below

instance Show Gate where
    show Ajar = "open"
    show Shut = "closed"

flipGate Ajar = Shut
flipGate Shut = Ajar

data Color = Red | Orange | Yellow | Green | Blue | Indigo | Violet
           deriving (Show, Read, Eq, Ord, Enum, Bounded)

c1 = Orange
c2 = Blue

lc = [Red .. Blue]
rainbow = [(minBound :: Color) .. (maxBound :: Color)]

flipWholeList :: (Flippable a) => [a] -> [a]
flipWholeList = map flp -- flp is in the scope of flippable

class Flippable a where -- Declare a type class that always has the function flp
    flp :: a -> a

instance Flippable Gate where -- Define flp for Gate to make Gate a Flippable type
    flp = flipGate

data OwnList a = Nil | Cons a (OwnList a)

instance (Show a) => Show (OwnList a) where -- restricts showing this to when a is showable
    show a = "[" ++ helper a ++ "]" -- Begin Jon tangent
           where helper Nil = ""
                 helper (Cons x Nil) = show x
                 helper (Cons x xs) = show x ++ "," ++ helper xs -- end Jon tangent

ol1 = Cons 56 (Cons 4 (Cons 9 Nil))

-- See Dr. Shell notes for a more complex example of a List thingy
