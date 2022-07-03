module StackADT (StkType, push, pop, top, empty, isEmpty) where

data StkType a = EmptyStk | Stk a (StkType a)

push x s = (Stk x s)
pop (Stk _ s) = s
top (Stk x _) = x
empty = EmptyStk
isEmpty EmptyStk = True
isEmpty _ = False
