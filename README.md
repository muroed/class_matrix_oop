# nd_matrix+

Реализация библиотеки nd_matrix_oop.h


## Contents

1. [Chapter I](#chapter-i) \
    1.1. [Introduction](#introduction)
2. [Chapter II](#chapter-ii) \
    2.1. [Information](#information)
3. [Chapter III](#chapter-iii) \
    3.1. [Part 1](#part-1-реализация-функции-библиотеки-nd_matrix_ooph) \
    3.2. [Part 2](#part-2-описание-проекта)


## Chapter I

## Introduction

В данном проекте вам предстоит еще раз реализовать уже знакомую вам по проекту **nd_matrix** библиотеку для работы с матрицами, но на этот раз, используя объектно-ориентированный подход (см. материалы). Объектно-ориентированный подход позволяет реализовать библиотеку для работы с матрицами в виде отдельного класса, над объектами которого определены операции, представленные как методами, так и стандартными операторами +, -, * и т.д.


## Chapter II

## Information

### Операции над матрицами

Ниже представлено краткое описание операций над матрицами, которые необходимо реализовать в разрабатываемой библиотеке. Они похожи на операции выполненные вами ранее в блоке "Структурного Программирования" и более подробное описание каждой из них можно посмотреть там. Обратите внимание, что некоторые операции имеют исключительные ситуации, требующие специальной обработки с использованием механизма исключений. 

| Операция    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const ndMatrix& other)` | Проверяет матрицы на равенство между собой |  |
| `void SumMatrix(const ndMatrix& other)` | Прибавляет вторую матрицы к текущей | различная размерность матриц |
| `void SubMatrix(const ndMatrix& other)` | Вычитает из текущей матрицы другую | различная размерность матриц |
| `void MulNumber(const double num)` | Умножает текущую матрицу на число |  |
| `void MulMatrix(const ndMatrix& other)` | Умножает текущую матрицу на вторую | число столбцов первой матрицы не равно числу строк второй матрицы |
| `ndMatrix Transpose()` | Создает новую транспонированную матрицу из текущей и возвращает ее |  |
| `ndMatrix CalcComplements()` | Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее | матрица не является квадратной |
| `double Determinant()` | Вычисляет и возвращает определитель текущей матрицы | матрица не является квадратной |
| `ndMatrix InverseMatrix()` | Вычисляет и возвращает обратную матрицу | определитель матрицы равен 0 |

Помимо реализации данных операций, необходимо также реализовать конструкторы и деструкторы:

| Метод    | Описание   |
| ----------- | ----------- |
| `ndMatrix()` | Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью |  
| `ndMatrix(int rows, int cols)` | Параметризированный конструктор с количеством строк и столбцов | 
| `ndMatrix(const ndMatrix& other)` | Конструктор копирования |
| `ndMatrix(ndMatrix&& other)` | Конструктор переноса |
| `~ndMatrix()` | Деструктор |

А также нужно перегрузить следующие операторы, частично соответствующие операциям выше:

| Оператор    | Описание   | Исключительные ситуации |
| ----------- | ----------- | ----------- |
| `+`      | Сложение двух матриц  | различная размерность матриц |
| `-`   | Вычитание одной матрицы из другой | различная размерность матриц |
| `*`  | Умножение матриц и умножение матрицы на число | число столбцов первой матрицы не равно числу строк второй матрицы |
| `==`  | Проверка на равенство матриц (`EqMatrix`) | |
| `=`  | Присвоение матрице значений другой матрицы | |
| `+=`  | Присвоение сложения (`SumMatrix`)   | различная размерность матриц |
| `-=`  | Присвоение разности (`SubMatrix`) | различная размерность матриц |
| `*=`  | Присвоение умножения (`MulMatrix`/`MulNumber`) | число столбцов первой матрицы не равно числу строк второй матрицы |
| `(int i, int j)`  | Индексация по элементам матрицы (строка, колонка) | индекс за пределами матрицы |


## Chapter III

## Part 1. Реализация функции библиотеки nd_matrix_oop.h

- Программа должна быть разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Код программы должен находиться в папке src
- При написании кода необходимо придерживаться Google Style
- Реализовать матрицу в виде класса `ndMatrix`
- Хранить только приватные поля `matrix_`, `rows_` и `cols_`
- Реализовать доступ к приватным полям `rows_` и `cols_` через accessor и mutator. При увеличении размера - матрица дополняется нулевыми элементами, при уменьшении - лишнее просто отбрасывается
- Оформить решение как статическую библиотеку (с заголовочным файлом nd_matrix_oop.h)
- Реализовать операции, описанные [выше](#операции-над-матрицами)
- Перегрузить операторы в соответствии с таблицой в разделе [выше](#операции-над-матрицами).
- Подготовить полное покрытие unit-тестами функций библиотеки c помощью библиотеки GTest
- Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean, test, nd_matrix_oop.a)


## Part 2. Описание проекта

## Цели Makefile
---
> make all

> make nd_matrix_oop.a

Cобирают библиотеку `nd_matrix_oop.a`

---
>make test

Загружает и локально собирает Google Test, собирает весь проект с тестами

---
> make gcov_report

Аналогично [make_test](#цели_makefile) собирает проект, и собирает отчет о покрытии функций библиотеки тестами

---
> make valgrind_docker

Обертывает тесты в `Docker` и прогоняет тесты через `valgrind`

---
>make style

Проверяет код на соответствие GoogleStyle

---
>make clean

Очищает репозиторий до начального состояния

