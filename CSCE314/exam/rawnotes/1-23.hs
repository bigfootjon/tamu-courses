-- Mon Jan 23 09:09:55 CST 2017
--
doubler x = x + x

mdoubler :: Integer -> Integer
mdoubler x = x + x


sum'r :: Integer -> Integer -> Integer
sum'r x y = x + y

f' x = sum'r 4 x
f = sum'r 4

dozen = 12
gross = 144

-- increment dozen
-- dozen = dozen + 1 -- Haskell won't allow this!

myList = [2,4,8,2,9,-10, 0]
myList' = ['c', 'd', 'e', 'f']
m1 :: [String]
m1 = ["hello", "world","these","are","strings"]
m2 = [5, 6, 8, 10, -12]

twiceListLength ls = doubler (length ls)

row1 = [6.3, 5.6, 4.5]
row2 = [0.0, 1.0, -9.15]
matrix1 = [row1, row2]

{-
 - head and tail, gets first element, gets the rest of the list, resp.
 -}

{- !! selects element -}
{- ++ concatenates two lists -}

myH :: [Char] -> Char
myH ls = ls !! 0 -- own version of head

{- take i ls, will take the first i elements of list ls
 - drop i ls, removes the first i elements of the list ls
 -}

{-
 - Is "head ls" the same as "take 1 ls" ?
 - 	not quite, the former gives an element, the latter a (short) list
 -}

pr x ls = x:ls
-- pp x ls = ls:x -- This doesn't define "post-pending"
pp x ls =    reverse(x:(reverse ls))

-- sum and product, which do what you'd expect!



