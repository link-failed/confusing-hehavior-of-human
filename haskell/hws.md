# 1.

### Q:

This task is meant to be solved with list comprehension.

Write a function headOrLast :: [String] -> Char -> [String] that, given a list of strings and a character, evaluates to a list with all the strings of the input list that either begin or end with the input character.

### A:

```haskell
headOrLast xs y = [ x | x <- xs, (head x == y || last x == y)]
```

### result:

```haskell
Prelude> headOrLast ["hello", "orz", "lol"] 'o'
["hello","orz"]
```



# 2.

### Q:

This task is meant to be solved with guards.

We represent playing cards with (Char, Int) pairs. ‘s’ means spades, ‘h’ hearts, ‘c’ clubs’ and ‘d’ diamonds, with number values going from 2 to 14 (Ace being 14). Consider a game, where a player is dealt two cards and wins credits based on the following rules:

If the player has the Ace of Spades (‘s’, 14), then the player wins 6 credits.
Otherwise if the player has a pair (same number values), then the player wins 4 credits.
Otherwise if the player has two cards of the same suit, then the player wins 2 credits.
Otherwise, the player wins 0 credits.

Write a function credits :: (Char, Int) -> (Char, Int) -> Int that evaluates the given credits.

You can assume that the given cards are real.

### A:

```haskell
(a, b) `credits` (c, d) 
| ((a == 's' && b == 14) || (c == 's' && d == 14)) = 6
| (b == d) =4
| (a == c) = 2
| otherwise = 0
```

### result:

```haskell
Prelude> (a, b) `credits` (c, d) | ((a == 's' && b == 14) || (c == 's' && d == 14)) = 6 | (b == d) = 4 | (a == c) = 2 | otherwise = 0
Prelude> ('c', 3) `credits` ('s', 14)
6
Prelude> ('d', 5) `credits` ('h', 5)
4
Prelude> ('d', 6) `credits` ('d', 10)
2
Prelude> ('c', 3) `credits` ('h', 14)
0
```



# 3.

### Q:

This task is meant to be solved with recursion.

Write a function nextIsGreater :: [Int] -> [Int] that, given a list of numbers, produces a list with all elements of the input list such that the element is followed by a greater number in the input list (the next number is greater).

The numbers need to be in the same order relative to each other in the output list as they are in the input list.

An example evaluation of the function:

function call:
nextIsGreater [0,5,2,3,2,2,3,1]
result:
[0,2,2]

### A:

```haskell
nextIsGreater [] = []
nextIsGreater (x:xs) 
	| xs == [] = [] 
	| x >= head xs = nextIsGreater (xs) 
	| otherwise = x:(nextIsGreater (xs))
```

### result:

```haskell
Prelude> nextIsGreater [0,5,2,3,2,2,3,1]
[0,2,2]
Prelude> nextIsGreater [0,0,0,0]
[]
Prelude> nextIsGreater [1,2,3,4]
[1,2,3]
```



Day 2 exercises are a bit more difficult, but you do not need to solve them all to pass the course. You get some points even for returning on Thursday but full points only by returning tomorrow (Wednesday).





# 4.

### Q:

This task is suitable for a recursive solution.

We say that character pair `(c1,c2)` appears in string `s` with gap `g`, if `c1` is **before** `c2` and there are **exactly g characters** between c1 and c2 in `s`.

Write a function `gap :: (Char, Char) -> Int -> String -> Int` that, given a pair `(c1,c2)`, a gap g and a string s returns an Int telling how many times `(c1,c2)` appear in s with gap g.

For example:

function call:
gap ('a','b') 1 "aaabbb"
result:
2

### A:

* import一个函数用于返回下标

* 写一个函数用于判断是否有符合下标差的pair

* 写一个函数用于遍历第一个字符

```haskell
import Data.List

judge index n b xs 
	| index < (length xs - 2) = b == xs!!(index + n + 1) 
	| otherwise = False
gap (a, b) n xs = length [index | index <- (elemIndices a xs), judge index n b xs]
```

The function judge is for juding for the element a (xs[index]), whether the element xs[index + n + 1] is b.

Dividing the solution into two funtions helps to fix the problem that some paraments' type couldn't match.

### result:

```haskell
Prelude Data.List> gap ('a','b') 1 "aaabbb"
2
```



# 5.

### Q:

Notice that e.g. length of a list is an Int and you can get a fractional (non-Integer) value out of that with the fromIntegral function.

Write a function distance1 :: String -> String -> Float that, given two strings s1 and s2, calculates their distance using the following formula ( (count of how many of the characters in s1 do not appear in s2 + (count of how many of the characters in s2 do not appear in s1) ) / ( (length of s1) + (length of s2) ). If both of the lists are empty, then the distance is 0.

For example, the distance between “aaabc” and “aabdd” with this function is (1 + 2) / (5 + 5).

Please note that this function is not standard well-behaving distance functions.

Hint: List comprehension is useful here.

### A:

```haskell
absence s1 s2 = sum [1 | x <- s1, not (x `elem` s2)]
distance1 s1 s2 
	| s1 == "", s2 == "" = 0
	| otherwise = (absence s1 s2 + absence s2 s1 ) / fromIntegral(length s1 + length s2)
	
distance1 s1 s2 | s1 == "", s2 == "" = 0 | otherwise = (absence s1 s2 + absence s2 s1 ) / fromIntegral(length s1 + length s2)
```

### result:

```haskell
Prelude> absence s1 s2 = sum [1 | x <- s1, not (x `elem` s2)]
Prelude> distance1 s1 s2 = (absence s1 s2 + absence s2 s1 ) / fromIntegral(length s1 + length s2)
Prelude> distance1 "aaabc" "aabdd"
0.3
```



# 6.

## Q:

Write a function clusters that is given:

- f,   a distance function of type String -> String -> Float (like the one in the previous Task 5)
- d :: Float
- ss :: [String]
  For each string s  in ss, the function clusters computes a "cluster", ie a list of similar strings in ss (strings that are **at most distance d from the s**). The list of strings similar to s should also contain s (if the distance function allows). 

The clusters and the list of clusters may be in any order. 

Calling this function with function of Task 5, d=0.3 and ss=["aaabc", "aabdd", "a", "aa", "abdd", "bcbcb", "", "abcdefghij"]
should return
[[""],["a","aa"],["a","aa","aaabc"],["aa","aaabc","aabdd","bcbcb"],["aaabc","aabdd","abdd"],["aaabc","bcbcb"],["aabdd","abdd"],["abcdefghij"]]

(in some order).

## A:

```haskell
clusters f d (x:y:ss)
	| f d [] = []
	| f d x:[] = []
	| f d (x:y:[]) = if (f x y <= d) then [x,y] else Nothing
	| otherwise = if (f x y <= d) then [x,y]:ss else clusters f d (x:ss)
	
--when apply these functions, ans should be an empty list, which is used to store the result
--function clusters' is used to deal with the first element of given list
clusters' f d (x:y:ss) ans
	| f d [] ans = ans
	| f d (x:[]) ans = ans 
	| f d (x:y:[]) ans = if (f x y <= d) then [x,y]:ans else ans
    | f d (x:ss) ans = f d ss
	| otherwise = 
		if (f x y <= d) 
		then clusters' f d (x:ss) [x,y]:ans 
		else clusters' f d (x:ss) ans
		
--function clusters. it applys clusters' to each element and also save results in ans
clusters f d (x:ss) ans
	| f d [] ans = ans
	| f d (x:[]) ans = ans 
	| otherwise = clusters f d ss ((clusters' f d (x:ss) ans):ans)
```



## result:
