-- 7.1
myLister :: [[x]] -> [x]
myLister ls = [x | xs <- ls, (length xs `mod` 2 == 0), x <- xs]

a = myLister ["This","is","a","longish","sentence"]
b = "Thisissentence"

-- 7.2
functionr :: (Enum t, Num t) => t -> [a] -> [[a]]
functionr x ls = [ls++ls | _ <- [1..x]]

-- returns x instances of ls concatenated with itself
c = functionr 3 [1,2,3]
d = [[1,2,3,1,2,3], [1,2,3,1,2,3], [1,2,3,1,2,3]]

isOdd 1 = True
isOdd 0 = False
isOdd n = isEven (n-1)

isEven 0 = True
isEven 1 = False
isEven n = isOdd (n-1)
