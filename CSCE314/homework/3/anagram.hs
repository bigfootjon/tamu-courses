factors x = [a | a <- [1..x], b <- [1..x], a * b == x]

shiftBy col row cs = [cs !! (i+j) | i <- [0..(col-1)], j <- map (col*) [0..(row-1)]]

anagramEncode :: [Char] -> [Char]
anagramEncode cs_raw = shiftBy col row cs
                     where cs = paddingAdd cs_raw
                           col = factors (length cs) !! 2
                           row = factors (length cs) !! 1

anagramDecode :: [Char] -> [Char]
anagramDecode cs = paddingRm $ shiftBy row col cs
                 where col = factors (length cs) !! 2
                       row = factors (length cs) !! 1

paddingAdd :: [Char] -> [Char]
paddingAdd cs | length (factors (length cs)) == 4 = cs
              | otherwise = paddingAdd $ cs ++ "X"

paddingRm :: [Char] -> [Char]
paddingRm cs | end == "X" = paddingRm $ reverse $ drop 1 $ reverse cs
             | otherwise = cs
             where end = take 1 $ reverse cs
