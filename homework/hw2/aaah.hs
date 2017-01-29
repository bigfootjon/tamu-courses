seeDoctor :: String -> String -> Bool
seeDoctor []     []     = True
seeDoctor _      []     = False
seeDoctor []     (p:ps) | p == 'a' = seeDoctor [] ps
                        | p == 'h' = length ps == 0
                        | otherwise = False
seeDoctor (d:ds) (p:ps) | d == 'h' = (p == 'h' || p == 'a') && seeDoctor ds ps
                        | d == 'a' = p == 'a' && seeDoctor ds ps
                        | otherwise = False

