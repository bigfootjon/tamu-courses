calculateInterest :: Double -> Double -> Double

calculateInterest v i = v + (v * (i / 100.0))

compoundReturn :: Double -> Double -> [Double]

compoundReturn capital interest = helper interest capital
                                where helper i x = val : helper i val
                                                   where val = calculateInterest i x
