weightAvg wl vl = top wl vl / bot wl
                where top [] _ = 0
                      top _ [] = 0
                      top (w:wl) (v:vl) = w*v + top wl vl
                      bot []     = 0
                      bot (w:wl) = w + bot wl
