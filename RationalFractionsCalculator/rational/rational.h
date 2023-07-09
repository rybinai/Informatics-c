#ifndef RATIONAL_H
#define RATIONAL_H

typedef struct {
    int num;
    unsigned int denom;
} rational_t;

/*
 * Возвращает рациональное число, получаемое как результат деления
 * n на d.
 */
rational_t rational(int n, int d);

/*
 * Возвращает числитель рационального числа r.
 */
int rat_num(rational_t r);

/*
 * Возвращает знаменатель рационального числа r.
 */
int rat_denom(rational_t r);

#endif
