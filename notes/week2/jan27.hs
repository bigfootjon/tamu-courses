mySum (x,y) = x + y

myListLength (x:xs) = 1 + myListLength xs
myListLength [] = 0

list1 = ["this", "is", "a", "list", "of", "strings"]

list2 = [1..6]
list3 = ['a', 'b', 'c', 'd', 'e', 'f']

t3 [] _ _ = []

t3 (x:xs) (y:ys) (z:zs) = (x, y, z) : t3 xs ys zs

myMap _ [] = []
myMap f (l:ls) = (f l):myMap f ls

cube x = x^3
listOCubes = map cube [1..]

listOCubes3 = [cube x | x <- [1..10]] -- List comprehensions

listOCubesEven = [cube x | x <- [1..10], x `mod` 2 == 0]

myFilter :: (a -> Bool) -> [a] -> [a]
myFilter f (l:ls) | f l = l : myFilter f ls
                  | otherwise = myFilter f ls
myFilter _ [] = []

myFilterComp f ls = [x | x <- ls, f x]

evenCheck x = (x `mod` 2 == 0)

sqrs = map (\x -> x^2) [1..99] -- (\var -> content) is a lambda expression


