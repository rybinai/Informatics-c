# Informatics-c

Англо-русский словарь

Программа поиска словарных статей в соответствии с заданным словом. Файл словаря приложен к заданию.

Запуск

./dict1 mueller.dict или ./dict2 mueller.dict 

Разница между dict1.c и dict2.c

dict1.c - Программа, предоставляющая единоразовый поиск по шаблону.

dict2.c - Программа, работающая с динамической памятью и предоставляющая многократнный ввод шаблонов.

Шаблон может начинаться со специального символа ^, обозначающего начало строки и оканчиваться специальным символом $, обозначающим конец строки

•  для введенного пользователем шаблона ^or, среди найденных словарных статей, может встретиться перевод слова orbital, но не могут встретиться переводы слов doctor, word;

•  для введенного пользователем шаблона or$, среди найденных словарных статей, может встретиться перевод слова doctor, но не могут встретиться переводы слов orbital, word;

•  для введенного пользователем шаблона ^or$ программа найдет единственную словарную статью для слова or.

///

English-Russian dictionary

The program for searching dictionary entries in accordance with the given word. The dictionary file is attached to the task.

launch

./dict1 mueller.dict or ./dict2 mueller.dict

Difference between dict1.c and dict2.c

dict1.c - A program that provides a one-time pattern search.

dict2.c - A program that works with dynamic memory and provides multiple input patterns.

A pattern can start with the special character ^, which marks the beginning of a line, and end with the special character $, which marks the end of a line.

• for the pattern ^or entered by the user, among the found dictionary entries, there may be a translation of the word orbital, but translations of the words doctor, word cannot be found;

• for the or$ template entered by the user, among the found dictionary entries, there may be a translation of the word doctor, but there cannot be translations of the words orbital, word;

• for the pattern ^or$ entered by the user, the program will find the only dictionary entry for the word or.
