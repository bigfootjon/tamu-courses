-- Fri Jan 27 09:00:29 CST 2017

mySum (x,y) = x + y
myDiv (x,y) = x / y

myListLength [] = 0
myListLength (x:xs) = 1 + (myListLength xs)

myListLength2 [] = 0
myListLength2 (x:xs) 	| xs == []		= 1
			| otherwise		= 1 + (myListLength2 xs)	

myListLength3 ls 	| ls == []		= 0
			| otherwise		= 1 + (myListLength3 (tail ls))	


list1 = ["This", "is", "a", "list", "of", "Strings"]
{-
 mLL ["This", "is", "a", "list", "of", "Strings"]
	-> x = "This", xs = ["is", "a", "list", "of", "Strings"]
		1 + mLL xs 
 -
 -}
list2 = [1..6]
list3 = ['a', 'b', 'c', 'd', 'e', 'f']

t1 [] [] [] = []
t1 xs ys zs = (head xs, head ys, head zs) : t1 (tail xs) (tail ys) (tail zs)

t2 = zip3

t3 [] _ _ = []

t3 (x:xs) (y:ys) (z:zs) = (x, y, z): t3 xs ys zs

myMap _ [] = []

myMap f (l:ls) = (f l):myMap f ls

cube x = x^3

listOCubes = map cube [1..]

listOCube3 = [cube x | x<-[1..] ]

listOCubeEven = [cube x | x<-[1..], x `mod` 2 == 0 ]

{-
fil chk ls -> elements in ls that pass check in chk, i.e., filters
chk :: a -> Bool
ls :: [a]
fil :: (a -> Bool) -> [a] -> [a]

e.g.
 fil evenChk listOCubes

-}

evenChk x = (x `mod` 2 == 0)

fil _ [] = []
fil chk (l:ls) 	| (chk l) 	= l:(fil chk ls)
		| otherwise	= (fil chk ls)

fil2 chk ls = [ x | x <- ls, chk x ]

sqrs = map (\x -> x^2) [1..99]

