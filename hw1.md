# 1.

## Q:

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

## Q:

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

