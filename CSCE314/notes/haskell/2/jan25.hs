sillySgn :: Integer -> Integer
sillySgn x = if x == 0 then 0 else
                if x < 0 then -1 else 1

-- Writing if bool then "string" else "anther string"
-- This is allowed because it will use automatic type inference.

sillySgn' :: Integer -> Integer
sillySgn' x = if x==0 then 0 else
                 if x==1 || x == (-1) then x else
                    if x < 0 then sillySgn' (x+1) else sillySgn (x-1)

myPairEx = (4, "hello")
myTripEx = (True, 5, 6.7)
myTripEx2 = (5, 6.7, "foo")

-- pairs: fst -> first element, snd -> second element

g pr = (fst pr) + 20 -- can take a pair as input
makeTrip n = (n, n*2, n*3)

addr x y = x + y

addr2(x,y) = x+y

incr = addr 1 -- curried function that increments anything by 1

omit x = 0
--keep_going 50 = "done"
keep_going x = keep_going (x+1)

{-
 - omit (keep_going 1) will immeditatly evaluate to 0, even if the case keep_going 50 case is uncommented
 - take 12 [1..] will not execute forever (despite [1..] going on forever on its own) due to lazy execution
 - map reverse ["abc", "def"] -> ["cba", "fed"] -- map takes a function to apply to a list
 - 
 -}

h x y = x + 2*y
-- map h [3..10] -- this fails because h expects 2 arguments
-- map (h 100) [3..10]] --this works because the result of "h 100" only expects 1 argument now

