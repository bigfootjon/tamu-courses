{-seeDoctor :: String -> String -> Bool
seeDoctor []     []     = True
seeDoctor _      []     = False
seeDoctor []     (p:ps) | p == 'a' = seeDoctor [] ps
                        | p == 'h' = length ps == 0
                        | otherwise = False
seeDoctor (d:ds) (p:ps) | d == 'h' = (p == 'h' || p == 'a') && seeDoctor ds ps
                        | d == 'a' = p == 'a' && seeDoctor ds ps
                        | otherwise = False
-}

seeDoctor :: String -> String -> Bool
seeDoctor dso pso = actualSeeDoctor ds ps
                where actualSeeDoctor [] [] = True
                      actualSeeDoctor _ [] = False
                      actualSeeDoctor [] _ = False
                      actualSeeDoctor (d:ds) (p:ps) = if p == d && p == 'h' then helper ds ps else False
                      ds = reverse dso
                      ps = reverse pso
                      helper [] _ = False
                      helper _ [] = True
                      helper (d:ds) (p:ps) = if p == d && p == 'a' then helper ds ps else False
