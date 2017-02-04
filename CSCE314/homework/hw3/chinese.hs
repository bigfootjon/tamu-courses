crt :: [(Integer, Integer)] -> (Integer, Integer)
crt ls = (collapse (expand ls max) !! 0, max)
       where max = maxval ls

collapse ls | length ls >  2 = collapse ([x | x <- xs, y <- ys, x == y] : lss)
            | length ls == 2 = [x | x <- xs, y <- ys, x == y]
            | length ls <  2 = []
            where xs  = head ls
                  ys  = head $ tail ls
                  lss = tail $ tail ls

expand [] _ = []
expand ls m = choices r d m : expand (tail ls) m
            where r = fst (head ls)
                  d = snd (head ls)

choices r d m = [x | x <- [1..m], x `mod` d == r]

maxval [] = 1
maxval ((r, d):ls) = d * maxval ls
