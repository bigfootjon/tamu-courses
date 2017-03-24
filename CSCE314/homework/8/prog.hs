import Prelude hiding (lookup)



data WValue = VInt Int 
            | VBool Bool 
            | VString String
            | VMarker
              deriving Eq

instance Show WValue where
    show (VInt i) = show i
    show (VBool b) = show b
    show (VString s) = s
    show (VMarker) = "_"

asInt (VInt v) = v
asInt x = error $ "Expected a number, got " ++ show x

asBool (VBool v) = v
asBool x = error $ "Expected a boolean, got " ++ show x

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
          deriving Show

data WStmt = Empty
           | VarDecl String WExp
           | Assign String WExp
           | If WExp WStmt WStmt
           | While WExp WStmt
           | Block [WStmt]
           | Print WExp
           deriving Show

type Memory = [(String, WValue)]
marker = ("|", VMarker)
isMarker (x, _) = x == "|"

mowrite str val mem | str == fst (head mem) = (str, val) : (tail mem)
                    | otherwise             = head mem : (mowrite str val (tail mem))

lookup :: String -> Memory -> Maybe WValue
lookup str [] = Nothing
lookup str ((vname, vvalue):xs) | str == vname = Just vvalue
                                | otherwise    = lookup str xs
fromJust (Just v) = v
fromJust Nothing = error "Expected a value in Maybe, but got Nothing"

definedInScope str []  = False
definedInScope str ((vs,vv):mem) | str == vs        = True
                                 | isMarker (vs,vv) = False
                                 | otherwise        = definedInScope str mem

eval :: WExp -> Memory -> WValue
eval (Val              v) _   = v
eval (Var              s) mem = case lookup s mem of
                                  Just a -> a
                                  Nothing -> error $ "Unknown variable " ++ s ++ " in memory " ++ show mem
eval (Plus           x y) mem = VInt $ asInt (eval x mem) +     asInt (eval y mem)
eval (Minus          x y) mem = VInt $ asInt (eval x mem) -     asInt (eval y mem)
eval (Multiplies     x y) mem = VInt $ asInt (eval x mem) *     asInt (eval y mem)
eval (Divides        x y) mem = VInt $ asInt (eval x mem) `div` asInt (eval y mem)
eval (Equals         x y) mem = VBool $ case eval x mem of
                                          VBool xb -> case eval y mem of
                                                        VBool yb -> xb == yb
                                          VInt  xi -> case eval y mem of
                                                        VInt  yi -> xi == yi
eval (NotEqual       x y) mem = eval (Not (Equals x y)) mem
eval (Less           x y) mem = VBool $ asInt  (eval x mem) <  asInt  (eval y mem)
eval (Greater        x y) mem = VBool $ asInt  (eval x mem) >  asInt  (eval y mem)
eval (LessOrEqual    x y) mem = VBool $ asInt  (eval x mem) <= asInt  (eval y mem)
eval (GreaterOrEqual x y) mem = VBool $ asInt  (eval x mem) >= asInt  (eval y mem)
eval (And            x y) mem = VBool $ asBool (eval x mem) && asBool (eval y mem)
eval (Or             x y) mem = VBool $ asBool (eval x mem) || asBool (eval y mem)
eval (Not              v) mem = VBool $ not $ asBool $ eval v mem

exec :: WStmt -> Memory -> IO Memory
exec (Empty              ) mem = return mem
exec (VarDecl str exp    ) mem | definedInScope str mem = error $ "Variable " ++ str ++ " already defined in scope"
                               | otherwise = return $ (str, (eval exp mem)) : mem
exec (Assign  str exp    ) mem = return $ mowrite str (eval exp mem) mem
exec (If      cnd tst fst) mem | eval cnd mem == VBool True  = exec tst mem
                               | eval cnd mem == VBool False = exec fst mem
                               | otherwise                   = error $ "Non-boolean in condition of if"
exec (While   cnd stm    ) mem | eval cnd mem == VBool True  = exec stm mem >>= \mem' -> exec (While cnd stm) mem'
                               | eval cnd mem == VBool False = return mem
                               | otherwise                   = error $ "Non-boolean in condition of while"
exec (Block sts          ) mem = helper sts (marker:mem) >>= \mem' -> cleanup mem'
                               where helper (st:sts) mem = exec st mem >>= \mem' -> helper sts mem'
                                     helper []       mem = return mem
                                     cleanup (a:mem) | isMarker a = return mem
                                                     | otherwise  = cleanup mem
exec (Print exp         ) mem = putStr (show (eval exp mem)) >> return mem

wprogram :: Parser WStmt
