-- Wed Feb  8 09:09:48 CST 2017

-- Last time in 314: foldr

-- foldrLen ls = <length of a list> via foldr

l1 = [5,8,2,19]

op x y = x + y
foldrLen ls = foldr op 0 ls
-- gives sum not len
-- [5,8,2,19] -> 5:8:2:19:[]
--            -> 5 `op` (8 `op`  (2 `op` (19 `op` 0)))

-- op x y = x/x + y/y
op' _ y = 1 + y

foldrLen' ls = foldr op' 0 ls
-- [5,8,2,19] -> 5:8:2:19:[]
--            -> 5 `op` (8 `op`  (2 `op` (19 `op` 0)))

op2 x y = 1 + x
foldrLen2 ls = foldr op2 0 ls
foldrLen3 ls = foldl op2 0 ls
-- [5,8,2,19] -> 5:8:2:19:[]
--            -> ((0 `op2` 5) `op2` 8) `op2` 2 ... 19

op3 x y = 1 + y
foldrLen4 ls = foldl op3 0 ls

----------------------

lenA [] = 0
lenA (_:xs) = 1 + lenA xs
{- 
 - 	lenA [1,9,6,4] (and I have a reason to need the value)
 -	  = 1 + lenA [9,6,4]
 -	  = 1 + 1 + lenA [6,4]
 -	  = 1 + 1 + 1 + lenA [4]
 -	  = 1 + 1 + 1 + 1 + lenA []
 -	  = 1 + 1 + 1 + 1 + 0
 -	  = 4
 -}

lenB ls = lenHelper 0 ls
		where 	lenHelper c [] = c
			lenHelper c (_:xs) = lenHelper (c+1) xs	
{-
 - 	lenB [1,9,6,4] (and I have a reason to need the value)
 - 		= lenHelper 0 [1,9,6,4]
 - 		= lenHelper 1 [9,6,4]
 - 		= lenHelper 2 [6,4]
 - 		= lenHelper 3 [4]
 - 		= lenHelper 4 []
 - 		= 4
 -          ^
 - --- This | isn't quite right.
 -
  - 	lenB [1,9,6,4] (and I have a reason to need the value)
 - 		= lenHelper 0 [1,9,6,4]
 - 		= lenHelper (0+1) [9,6,4]
 - 		= lenHelper ((0+1)+1) [6,4]
 - 		= lenHelper (((0+1)+1)+1) [4]
 - 		= lenHelper ((((0+1)+1)+1)+1) []
 - 		= ((((0+1)+1)+1)+1)
 - 		= 4
 -
-}

f a b = b
-- seq a b = b (but also, get me the value of a)

lenC ls = lenHelper 0 ls
		where 	lenHelper c [] = c
			lenHelper c (_:xs) = let s=(c+1) 
						in s `seq` (lenHelper s xs)

{-
  - 	lenC [1,9,6,4] (and I have a reason to need the value)
 - 		= lenHelper 0 [1,9,6,4]
 - 		= lenHelper 1 [9,6,4]
 - 		= lenHelper 2 [6,4]
 - 		= lenHelper 3 [4]
 - 		= lenHelper 4 []
 - 		= 4
 -
-}


