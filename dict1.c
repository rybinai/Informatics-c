/**
 * dict1.c -- программа чтения словаря и печати словарной статьи по номеру
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

void show_entries(const char *s, FILE *dict);

int main(int argc, char *argv[])
{
    /* Файл словаря */
    FILE* dict = NULL;
    
    if (argc != 2) {
    	fprintf(stderr,"Неправильное число аргументов. \n Использование: dict1 файл_словаря \n ");
    	return EXIT_FAILURE;
    }   
     
    char s[MAXLINE];
    
    printf("Поиск по шаблону:");	
    scanf("%s", s);
    
    /* Открываем файл словаря */
    dict = fopen(argv[1], "r");

    /* Проверка файла */
    if (dict == NULL){
    	errno;
    	perror("Error");
    }

    show_entries(s, dict);

    fclose(dict);

    return EXIT_SUCCESS;
}
void show_entries(const char *s, FILE *dict) {

    /* Флаг соответствия текущей статьи условию отбора */
    int matched_entry = 0;

     /* Текущая строка */
    char current_line[MAXLINE + 1] = "";    
    
    /* Просматриваем словарь, печатая строки запрошенной статьи */
    while (fgets(current_line, MAXLINE, dict) != NULL) {
         /* Если первый символ строки не является пробельным разделителем,
            найдено начало новой словарной статьи */
            if (!isspace(current_line[0])) {
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
         /* Печатаем строку, если она относится к запрошенной статье */
        if (matched_entry) {
             printf("%s", current_line);
         }
    }
}
