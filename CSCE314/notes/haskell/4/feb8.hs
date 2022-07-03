op _ y = 1 + y

foldrLen ls = foldr op 0 ls

lenB ls = lenHelper 0 ls
        where lenHelper c [] = c
              lenHelper c (_:xs) = lenHelper (c+1) xs
