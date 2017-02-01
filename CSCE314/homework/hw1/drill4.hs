countdownList :: Int -> Int -> [Int]
countdownList x y | (x < y) = reverse [x..y]
                  | otherwise = [2]
