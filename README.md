# fancy_matrix_calculator
___
### 1. Team and roles
* ##### Afonina Varvara (v4rvarya) - logger and interface
* ##### Gromova Daria (Prussia) - language processing
* ##### Petrova Sophie (qrivthv) - matrix logic

___
### 2. Our mission
1. we want to provide free working matrix calculator for our fellow time travellers </p> 
2. we want to make past forms of languages used and more popular </p>
___
### 3. How to use
1. start main.cpp
2. the program will start in the console. by default the set language is pre-revolutionary russian (but you can switch it to modern russian whenever you want with command ```changeLang```)
3. you will be asked to enter two initial matrices (A and B), and then you may do whatever you want using these commands (all are in pre-revolutionary russian, except 3 service commands)
* `changeLang` - changes language (pre-revolutionary to modern and from modern to pre-revolutionary)
* `print <A or B>` - prints the requested matrix (A or B)
* `exit` - terminates the program
* `опредѣлитель` or `определитель` - calculates the determinant if it's possible and outputs it
* `инверсія` or `инверс` - calculates the inverse of the matrix if possible and outputs it
* `перевернуть матрицу` or `транспонировать` - calculates the transposed version of the matrix and outputs it
* `табель о рангахъ` (`узнать рангъ` \ `рангъ`) or `найти ранг` (`ранг`) - calculates matrix rank if possible and outputs it (also outputs possible rank (title) from the Table of Ranks)
* `преумножить въ <n> разъ` (`умножить на <n>`) or `умножить на число <n>` (`умножить на <n>`) - multiplies the matrix by the provided scalar `n`
* `переумножить матрицы` or `перемножить матрицы` (`умножить матрицы`) - multiplies the given matrices (A*B) and outputs the result
* `складывать матрицы` (`сложить`) or `сложить матрицы` (`сложить`) - calculates sum of the given matrices and outputs it
* `вычесть матрицы` (`вычесть`) or `вычесть матрицы` (`вычесть`) (yep, some words are the same in modern and pre-revolutionary orthographies) - calculates the difference of the given matrices and outputs it
* `идентичность <n>` or `айдентити <n>` - outputs the identity matrix of the given size (n by n)
* `перемѣнить мѣстами` (`перемѣнить` / `vice versa`) or `поменять матрицы местами` (`поменять`) - swaps A and B and outputs the two new matrices (A and B)
* `слѣдъ` or `след` (`трейс`) - calculates the trace of the matrix A and outputs it
* `отмѣна` or `отмена` (`отменить`) - cancels (reverts) the previous operation

###### Remark: every operation that is applied to 1 matrix is applied to matrix A