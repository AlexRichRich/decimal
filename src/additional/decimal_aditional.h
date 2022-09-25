#ifndef DECIMAL_ADDITIONAL_H_
#define DECIMAL_ADDITIONAL_H_

#include "../s21_decimal.h"
#include "../arithmetic/arithmetic_handlers.h"
//  CONVERTERS ADDITIONAL PART
void set_neg_sign(s21_decimal *decimal);
void int_to_str(unsigned long long int  num, char* intBuffer);
void str_to_decimal(char* intStr, s21_decimal* intDec);
void decimal_to_str(s21_decimal src, char* buffer);
bool get_sign(s21_decimal decimal);
int all_bits_set(s21_decimal dec);
int not_valid_int(s21_decimal dec);
int get_exponent(float num);
void exp_to_decimal(int exp, s21_decimal* dst);
int get_exp_from_decimal(s21_decimal src);
int int_min_check(s21_decimal dec);
int str_to_int(char* intStr);
void revstr(char *str1);
//  CONVERTERS ADDITIONAL EOP

//  DEBUG PART

void decimal_printer(s21_decimal print);
void binary_printer(int b);

//  DEBUG EOP

#endif  //  DECIMAL_ADDITIONAL_H_
