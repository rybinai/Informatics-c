/**
 * spacexplore.c -- прототип игры управления звездолетом
 * 
 * Copyright (c) 2022 Alexey Rybin @arybin.cs.petrsu.ru
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>
#include <SDL_ttf.h>

#define VXD 8 /* Скорость коробля по x */
#define VYD 8 /* Скорость коробля по y*/
#define TIMER 10 /* Игровое время */
int r=1; /* Закрытие игры */
time_t timer_start; /* Время начала игры */

/* Описание экрана игры */
typedef struct _gamescreen {
    /* Поверхность отрисовки */
    SDL_Surface *sprite;    
} gamescreen;

/* Описание заднего фона */
typedef struct _background {
    /* Задний фон */
    SDL_Surface *sprite;
} background;

/* Шрифты для текстов */
typedef struct _text {
    /* Шрифты для текста */
    TTF_Font *timer;
    TTF_Font *end;
} text;

/* Описание объекты */
typedef struct _object {
    /* Поверхность отрисовки */
    SDL_Surface *sprite;
    /* Координаты объекта */
    int x;
    int y;
} object;

/* Описание управляемого пользователем корабля */
typedef struct _spaceship {
    /* Поверхность отрисовки */
    SDL_Surface *sprite;
    /* Координаты корабля */
    int x;
    int y;
    /* Проекции скорости корабля */
    int vx;
    int vy;
} spaceship;

/* Ресурсы и состояние игры  */
typedef struct _game {
    /* Экран игры */
    gamescreen *screen;

    /* Корабль пользователя */
    spaceship *ship;

    /* background - фон игры, background2 - черный экран */
    background *background;
    background *background2;
    
    /*Шрифты */
    text *text;

} game;

/* Инициализирует игру */
game *init();

/* Функция вывода всего текста на экран */
void print_text(char *text, int x, int y, TTF_Font *font, game *g);

/* Все функции игры */
int run(game *g);

/* Функция отрисовывающая экран и приколы на ней */
void draw(game *g, int* done);

/* Функция завершения игра */
int endgame();

/* Основная программа */
int main()
{
    //Пока флаг поднят игра запущена
    while(r==1)
    {
    /* Инициализируем игру */
    game *g = init();
    
    /* Если функция игры вернёт 1, то пользователь хочет выйти из неё */
    if(run(g))
        r = 0;
    }
    return 0;
}

/* Игра */
game *init()
{
    /* Создаем структуру представления состояния игры */
    game *g;
    g = (game *) malloc(sizeof(game));
    if (g == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }

    /* Инициализируем библиотеку SDL */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Инициализируем библиотеку SDL_TTF */
    if (TTF_Init() < 0) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Регистрируем обработчик завершения программы */
    atexit(TTF_Quit);
    atexit(SDL_Quit);

    /* Выделяем память для структуры представления экрана */
    g->screen = (gamescreen *) malloc(sizeof(gamescreen));
    if (g->screen == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }    
    
    /* Инициализируем видеорежим */
    g->screen->sprite =
        SDL_SetVideoMode(1024, 768, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (g->screen->sprite == NULL) {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Выделяем память для структур заднего фона */
    g->background = (background *) malloc(sizeof(gamescreen));
    if (g->background == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }

    g->background2 = (background *) malloc(sizeof(gamescreen));
    if (g->background2 == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }

    /* Загружаем фон */
    g->background->sprite = SDL_LoadBMP("space.bmp");
    if (g->background->sprite == NULL) {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    g->background2->sprite = SDL_LoadBMP("black.bmp");
    if (g->background2->sprite == NULL) {
        fprintf(stderr, "Couldn't load a bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Выделяем память для структуры представления корабля */
    g->ship = (spaceship *) malloc(sizeof(spaceship));
    if (g->ship == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }
    /* Загрузка картинки корабля */
    g->ship->sprite = SDL_LoadBMP("ship.bmp");
    if (g->ship->sprite == NULL) {
        fprintf(stderr, "Couldn't load a bitmap: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Делаем все белые пиксели, с фона картинки, прозрачными*/
    if(SDL_SetColorKey(g->ship->sprite, SDL_SRCCOLORKEY, SDL_MapRGB(g->ship->sprite->format,255,255,255))!=0)
    {
    fprintf(stderr, "Unable to set colorkey: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

     /*Выделяем память для структуры текста*/
    g->text = (text *) malloc(sizeof(object));
    if (g->text == NULL) {
        fprintf(stderr, "Not enough memory!");
        exit(EXIT_FAILURE);
    }

    /* Загружаем в структуры шрифт */
    g->text->timer = TTF_OpenFont("Times New Roman.ttf", 40);
    if( g->text->timer ==NULL)
    {
    fprintf(stderr, "Couldn't load a font: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    g->text->end = TTF_OpenFont("Times New Roman.ttf", 120);
    if( g->text->end ==NULL)
    {
    fprintf(stderr, "Couldn't load a font: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* Устанавливаем заголовок окна */
    SDL_WM_SetCaption("Space nikita", NULL);

    return g;
}

/* Инициализирует игру */
int run(game * g)
{
    /* Старт времени */
    timer_start = time(NULL);

    /* Флажок выхода */
    int done = 0;
    
    /* Установка кораблика по центру */
    g->ship->y = 640;
    g->ship->x = 450;

    /* Продолжаем выполнение, пока не поднят флажок */
    while (!done) {

        /* Структура описания события */
        SDL_Event event;

        /* Извлекаем и обрабатываем все доступные события */
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            /* Если клавишу нажали */
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    g->ship->vx += -VXD; 
                    break;
                case SDLK_RIGHT:
                    g->ship->vx += VXD; 
                    break;
                case SDLK_UP:
                    g->ship->vy += -VYD;
                    break;
                case SDLK_DOWN:
                    g->ship->vy += VYD;
                    break;
                case SDLK_ESCAPE: /* Выход из программы */
                    done = 1;
                    r=0; /* Флаг конца игры */
                    break;
                }
                break;
            /* Если клавишу отпустили */
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    g->ship->vx += VXD;
                    break;
                case SDLK_RIGHT:
                    g->ship->vx += -VXD;
                    break;
                case SDLK_UP:
                    g->ship->vy += VYD;
                    break;
                case SDLK_DOWN:
                    g->ship->vy += -VYD;
                    break;
                default:
                    break;
                }
                break;
            /* Если закрыли окно */
            case SDL_QUIT:
                r=0; /* Флаг конца игры */
                done = 1;
                break;
            default:
                break;
            }
        }

    /*Ограничиваем игровое поле краями экрана(по х), учитывая размеры самого корабля*/
    if((g->ship->x >= 8|| g->ship->vx > 0)&&(g->ship->x <= 884||g->ship->vx < 0))
        g->ship->x += g->ship->vx;
    
    /*Ограничиваем игровое поле снизу краем экрана, сверху 1/3 (по у), учитывая размеры самого корабля */
    if((g->ship->y >= 512|| g->ship->vy > 0)&&(g->ship->y <= 639||g->ship->vy < 0))
        g->ship->y += g->ship->vy;
        
        /* Отрисовка игрового поля */
        draw(g, &done);

        /* Задержка */
        SDL_Delay(10);
    }
    return endgame();
}


/**
 * Отрисовывает объекты в новой позиции
 * @param g указатель на структуру состояния игры
 */
void draw(game * g, int* done)
{
    /* Прямоугольники, определяющие зону отображения */
    SDL_Rect src, dest, background;

    /*Отображение заднего фона*/
    background.x = 0;
    background.y = 0;
    background.w = g->background->sprite->w;
    background.h = g->background->sprite->h;

    SDL_BlitSurface(g->background->sprite, NULL, g->screen->sprite, &background);

    /* Корабль отображаем целиком */
    src.x = 0;
    src.y = 0;
    src.w = g->ship->sprite->w;
    src.h = g->ship->sprite->h;

    /* в новую позицию */
    dest.x = g->ship->x;
    dest.y = g->ship->y;
    dest.w = g->ship->sprite->w;
    dest.h = g->ship->sprite->h;

    /* Выполняем отображение кораблика на заднем фоне */
    SDL_BlitSurface(g->ship->sprite, &src, g->screen->sprite, &dest);

    /* Таймер */
    Uint32 time_edit = TIMER+timer_start-time(NULL);

    /* Строчка, в которой будет хранится текст, который будет выводиться на таймере */
    char timer[9];

    /* Записываем в строчку слово Time, и значение time_edit */
    sprintf(timer,"%s %d","Time: ", time_edit);

    print_text(timer,5,5,g->text->timer,g);

    /* Время вышло */
    if(time_edit==0)
    {  

    /* Флаг, показывающий, что попытка законечены */
    *done = 1;
    /* Отрисовка черного фона */
    background.x = 0;
    background.y = 0;
    background.w = g->background2->sprite->w;
    background.h = g->background2->sprite->h;
    
    SDL_BlitSurface(g->background2->sprite, NULL, g->screen->sprite, &background);

    /* Выводим текст на экран */
    print_text("Game over!", 250, 200,g->text->end,g);


    SDL_Flip(g->screen->sprite);
    }
    

    /* Отрисовываем обновленный экран */
    SDL_Flip(g->screen->sprite);
}

/* Вывод текста на экран */
void print_text(char *text, int x, int y, TTF_Font *font, game *g) {

    /* Задаем цвет текста */
    SDL_Color color = {255,255,255,0};

    /* Графика */
    SDL_Surface *oblfortext;

    /* Позиция текста */
    SDL_Rect font_pos;
    font_pos.y=y;
    font_pos.x=x;

    /* Отображает текст на объекте*/
    oblfortext = TTF_RenderText_Solid(font,text,color);

    /* Вторая переменная NULL, т.к. текст, так же как и фон статичен */
    SDL_BlitSurface(oblfortext, NULL, g->screen->sprite, &font_pos);
}
int endgame()
{
    /* Если r=0, закрыть игру*/
    if(r==0)
    return 1;
    /* Пользователь пытается выйти из игры */
    while(1)
    {
    SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
        /* Если клавишу нажали */
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
            break;
                case SDLK_ESCAPE: /* Нажать эскейп = выйти из игры*/
            return 1;
                    break;
                }
                break;
                /* Если закрыли игры */
            case SDL_QUIT: 
        return 1;
        break;
            default:
                break;
            }
    }
    }
}