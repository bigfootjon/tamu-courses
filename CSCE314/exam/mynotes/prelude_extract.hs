fst :: (a, b) -> a
snd :: (a, b) -> b
-- not defined for n length tuples

class Eq a where
      (==) :: a -> a -> Bool
      (/=) :: a -> a -> Bool
      x == y = not (x /= y)
      x /= y = nt (x == y)
      -- MUST define one of: (==), (/=)

id :: a -> a
id a = a

doubleNegate   x = not (not x)
doubleNegate'  x = (not . not) x -- (.) is composition
doubleNegate'' x = not $ not x -- ($) is right side first

[1] ++ [2,3] == [1,2,3]
filter (=='c') ['a', 'b', 'c'] == ['c']

head [1,2,3] == 1
last [1,2,3] == 3
tail [1,2,3] == [2,3]
init [1,2,3] == [1,2]
length [1,2,3] == 3
reverse [1,2,3] == [3,2,1]
[1,2,3] !! 1 == 2
and [True, True, True] == True
and [True, False, True] == False
or [True, False, False] == True
or [False, False, False] == False

take 2 [1,2,3] == [1,2]
drop 2 [1,2,3] == [3]
splitAt 2 [1,2,3] == [[1,2], [3]]
takeWhile (<3) [1,2,2,2,2,4] == [1,2,2,2,2]
dropWhile (<3) [1,2,2,2,2,4] == [4]

lines "one\ntwo\n" == ["one", "two"]
words "one two three" == ["one", "two", "three"]
unlines ["one", "two"] == "one\ntwo\n"
unwords ["one", "two", "three"] == "one two three"

class Show a where
      show :: a -> String

class Read a where
      read :: String -> a
