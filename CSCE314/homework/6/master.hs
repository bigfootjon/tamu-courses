import Data.List

data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a
              deriving Show

type HuffmanTree = Tree (Char,Int) Int

sortFt :: [Tree (Char, Int) Int] -> [Tree (Char, Int) Int]
sortFt ls = sortOn doSort ls
       where doSort (Branch b _ _) = b+1
             doSort (Leaf (_, a)) = a

traverseFt :: (Tree (Char, a) a) -> Char -> String
traverseFt (Branch _ l r) c | length (traverseFt l c) > 0 = traverseFt l c ++ "0"
                            | length (traverseFt r c) > 0 = traverseFt r c ++ "1"
                            | otherwise                   = ""
traverseFt (Leaf (a, _))  c | c == a    = "!"
                            | otherwise = ""

-- huffmanCode :: String -> [(Char, String)]
huffmanCode cs = convertString freqTable $ head $ buildTree $ sortFt $ freqTable
               where freqTable = reverse (map (\x -> Leaf (head x, length x)) (group (sort cs)))
                     buildTree (c0:c1:[]) =             sortFt $ [Branch (sumFt c0 c1) c0 c1]
                     buildTree (c0:c1:ls) = buildTree $ sortFt $ Branch (sumFt c0 c1) c0 c1 : ls
                     sumFt (Leaf (_, l))  (Leaf (_, r))  = l + r
                     sumFt (Leaf (_, l))  (Branch r _ _) = l + r
                     sumFt (Branch l _ _) (Leaf (_, r))  = l + r
                     sumFt (Branch l _ _) (Branch r _ _) = l + r
                     convertString ft tree = reverse $ map (\(Leaf (c, _)) -> (c, reverse $ drop 1 $ traverseFt tree c)) ft
