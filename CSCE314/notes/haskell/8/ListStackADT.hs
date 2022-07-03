module ListStackADT (StkType, push, pop, top, empty, isEmpty) where

newtype StkType a = Stk [a]
push x (Stk s) = (Stk (x:s))
pop (Stk (_:s)) = (Stk s)
top (Stk (x:_)) = x
empty = Stk []
isEmpty (Stk []) = True
isEmpty _        = False
