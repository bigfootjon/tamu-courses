--- Mon Jan 30 08:55:33 CST 2017

-- someOnes k = [1 | x<-[0..(k-1)] ]
-- someOnes k = take k (repeat 1)
-- someOnes k = replicate k 1
-- someOnes 0 = []
-- someOnes k = [1] ++ someOnes (k-1)

-- f _ = 1
-- someOnes k = map f [1..k]

someOnes k = map (\x -> 1) [1..k]

-------------------------------------------------------

{-
 - ["abcd", "efg", "hi", "dfadfads"] -> ["ab", "ef", "hi", "df"] 
 -}

l = ["abcd", "efg", "hi", "dfadfads"]

shortestListInList ls = minimum $ map length ls
truncAllListsToN ls n = map (take n) ls

listTrunc ls = truncAllListsToN ls (shortestListInList ls)

{-
 - weave [1,2,3,4] [0,9,8,1] -> [ (1,0), (9,2), (3,8) ...]
 -}

weave [] [] = []
weave (l:ls) (m:ms) = (l,m) : weave2 ls ms

-- weave2 [] [] = []
-- weave2 (l:ls) (m:ms) = (m,l) : weave ls ms
weave2 a b = weave b a

id' (a,b) = (a,b)
di (a,b) = (b,a)

iddi 0 = id'
iddi 1 = di

-- makeDiId n = [id, di, id, di...]
makeDiId n = [ iddi (i `mod` 2) | i <- [0..(n-1)] ]
weave' l m = applyFxns (makeDiId (length l)) (zip l m)

listC = [ (i,j) | i <- [1..4], j<-[2..3] ] -- Interesting, but not of use for us.

applyFxns [] _ = []
applyFxns (f:lfs) (a:las) = (f a): applyFxns lfs las

f1 x = x*x 
f2 x = 3*x 
f3 x = 5*x-6 

---- http://robotics.cs.tamu.edu/dshell/cs314/mult/ 

firstList 1 = [1]
firstList n = n:firstList (n `div` 2)

secondList k = [k] ++ secondList (k*2)
-- or this: secondList' k = k:(secondList' (k*2))

grabItems m n = (zip fl sl)
			where	fl = firstList m
			   	sl = secondList n 
multi m n = sum [ (snd x) | x <- grabItems m n, (fst x) `mod` 2 == 1 ]



