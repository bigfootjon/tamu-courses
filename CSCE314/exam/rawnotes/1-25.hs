-- Wed Jan 25 09:06:50 CST 2017
--

sillySgn :: Integer -> Integer
sillySgn x = if x==0 then 0 else
		if x < 0 then -1 else 1

-- can write: if boolean then "string" else "another string"
a = -5
-- testing: if a > 0 then [5,6,7] else []

sillySgn' :: Integer -> Integer
sillySgn' x = if x==0 then 0 else
		if x==1 || x == (-1) then x else
			if x < 0 then sillySgn' (x+1) else sillySgn' (x-1)

f 0 = "hello" -- Reverse order generates a warning. A helpful one at that.
f x = f (x-1)


{-
s x 	| x == 0   = "blah"
	| otherwise = "other value"
-}

myPairEx = (4, "hello") -- pair, 2-tuple
myTripEx = (True, 5, 6.7) -- triple, 3-tuple
myTripEx2 = (5, 6.7, "foo") -- triple, 3-tuple

-- tuples vs. lists
-- pairs: fst -> first, snd -> second

g pr = (fst pr) + 20 -- can take a pair as input
makeTrip n = (n, n*2, n*3)

adder x y = x+y

adder2(x,y) = x+y

incr = adder 1 -- adder is more useful


omit x = 0
-- keep_going 50 = "done"
keep_going x = keep_going (x+1)

{-
  keep_going 12
  keep_going (12+1)
  keep_going 13
  keep_going (13+1)
	...

  keep_going 12
  keep_going (12+1)
  keep_going ((12+1)+1)
  keep_going (((12+1)+1)+1)
	...

-}

-- Laziness is a virtue:
-- take 12 [1..]

l = ["abc", "defg", "ijklm"]

h x y = x + 2*y

--  map (h 100) [3..10]



