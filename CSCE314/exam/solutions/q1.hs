calculateInterest :: Double -> Double -> Double

calculateInterest cap int = cap + (cap * (int / 100.0))

compoundReturn :: Double -> Double -> [Double]

compoundReturn capital interest = capital : helper capital interest
                                where helper cap int = val : helper val int
                                                   where val = calculateInterest cap int
