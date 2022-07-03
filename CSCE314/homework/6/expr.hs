data E = IntLit Int
       | BoolLit Bool
       | Plus E E
       | Minus E E
       | Multiplies E E
       | Exponentiate E E
       | Equals E E
         deriving (Eq, Show)

program = Equals
            (Plus (IntLit 1) (IntLit 2))
            (Minus
              (IntLit 5)
              (Minus (IntLit 3) (IntLit 1)))

program' = Equals
            (Plus (IntLit 1) (IntLit 2))
            (Minus
              (IntLit 5)
              (Exponentiate (IntLit 3) (IntLit 1)))

unwrapInt :: E -> Int
unwrapInt (IntLit a) = a

unwrapBool :: E -> Bool
unwrapBool (BoolLit a) = a

eval :: E -> E
eval (IntLit a)         = IntLit  a
eval (BoolLit a)        = BoolLit a
eval (Plus l r)         = IntLit  $ unwrapInt  (eval l) +  unwrapInt  (eval r)
eval (Minus l r)        = IntLit  $ unwrapInt  (eval l) -  unwrapInt  (eval r)
eval (Multiplies l r)   = IntLit  $ unwrapInt  (eval l) *  unwrapInt  (eval r)
eval (Exponentiate l r) = IntLit  $ unwrapInt  (eval l) ^  unwrapInt  (eval r)
eval (Equals l r)       = BoolLit $ (eval l) == (eval r)

-- log function adapted from http://stackoverflow.com/questions/26416323/function-to-calculate-log-of-integer
log2 x | even x = (floor . logBase 2.0 . fromIntegral) x
       | x == 1 = 0

log2Sim :: E -> E
log2Sim (IntLit a)         = IntLit    (log2 a)
log2Sim (BoolLit a)        = BoolLit   a
log2Sim (Plus l r)         = Plus      (log2Sim l) (log2Sim r)
log2Sim (Minus l r)        = Minus     (log2Sim l) (log2Sim r)
log2Sim (Multiplies l r)   = Plus      (log2Sim l) (log2Sim r)
log2Sim (Exponentiate l r) = Multiplies r          (log2Sim l)
log2Sim (Equals l r)       = Equals    (log2Sim l) (log2Sim r)
