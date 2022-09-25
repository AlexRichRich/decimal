#ifndef S21_CONVERTERS_H_
#define S21_CONVERTERS_H_

#include "../arithmetic/arithmetic_handlers.h"

#define N_SIGN 31
#define NO_ERROR 0
#define ERROR 1
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
#define ADD_BIT(X, POS) ((X) |= (1 << (POS)))
#define IS_SET(X, POS) ((X >> POS) & 1)

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif  //  S21_CONVERTERS_H_
