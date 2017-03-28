import Prelude hiding (Maybe, Nothing, Just)

data Maybe a = Nothing | Just a
             deriving Show

safeSqrt :: Float -> Maybe Float
safeSqrt n | n < 0     = Nothing
           | otherwise = Just (sqrt n)

safeDiv :: Float -> Float -> Maybe Float
safeDiv m n | n == 0    = Nothing
            | otherwise = Just (m / n)

-- safeApply from notes is >>=
