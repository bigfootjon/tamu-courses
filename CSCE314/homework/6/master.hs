import Data.List

data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a
              deriving Show

type HuffmanTree = Tree (Char,Int) Int

-- huffmanCode :: String -> [(Char, String)]
huffmanCode cs = helper freqTable
               where freqTable = reverse (map (\x -> Leaf (head x, length x)) (group (sort cs)))
                     helper ((Leaf (xc,xi)):(Leaf (yc,yi)):ls) = helper $ Branch (xi + yi) (Leaf (xc, xi)) (Leaf (yc, yi)) : ls
