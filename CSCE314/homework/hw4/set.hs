type Set a = [a]

isElement _ [] = False
isElement n (x:xs) | n == x    = True
                   | otherwise = isElement n xs

mkset :: Eq a => [a] -> Set a
mkset [] = []
mkset (x:xs) = if isElement x xs then mkset xs else x : mkset xs

subset :: Eq a => Set a -> Set a -> Bool
subset [] ol = True
subset (s:sl) ol = if isElement s ol then subset sl ol else False

setEqual :: Eq a => Set a -> Set a -> Bool
setEqual [] [] = True
setEqual [] _  = False
setEqual _ []  = False
setEqual (a:al) (b:bl) = if a == b then setEqual al bl else False

setProd :: (Eq t, Eq t1) => Set t -> Set t1 -> Set (t, t1)
setProd [] _ = []
setProd (x:xs) ls = helper x ls ++ setProd xs ls
                  where helper _ [] = []
                        helper x (l:ls) = (x, l) : helper x ls

bits 0 = []
bits i = i `mod` 2 : bits (i `quot` 2)

bitIndexes bs = helper $ reverse bs
              where helper [] = []
                    helper (b:bs) = if b == 1 then length bs : helper bs else helper bs

punch i xs = helper xs
           where helper [] = []
                 helper (x:xs) = if isElement (length xs) bis then x : helper xs else helper xs
                 bis = bitIndexes $ bits i 

punch' i xs = punch (2^(length xs) - 1 - i) xs

partitionSet :: Eq t => Set t -> Set (Set (Set t))
partitionSet xs = [xs] : [punch i xs : punch' i xs : [] | i <- [1..(2^(length xs)-2)]]

bellNum :: Int -> Int
bellNum x = length $ partitionSet [1..x]
