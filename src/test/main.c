#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
    int bits[4];
} s21_decimal;

int get_exponent(float num);
int get_not_exponent(float num);
int string_from_float(float num, char* str);
int float_from_string(float* num, char* str, int exp);
int from_decimal_to_int(int* dst, s21_decimal src);
int from_int_to_decimal(int src, s21_decimal *dst);
int from_decimal_to_float(float* num, s21_decimal dst, int exp);
int int_from_string(int* num, char* str);
int from_float_to_decimal(float num, s21_decimal* dst);

int main() {
  float value = 1.00010;
  printf("VAL %f\n", value);
  int exp = get_exponent(value);
  s21_decimal dst;
  from_float_to_decimal(value, &dst);
  float res = 0;
  from_decimal_to_float(&res, dst, exp);
  printf("ORIG:\t %f\nRES:\t %f\n", value, res);
  return 0;
}

int from_float_to_decimal(float num, s21_decimal* dst) {
  int exp = get_exponent(num);
  char buf[50] = "\0";
  int converted_to_int = 0;
  float unum = floorf(num * pow(10, exp));
  string_from_float(num, buf);
  int_from_string(&converted_to_int, buf);
  if (converted_to_int == unum) {
    from_int_to_decimal(unum, dst);
  }
  return 0;
}

int from_decimal_to_float(float* num, s21_decimal dst, int exp) {
  int get = 0;
  from_decimal_to_int(&get, dst);
  *num = (float)get / pow(10, exp);
  return 0;
}

int from_decimal_to_int(int* dst, s21_decimal src) {
  *(dst) = src.bits[0];
  return 0;
}

int from_int_to_decimal(int src, s21_decimal *dst) {
  memset(dst, 0, sizeof(int) * 4);
  // if (src < 0) fill_negative(dst);
  dst->bits[0] = abs(src);
  return 0;
}

int string_from_float(float num, char* str) {
  int exp = get_exponent(num);
  int not_exp = get_not_exponent(num);
  num *= pow(10, exp);
  int ndigit = exp + not_exp;
  gcvt(num, ndigit, str);
  return 0;
}

int int_from_string(int* num, char* str) {
  *num = atoi(str);
  return 0;
}

int float_from_string(float* num, char* str, int exp) {
  *num = atof(str);
  *num /= pow(10, exp);
  return 0;
}

int get_exponent(float num) {
  int exponent = 0;
  for (; num != floorf(num); exponent++)
    num *= 10;
  return exponent;
}

int get_not_exponent(float num) {
  int exponent = 0;
  for (; num >= 1; exponent++)
    num /= 10;
  return exponent;
}