--- Wed Feb 15 08:57:44 CST 2017

-- From last time:

data Expr	= Val Int
	  	| Add Expr Expr	
	  	| Mul Expr Expr	

-- 1 + 2 * 3
e1 = Add (Val 1) (Mul (Val 2) (Val 3))
e1' = Mul (Add (Val 1) (Val 2)) (Val 3)
e2 = Mul (Val 9) (Add (Val 8) (Val 6))

instance Show Expr where
	show (Val v) = show v
	show (Add s1 s2) = "(" ++ (show s1) ++ "+" ++ (show s2) ++ ")"
	show (Mul s1 s2) = (show s1) ++ "*" ++ (show s2)

evalExpr :: Expr -> Int
evalExpr (Val v)  = v
evalExpr (Add s1 s2)  =  evalExpr s1 + evalExpr s2
evalExpr (Mul s1 s2)  =  evalExpr s1 * evalExpr s2

countLeaves :: Expr -> Int
countLeaves (Val v)  = 1
countLeaves (Add s1 s2)  =  countLeaves s1 + countLeaves s2
countLeaves (Mul s1 s2)  =  countLeaves s1 + countLeaves s2

depthExpr :: Expr -> Int
depthExpr (Val v)  = 1
depthExpr (Add s1 s2) = 1 + max (depthExpr s1) (depthExpr s2)
depthExpr (Mul s1 s2) = 1 + max (depthExpr s1) (depthExpr s2)

foldExpr :: (Int -> b) -> (b -> b -> b) -> (b -> b -> b) -> Expr -> b 
-- foldExpr :: valF          addF              mulF          input    output
foldExpr valF _ _ (Val v) = valF v
foldExpr valF addF mulF (Add s1 s2) = addF (foldExpr valF addF mulF s1) (foldExpr valF addF mulF s2)
foldExpr valF addF mulF (Mul s1 s2) = mulF (foldExpr valF addF mulF s1) (foldExpr valF addF mulF s2)

evalExpr' :: Expr -> Int
evalExpr' = foldExpr (\x -> x) (\x -> (\y -> x+y))  (\x -> (\y -> x*y))  

countLeaves' = foldExpr (\_ -> 1) (+) (+)

evalExpr'' = foldExpr id (+) (*)

