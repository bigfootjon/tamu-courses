--- Wed Feb  1 09:07:03 CST 2017

l = [(1,4), (3,4), (5,8), (9,8) ]
--- -> [1, 3, 5, 9] 

-- pieces: 	1. how break the problem down.
--		2. how to put sub-solutions back together.
--		3. how to solve small sub-problems.

-- 1. break list the beginning and the rest
-- 2. concatenating lists
-- 3. fst

getFirsts :: [(a,b)] -> [a]
getFirsts [] = []
getFirsts (l:[]) = [fst l]
getFirsts ls = (getFirsts (take 1 ls)) ++ (getFirsts (drop 1 ls))

fst3 (a,_,_) = a
mid (a,b,c) = b

{-
 - "hello" -> [('h,'h','h'), ('e','e','e'), etc.]
 -  h -> (h,h,h)
 -}

-- g c = (c,c,c)

f3 [] = []
f3 (l:ls) = (l,l,l):f3 (ls)

f4 [] = []
f4 (l:ls) = (l,l,l,l):f4 (ls)

-- This can't be done with the strictness of the type system, as 
-- 	2-tuples are distinct types from 3-tuples. What would be
-- 	on the r.h.s. of gn's type declaration?
--
-- gn n c -> (c,c,c, ... c)  -- n of those
-- gn n c (defined in terms of) gn (n-1) c
-- fn n list ->  ...
--
-- fn n list ->  [[]]

mergeSort :: [Integer] -> [Integer]

mergeSort [] = []
mergeSort (e:[]) = [e]
-- mergeSort ls = ... < try fill this in using the function >

merge2SortedLists :: [Integer] -> [Integer] -> [Integer]
merge2SortedLists [] ls = ls
merge2SortedLists ls [] = ls
merge2SortedLists (n:ns) (m:ms) 	| n < m		= n : merge2SortedLists ns (m:ms)
					| otherwise 	= m : merge2SortedLists (n:ns) ms 


