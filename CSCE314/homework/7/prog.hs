type Memory = [(String, WValue)]

data WValue = VInt Int 
            | VBool Bool 
              deriving (Eq, Show)

data WExp = Val WValue

          | Var String 

          | Plus WExp WExp
          | Minus WExp WExp
          | Multiplies WExp WExp
          | Divides WExp WExp

          | Equals WExp WExp
          | NotEqual WExp WExp
          | Less WExp WExp
          | Greater WExp WExp
          | LessOrEqual WExp WExp
          | GreaterOrEqual WExp WExp

          | And WExp WExp
          | Or WExp WExp
          | Not WExp

data WStmt = Empty
           | VarDecl String WExp
           | Assign String WExp
           | If WExp WStmt WStmt
           | While WExp WStmt
           | Block [WStmt]

p1 = Block
     [
       VarDecl "x" (Val (VInt 0)),
       VarDecl "b" (Greater (Var "x") (Val (VInt 0))),
       If (Or (Var "b") (Not (GreaterOrEqual (Var "x") (Val (VInt 0)))))
         ( Block [ Assign "x" (Val (VInt 1)) ] )
         ( Block [ Assign "x" (Val (VInt 2)) ] )
     ]

intUnwrap :: WValue -> Int
intUnwrap (VInt i) = i

boolUnwrap :: WValue -> Bool
boolUnwrap (VBool b) = b

mlookup :: String -> Memory -> Maybe WValue
mlookup str [] = Nothing
mlookup str ((vname, vvalue):xs) | str == vname = Just vvalue
                                | otherwise    = lookup str xs

eval :: WExp -> Memory -> WValue
eval (Val              v) mem = v
eval (Var              s) mem = case mlookup s mem of 
                                  Just a -> a
eval (Plus           x y) mem = VInt $ intUnwrap (eval x mem) +     intUnwrap (eval y mem)
eval (Minus          x y) mem = VInt $ intUnwrap (eval x mem) -     intUnwrap (eval y mem)
eval (Multiplies     x y) mem = VInt $ intUnwrap (eval x mem) *     intUnwrap (eval y mem)
eval (Divides        x y) mem = VInt $ intUnwrap (eval x mem) `div` intUnwrap (eval y mem)
eval (Equals         x y) mem = VBool $ case eval x mem of
                                          VBool xb -> case eval y mem of
                                                        VBool yb -> xb == yb
                                          VInt  xi -> case eval y mem of
                                                        VInt  yi -> xi == yi
eval (NotEqual       x y) mem = eval (Not (Equals x y)) mem
eval (Less           x y) mem = VBool $ intUnwrap  (eval x mem) <  intUnwrap  (eval y mem)
eval (Greater        x y) mem = VBool $ intUnwrap  (eval x mem) >  intUnwrap  (eval y mem)
eval (LessOrEqual    x y) mem = VBool $ intUnwrap  (eval x mem) <= intUnwrap  (eval y mem)
eval (GreaterOrEqual x y) mem = VBool $ intUnwrap  (eval x mem) >= intUnwrap  (eval y mem)
eval (And            x y) mem = VBool $ boolUnwrap (eval x mem) && boolUnwrap (eval y mem)
eval (Or             x y) mem = VBool $ boolUnwrap (eval x mem) || boolUnwrap (eval y mem)
eval (Not              v) mem = VBool $ not $ boolUnwrap $ eval v mem

exec :: WStmt -> Memory -> Memory
exec (Empty              ) mem = mem
exec (VarDecl str exp    ) mem = 
exec (Assign  str exp    ) mem = 
exec (If      cnd tex fex) mem = 
exec (While   cnd exp    ) mem = 
exec (Block   xs         ) mem = 
