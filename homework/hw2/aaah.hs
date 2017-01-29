seeDoctor :: String -> String -> Bool
seeDoctor draw praw = dhph && length pa >= length da && and [d == p && d == 'a' | (d,p) <- zip da pa]
                    where da = reverse (drop 1 (reverse draw))
                          pa = reverse (drop 1 (reverse praw))
                          dhph = head (reverse draw) == head (reverse praw) && 'h' == head (reverse praw)
