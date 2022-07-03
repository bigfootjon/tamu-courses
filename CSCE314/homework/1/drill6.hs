multComplex :: Num a => (a, a) -> (a, a) -> (a, a)
multComplex (xr, xi) (yr, yi) = (xr * yr - xi * yi, xr * yi + xi * yr)
