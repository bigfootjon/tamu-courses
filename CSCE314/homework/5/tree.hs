import Debug.Trace

data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a

mytree = Branch "A" (Branch "B" (Leaf (1::Int)) (Leaf (2::Int))) (Leaf (3::Int))

instance (Show a, Show b) => Show (Tree a b) where
    show (Branch b tl tr) = show b ++ ":{" ++ show tl ++ ", " ++ show tr ++ "}"
    show (Leaf a) = show a

preorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
preorder fa fb (Branch b tl tr) = [fb b] ++ preorder fa fb tl ++ preorder fa fb tr
preorder fa fb (Leaf a) = [fa a]

inorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
inorder fa fb (Branch b tl tr) = inorder fa fb tl ++ [fb b] ++ inorder fa fb tr
inorder fa fb (Leaf a) = [fa a]

postorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
postorder fa fb (Branch b tl tr) = postorder fa fb tl ++ postorder fa fb tr ++ [fb b]
postorder fa fb (Leaf a) = [fa a]

measureWater :: Int -> Int -> Int -> Bool
measureWater jug1 jug2 target = helper jug1 jug2 target (0, 0) || helper jug2 jug1 target (0, 0)
    where helper j1 j2 t (cl, cr) = c jt_fill || c jt_tran || c jt_emty || c jt_trn2 || if cl == fst jt_trn2 && cr == snd jt_trn2 then False else helper j1 j2 t jt_trn2
                         where c jt = fst jt == t || snd jt == t
                               jt_trn2 = transfer j1 j2 jt_emty
                               jt_emty = emptyr j1 j2 jt_tran
                               jt_tran = transfer j1 j2 jt_fill
                               jt_fill = fill j1 j2 (cl, cr)
                               fill ja1 ja2 (j1, j2) = (ja1, j2)
                               emptyl ja1 ja2 (j1, j2) = (0, j2)
                               emptyr ja1 ja2 (j1, j2) = (j1, 0)
                               transfer ja1 ja2 (j1, j2) = (j1 - diff, j2 + diff)
                                                       where canAdd = (ja2 - j2)
                                                             diff = if (j1 - canAdd) > 0 then canAdd else j1
