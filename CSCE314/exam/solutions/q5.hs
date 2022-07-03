myRLE ls = helper (zip (repeat 1) ls)
         where helper [x] = [x]
               helper ((xc,xv):(yc,yv):ls) | xv == yv = helper ((xc + yc, xv) : ls)
                                           | otherwise= (xc,xv) : helper ((yc,yv) : ls)
