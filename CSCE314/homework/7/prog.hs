module Main where

import Prelude hiding (lookup)
import Test.HUnit
import System.Exit

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

type Memory = [(String, WValue)]
marker = ("|", VInt 0)
isMarker (x, _) = x == "|"

mowrite str val mem | str == fst (head mem) = (str, val) : (tail mem)
                    | otherwise             = head mem : (mowrite str val (tail mem))

eval :: WExp -> Memory -> WValue
eval (Val              v) mem = v
eval (Var              s) mem = case lookup s mem of 
                                  Just a -> a
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

exec :: WStmt -> Memory -> Memory
exec (Empty              ) mem = mem
exec (VarDecl str exp    ) mem = (str, (eval exp mem)) : mem
exec (Assign  str exp    ) mem = mowrite str (eval exp mem) mem
exec (If      cnd tst fst) mem = if eval cnd mem == VBool True then exec tst mem else exec fst mem
exec (While   cnd stm    ) mem = if eval cnd mem == VBool True then exec (While cnd stm) (exec stm mem) else mem
exec (Block sts          ) mem = cleanup $ helper sts (marker:mem)
                               where helper (st:sts) mem = helper sts (exec st mem)
                                     helper []       mem = mem
                                     cleanup (a:mem) | isMarker a = mem
                                                     | otherwise  = cleanup mem

factorial = 
  Block
  [
    Empty,
    VarDecl "acc" (Val (VInt 1)),
    Empty,
    While (Greater (Var "x") (Val (VInt 1)))
    (
      Block
      [
        Empty,
        Assign "acc" (Multiplies (Var "acc") (Var "x")),
        Empty,
        Assign "x" (Minus (Var "x") (Val (VInt 1))),
        Empty
      ]
    ),
    Empty,
    Assign "result" (Var "acc"),
    Empty
  ]

p1 = Block
     [
       VarDecl "x" (Val (VInt 0)),
       VarDecl "b" (Greater (Var "x") (Val (VInt 0))),
       If (Or (Var "b") (Not (GreaterOrEqual (Var "x") (Val (VInt 0)))))
         ( Block [ Assign "x" (Val (VInt 1)) ] )
         ( Block [ Assign "x" (Val (VInt 2)) ] )
     ]

lookup :: String -> Memory -> Maybe WValue
lookup str [] = Nothing
lookup str ((vname, vvalue):xs) | str == vname = Just vvalue
                                | otherwise    = lookup str xs
asInt (VInt v) = v
asInt x = error $ "Expected a number, got " ++ show x

asBool (VBool v) = v
asBool x = error $ "Expected a boolean, got " ++ show x

fromJust (Just v) = v
fromJust Nothing = error "Expected a value in Maybe, but got Nothing"

myTestList =

  TestList [
    test $ assertEqual "p1 test" [] (exec p1 []),

    let res = lookup "result" (exec factorial [("result", undefined), ("x", VInt 10)])
    in test $ assertBool "factorial of 10" (3628800 == asInt (fromJust res))
    ]    

main = do c <- runTestTT myTestList
          putStrLn $ show c
          let errs = errors c
              fails = failures c
          if (errs + fails /= 0) then exitFailure else return ()
