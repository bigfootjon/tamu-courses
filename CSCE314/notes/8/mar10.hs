import Tree
import ListStackADT as Stack -- Could be ListStackADT or StackADT

-- Begin Tree
f :: Tree a -> [a]
f t = fringe t ++ fringe t

-- Begin Stack
s :: StkType Int
s = empty

s'  = push (-6) s
s'' = push 4 $ pop $ push 2 s'

stackSum :: StkType Int -> Int
stackSum s | isEmpty s = 0
           | otherwise = top s + stackSum (pop s)

stackContainsNeg :: (Num a, Ord a) => StkType a -> Bool
stackContainsNeg s | isEmpty s = False
                   | top s < 0 = True
                   | otherwise = stackContainsNeg (pop s)
