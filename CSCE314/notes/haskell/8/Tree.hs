module Tree (Tree(Leaf, Branch), fringe) where

data Tree a = Leaf a | Branch (Tree a) (Tree a)

mytree :: Tree Int
mytree = Branch (Leaf 78) (Leaf 12)

fringe :: Tree a -> [a]
fringe (Leaf l) = [l]
fringe (Branch l r) = fringe l ++ fringe r
