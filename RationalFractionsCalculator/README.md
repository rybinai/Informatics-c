# Informatics-c

Калькулятор рациональных дробей

Пользователь вводит строки выражений, которые имеют вид число оператор число (через пробел), где

	число задано в формате n или n/d, где n — десятичное целое, d — положительное десятичное целое;
	вместо числа может быть введено слово last — в этом случае будет использован результат вычисления предыдущего выражения;
	оператор задан одним из символов арифметических операций +-*/.

	Пример:

5/6 - 3/4
= 1/12
last * -20
= -5/3
13/6 + last
= 1/2
last + last
= 1

Также обеспечена сборка модулей для работы с рациональными числами в виде динамической разделяемой библиотеки и использование этой библиотеки в программе calc. 

Динамическая библиотека подключается при загрузке программы. 

///

Rational Fractions Calculator

The user enters strings of expressions that are of the form number operator number (separated by a space), where

	the number is specified in the format n or n/d, where n is a decimal integer, d is a positive decimal integer;
	instead of a number, the word last can be entered - in this case, the result of the calculation of the previous expression will be used;
	the operator is specified by one of the symbols for arithmetic operations +-*/.

	Example:

5/6 - 3/4
= 1/12
last*-20
= -5/3
13/6 + last
= 1/2
last + last
= 1

Also provided is the assembly of modules for working with rational numbers in the form of a dynamic shared library and the use of this library in the calc program.

The dynamic library is connected when the program is loaded.
