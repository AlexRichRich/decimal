#ifndef SRC_S21_ARITHMETIC_HANDLERS_H_
#define SRC_S21_ARITHMETIC_HANDLERS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define N_SIGN 31
#define NO_ERROR 0
#define ERROR 1
#define SET_BIT(X, BIT, POS) (X |= (BIT << POS))
#define ADD_BIT(X, POS) ((X) |= (1 << (POS)))
#define IS_SET(X, POS) ((X >> POS) & 1)

typedef struct {
    unsigned int bits[4];
} s21_decimal;

int what_bit(int target, int bit);
void add_bit(s21_decimal* target, int adress, int bit, int value);
void print_decimal(s21_decimal decimal);
void decimal_set_zero(s21_decimal* target);
void pilling_bits(s21_decimal value_1, s21_decimal value_2, int* adress,
                    int* bit, int* result_1, int* result_2, int i);
int decimal_prepare(s21_decimal *target_1, s21_decimal *target_2, int *sign);
int decimal_is_negative(s21_decimal target_1);
int decimal_minus_plus(s21_decimal *pacient);
int loan_num(s21_decimal* borrower, int adress, int bit, int len);
int loan_mantissa_num(s21_decimal* borrower);
void decimal_shifter(s21_decimal *target, int operation);
int decimal_is_null(s21_decimal target, int adress);
void mantissa_changer(s21_decimal *target, int operation);
int div_shifter(s21_decimal* divider, int operation, int shift);
int where_is_begin(s21_decimal target);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int div_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int num_2_len);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int add_handler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int operation);
int s21_is_not_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater(s21_decimal num_1, s21_decimal num_2);
int s21_is_greater_or_equal(s21_decimal num_1, s21_decimal num_2);
int s21_is_less(s21_decimal num_1, s21_decimal num_2);
int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2);
int decimal_is_zero(s21_decimal num);
int s21_negate(s21_decimal value, s21_decimal *result);
int div_handler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int operation);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int decimal_normalize(s21_decimal *target);

#endif  //  SRC_S21_ARITHMETIC_HANDLERS_H_