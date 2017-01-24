doubler x = x + x


summer :: Integer -> Integer -> Integer -- Example of 'curried' function
summer x y = x + y

f' x = summer 4 x -- non-curried
f = summer 4 -- magically currying
-- f :: Integer -> Integer

-- These are actually functions that return their value, NOT variable
-- Therefore these can be considered immutable
dozen = 12
gross = 144

myList = [2,3,8,2,9,-10,0]
myList' = ['c', 'a', 't']

m1 :: [String]
m1 = ["hello", "world", "these", "are", "strings"]
m1' = "ASD" : m1 -- This prepends "ASD" to m1


twiceListLength ls = doubler (length ls)

row1 = [6.2, 5.6, 4.5]
row2 = [0.0, 1.0, -9.5]
matrix1 = [row1, row2] -- i.e. A list of lists

{-
 - head <list> pulls off first element of list and returns it
 - ^ in the case of strings, pulls off first char and returns it
 - tail <list> does the reverse (pulls off first element and returns everything besides the first element)
 -}

-- !! selects nth element
-- ++ concatenates 2 lists

myH :: [a] -> a
myH ls = ls !! 0 -- my version of the head function

{- take returns first n elements of a list
 - drop returns the elements after the first n elements of a list
 -}

{- head ls == take 1 ls
 - Above is false because take returns a list while head returns an element
 -}

pre x ls = x : ls
pp x ls = reverse (x : (reverse ls))

-- sum and product do as expected
