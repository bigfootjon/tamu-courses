{- basic defs:
 - someOnes k = [1 | x <- [1..k]]
 - someOnes k = take k (repeat 1)
 - someOnes k = replicate k 1
 - someones 0 = []; someOnes k = [1] ++ someOnes (k-1)
 -}

-- using lambda expression
someOnes k = map (\x -> 1) [1..k]

shortestListInList xs = minimum $ map length xs -- $ is implied parens from $ to end

listTrunc xs = map (\s -> take n s) xs
             where n = shortestListInList xs

weave_co1 [] [] = []
weave_co1 (x:xs) (y:ys) = (x, y) : weave_co2 xs ys

weave_co2 [] [] = []
weave_co2 (x:xs) (y:ys) = (y, x) : weave_co1 xs ys

weave [] [] = []
weave (x:xs) (y:ys) = (x, y) : weave ys xs

applyFxns [] _ = []
applyFxns (f:lfs) (a:las) = (f a) : applyFxns lfs las

id' (a,b) = (a,b)
di' (a,b) = (b,a)

iddi 0 = id'
iddi 1 = di'

makeDiId n = [ iddi (i `mod` 2) | i <- [0..(n-1)]]
weave' l m = applyFxns (makeDiId (length l - 1)) (zip l m)

firstList 1 = [1]
firstList n = n:firstList (n `div` 2)

secondList k = [k] ++ secondList (k*2)

