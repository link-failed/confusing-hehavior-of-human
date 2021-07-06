## ghci的打开方式

* 进入ghci：`stack exec ghci`
* 编译函数文件（后缀为.hs）：`:l name` （name中不需要包括后缀）





## 关于函数式编程

* 函数调用拥有最高的优先级

若要取9乘10的后继，`succ 9*10`是不行的，程序会先取9的后继，然后再乘以10得100。正确的写法应该是`succ(9*10)`    

* 前缀写法

```haskell
Prelude> (+) 1 4
5
Prelude> 1 + 5
6
```

* 在haskell中，函数的调用必使用空格，例如`bar (bar 3)`，它并不表示以bar和3两个参数去调用bar，而是以bar 3所得的结果作为参数去调用bar。在C中，就相当于`bar(bar(3))`

* 编写一些简单的函数，然后将其组合，形成一个较为复杂的函数，这样可以减少重复工作
  * 这种情形在haskell下边十分常见
  * 设想若是哪天有个数学家验证说2应该是3，我们只需要将函数doubleMe改为x+x+x即可，由于函数doubleUs调用到doubleMe，于是整个程序便进入了2即是3的古怪世界

* haskell中的函数并没有顺序，所以先声明doubleUs还是先声明doubleMe都是同样的





## 语法

### <font color='orange'>list</font>

#### `++` 操作符

* 用于把两个列表拼接起来

  ```haskell
  ghci> [1,2,3,4] ++ [9,10,11,12]  
  [1,2,3,4,9,10,11,12]  
  ghci> ['w','o'] ++ ['o','t']  
  "woot"  
  ```

####  `:` 操作符

* 用于在列表前添加元素

  ```haskell
  ghci> 'A':" SMALL CAT"  
  "A SMALL CAT"  
  ghci> 5:[1,2,3,4,5]  
  [5,1,2,3,4,5]  
  ```

#### `!! ` 操作符

* 用于从列表中取出元素

  ```haskell
  ghci> "Steve Buscemi" !! 6  
  'B'  
  ghci> [9.4,33.2,96.2,11.2,23.25] !! 1  
  33.2 
  ```

#### 列表的比较：

* 从第一个元素开始比较，相等的话再比较后面的，以此类推

  ```
  ghci> [3,2,1] > [2,1,0]  
  True  
  ghci> [3,2,1] > [2,10,100]  
  True  
  ghci> [3,4,2] > [3,4]  
  True  
  ghci> [3,4,2] > [2,4]  
  True  
  ghci> [3,4,2] == [3,4,2]  
  True  
  ```

#### head, tail, last, init

```haskell
ghci> head [5,4,3,2,1]  
5   
ghci> tail [5,4,3,2,1]  
[4,3,2,1]   
ghci> last [5,4,3,2,1]  
1   
ghci> init [5,4,3,2,1]  
[5,4,3,2]
```

* 神奇配图

  ![image-20210705150010677](D:\notes\NLP\NLP_illustration\haskell_learning\image-20210705150010677.png)

* 对空列表进行上述操作会报错

#### length, null, reverse

```haskell
ghci> length [5,4,3,2,1]  
5  

ghci> null [1,2,3]  
False  
ghci> null []  
True  

ghci> reverse [5,4,3,2,1]  
[1,2,3,4,5]  

ghci> take 3 [5,4,3,2,1]  
[5,4,3]  
ghci> take 0 [6,6,6]  
[]  
```

#### take, drop

```haskell
ghci> take 3 [5,4,3,2,1]  
[5,4,3]  
ghci> take 0 [6,6,6]  
[]  

ghci> drop 3 [8,4,2,1,5,6]  
[1,5,6]  
ghci> drop 0 [1,2,3,4]  
[1,2,3,4]  
ghci> drop 100 [1,2,3,4]  
[] 
```

#### maximum, minimum

```haskell
ghci> minimum [8,4,2,1,5,6]  
1  
ghci> maximum [1,9,2,3,4]  
9
```

#### sum, product, elem

```haskell
ghci> sum [5,2,1,6,3,2,5,7]  
31  

ghci> product [6,2,1,2]  
24

ghci> 4 `elem` [3,4,5,6]  
True  
ghci> 10 `elem` [3,4,5,6]  
False 
```

#### Texas ranges

```haskell
ghci> [1..20]  
[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]  
ghci> ['K'..'Z']  
"KLMNOPQRSTUVWXYZ"   
```

To make a list with all the numbers from 20 to 1, you can't just do **[20..1]**, you have to do **[20,19..1]**.

否则会出现如下结果

```haskell
ghci> [0.1, 0.3 .. 1]  
[0.1,0.3,0.5,0.7,0.8999999999999999,1.0999999999999999]  
```

#### cycle, repeat

前者重复整个列表，后者重复单个元素

```haskell
ghci> take 10 (cycle [1,2,3])  
[1,2,3,1,2,3,1,2,3,1]  
ghci> take 12 (cycle "LOL ")  
"LOL LOL LOL "   


ghci> take 10 (repeat 5)  
[5,5,5,5,5,5,5,5,5,5]  
```

#### list comprehension (就很神奇...)

* set comprehensions：用推导式来描述的集合

* list comprehension：

  ```haskell
  ghci> [x*2 | x <- [1..10]]  
  [2,4,6,8,10,12,14,16,18,20]  
  
  ghci> [x*2 | x <- [1..10], x*2 >= 12]  
  [12,14,16,18,20]  
  
  ghci> [ x | x <- [50..100], x `mod` 7 == 3]  
  [52,59,66,73,80,87,94]
  ```

  * prediction

    ```haskell
    boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]   
    
    ghci> boomBangs [7..13]  
    ["BOOM!","BOOM!","BANG!","BANG!"] 
    ```

  * to exclude 13,15, 19

    ```haskell
    ghci> [ x | x <- [10..20], x /= 13, x /= 15, x /= 19]  
    [10,11,12,14,16,17,18,20]  
    ```

  * include more than one variables

    ```haskell
    ghci> [ x*y | x <- [2,5,10], y <- [8,10,11]]  
    [16,20,22,40,50,55,80,100,110]
    ```

#### 其他奇奇怪怪的语法糖

* 自定义的列表长度

  ```haskell
  length' xs = sum [1 | _ <- xs]
  ```

  **_** means that we don't care what we'll draw from the list anyway so instead of writing a variable name that we'll never use, we just write **_**. This function replaces every element of a list with **1** and then sums that up. This means that the resulting sum will be the length of our list.

### <font color='orange'>tuples</font>

#### fst, snd

 the two functions operate only on pairs. They won't work on triples, 4-tuples, 5-tuples

```haskell
ghci> fst (8,11)  
8  

ghci> snd ("Wow", False)  
False 
```

#### zip

```haskell
ghci> zip [5,3,2,6,2,7,2,5,4,6,6] ["im","a","turtle"]  
[(5,"im"),(3,"a"),(2,"turtle")]  

ghci> zip [1..] ["apple", "orange", "cherry", "mango"]  
[(1,"apple"),(2,"orange"),(3,"cherry"),(4,"mango")]  
```

## <font color='orange'>Types & Typeclasses</font>(类型类？)

* haskell是静态类型系统。所有表达式的类型在编译的时候就确定了。

  “Everything in Haskell has a type”

* haskell有类型推断，声明时不必指明

* `:t` 命令可以查看表达式的类型

  ```haskell
  ghci> :t 'a'  
  'a' :: Char  
  
  ghci> :t "HELLO!"  
  "HELLO!" :: [Char]
  
  ghci> :t (True, 'a')  
  (True, 'a') :: (Bool, Char)  
  
  ghci> :t 4 == 5  
  4 == 5 :: Bool 
  ```

  * 函数也有类型

    ```haskell
    addThree :: Int -> Int -> Int -> Int  
    addThree x y z = x + y + z 
    ```



### Some basic typeClasses

* Eq

* Ord
* Show
* Read
* Enum
* Bounded
* Num
* Integral
* Floating



## <font color='orange'>Syntax in Functions</font>

### Pattern matching



## <font color='orange'>reference</font>

* http://learnyouahaskell.com/chapters

* w3cschool

【describe List】

