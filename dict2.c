/**
 * dict2.c -- программа чтения словаря и печати словарной статьи по номеру
 *
 * Copyright (c) 2022, Student Name RybinAI
 *
 * This code is licensed under MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAXLINE 1023
#define MAXSIZE 10485760

/* Функция для вывода статей, соотвествующих заданному шаблону */
char *filter_dictionary(const char *s, const char *dictionary, char *entries);

/* Функция, загружающая словарь в память программы */
char *load_dictionary(char *dictionary, FILE *dict);

int main(int argc, char *argv[])
{   
    /* Проверка */
    if (argc != 2) {
        fprintf(stderr,"Неправильное число аргументов. \n Использование: dict1 файл_словаря \n ");
        return EXIT_FAILURE;
    }   

    /* Файл словаря */
    FILE* dict = NULL;

     /* Открываем файл словаря */
    dict = fopen(argv[1], "r");

    /* Проверка файла */
    if (dict == NULL){
        errno;
        perror("Error");
    }

    /* Загружаем словарь в выделенную область памяти */
    char *dictionary;   
    dictionary = malloc(MAXSIZE);
    dictionary = load_dictionary(dictionary, dict);

    /* Проверка на загрузку */
    if (dictionary == NULL) {
        fprintf(stderr, "Не удалось загрузить файл \n");
        return EXIT_FAILURE;
    }

    fclose(dict);

    /* Выделяем память*/
    char *entries;
    entries = malloc(MAXSIZE);

    /* Шаблон */
    char s[MAXLINE];
    printf("Поиск по шаблону:");    

    /* Вывод нужных статей */

    while (scanf("%s", s) > 0) {
        entries=calloc(MAXSIZE,1);
        if (filter_dictionary(s,dictionary,entries) != NULL)
            printf ("%s\n", entries);
        else
            printf("Статьи не найдены \n");
            free (entries);
    }
    
     /* Освобождаем память */
    free(dictionary);

    return 0;
} 

/* Функция, выводящая статьи, соответствующие заданному шаблону */
char *filter_dictionary(const char *s, const char *dictionary, char *entries) {

    /* Флаг соответствия текущей статьи условию отбора */
    int matched_entry;

     /* Текущая строка */
    char current_line[MAXLINE + 1] = ""; 

    /* Обнуление переменных и освобождение буфера найденных статей */
    memset(entries, 0, MAXSIZE);

    int q = 0;
    int end_dict = 0;
    int end_buffer = 0;  

      /* Просматриваем словарь, печатая строки запрошенной статьи */
    while (dictionary[end_dict] != '\0') {

        /* Запоминаем текущую строку */
        int l = 0;
        for (q = end_dict; dictionary[q] != '\n'; q++) {
            current_line[l] = dictionary[q];
            l++;
            if (l == MAXLINE - 1) {
                break;
            }
        }
        current_line[l] = '\n';
        current_line[l + 1] = '\0';

        /* Запоминаем место, на котором мы остановились при просмотре словаря */
        end_dict = q + 1;
    
            if (!isspace(current_line[0])) {
                matched_entry = 0;
                /* Определяем, выполнено ли условие отбора для данной статьи */
                 if ((s[0] == '^') && (s[strlen(s) - 1] == '$')) {
                    if (!strncmp(current_line, s + 1, strlen(current_line) - 1))
                        matched_entry = 1;
                    else
                        matched_entry = 0;
                }
                else
                if  ((s[0] !='^') && (s[strlen(s) - 1] != '$')) {
                    if (strstr(current_line, s))
                        matched_entry = 1;
                    else
                        matched_entry = 0; 
                }
                else
                if (s[0] == '^') {

                    if (s[strlen(s)] != '$') { 
                        if (!strncmp(current_line, s + 1, strlen(s + 1)))
                            matched_entry = 1;
                        else
                            matched_entry = 0; 
                    }
                }
                else 
                if (s[strlen(s) - 1] == '$') {
                    if (!strncmp((current_line + strlen(current_line + strlen(s) - 1) - 1), s, strlen(s) - 1)) 
                        matched_entry = 1;
                    else
                        matched_entry = 0;
                }
            }        
         /* Печатаем строку, если она относится к запрошеннойй статье */
        if (matched_entry) {
            sprintf(entries + end_buffer, "%s\n", current_line);
            end_buffer = end_buffer + strlen(current_line);
         }
    }    

    /* Возвращаем адрес буфера выбранных статей */
    if (*entries == 0)
        return (NULL);
    else
        return (entries);
}

/* Функция загружающая словарь в память программы */
char* load_dictionary(char *dictionary, FILE *dict) 
{  
    /* Находим размер файла */
    if (fseek(dict, 0L, SEEK_END) < 0)
        return NULL;
    long filesize = ftell(dict);
    if (fseek(dict, 0L, SEEK_SET) < 0)
        return NULL;

    /* Если размер файла превышает 10 МБ, возвращаем ошибочное значение */
    if ((filesize < 0) && (filesize > MAXSIZE))
        return (NULL);

    /* Загружаем словарь в динамическую память */
    if (fread(dictionary, sizeof(char), filesize, dict) != (size_t) filesize)
        return (NULL);
    
    return (dictionary);
}
