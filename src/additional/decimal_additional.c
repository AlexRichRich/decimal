#include "../arithmetic/arithmetic_handlers.h"
#include "../s21_decimal.h"
#include "decimal_aditional.h"
#include <stdio.h>

char to_string (float value, char *buf) {
  int ndigit = 50;
  char res = *gcvt(value, ndigit, buf);

  return res;
}

//  CONVERTERS ADDITIONAL PART
void set_neg_sign(s21_decimal *decimal) {
  ADD_BIT(decimal->bits[3], N_SIGN);
}

void int_to_str(unsigned long long int  num, char* intBuffer) {
  for (int i = 0; i < 96; i++, num /= 2)
    intBuffer[i] = ((num % 2) == 0) ?  '0' : '1';
}

void str_to_decimal(char* intStr, s21_decimal* intDec) {
  for (int i = 0; i < 96 && i < (int)strlen(intStr); i++)
    if (intStr[i] == '1') intDec->bits[i / 32] |= 1 << i;
}

void decimal_to_str(s21_decimal src, char* buffer) {
  for (int i = 0; i < 96; i++)
    buffer[i] = (src.bits[i / 32] & (1 << i)) ? '1' : '0';
  if(strrchr(buffer, '1')) *(strrchr(buffer, '1') + 1) = '\0';
  revstr(buffer);
}

bool get_sign(s21_decimal decimal) {
  return IS_SET(decimal.bits[3], N_SIGN);
}

int all_bits_set(s21_decimal dec) {
  return (dec.bits[0] == UINT32_MAX && dec.bits[1] == UINT32_MAX && dec.bits[2] == UINT32_MAX) ? 1 : 0;
}

int not_valid_int(s21_decimal dec) {
  int result = 1;
  if (all_bits_set(dec)) result = 0;
  else if (dec.bits[1] == 0 && dec.bits[2] == 0 && dec.bits[0] == UINT32_MAX) result = 0;
  return result;
}

int get_exponent(float num) {
  char str[501] = "\0";
  sprintf(str, "%.8f", num);
  for (int i = (int)strlen(str) - 1; str[i] == '0' && i >= 0; str[i--] = '\0') { }
  char* p = strpbrk(str, ".");
  return p ? (int)strlen(p + 1) : 0;
}

void exp_to_decimal(int exp, s21_decimal* dst) {
  char intStr[9] = "\0";

  for (int i = 0; i < 8; i++, exp /= 2)
    intStr[i] = ((exp % 2) == 0) ? '0' : '1';
  if (strrchr(intStr, '1')) {
    *(strrchr(intStr, '1') + 1) = '\0';
    for (int i = 0; i < 8 && i < (int)strlen(intStr); i++)
      if (intStr[i] == '1') dst->bits[3] |= 1 << (i + 15);
  }
}

int get_exp_from_decimal(s21_decimal src) {
  char buffer[9] = "\0";
  for (int i = 15, j = 0; i < 23; i++, j++)
    buffer[j] = IS_SET(src.bits[3], i) ? '1' : '0';

  if (strrchr(buffer, '1')) *(strrchr(buffer, '1') + 1) = '\0';
  revstr(buffer);
  return str_to_int(buffer);
}

int int_min_check(s21_decimal dec)  {
  return (get_sign(dec) && all_bits_set(dec)) ? 1 : 0;
}

int str_to_int(char* intStr) {
  unsigned long long int result = 0;
  for (int i = 0; i < (int)strlen(intStr); i++)
    if(intStr[i] == '1') result += pow(2, strlen(intStr) - i - 1);
  return result;
}

void revstr(char *str1) {
  int i, len, temp;
  len = strlen(str1);

  for (i = 0; i < len/2; i++) {
    temp = str1[i];
    str1[i] = str1[len - i - 1];
    str1[len - i - 1] = temp;
  }
}

//  CONVERTERS ADDITIONAL EOP

//  DEBUG PART

void decimal_printer(s21_decimal print) {
  for (int i = 0; i < 4; binary_printer(print.bits[i++])) printf("bits[%d]: ", i);
}

void binary_printer(int b) {
  for (int i = 31; i >= 0; i--)
    IS_SET(b, i) ? printf("1") : printf("0");
  printf("\n");
}
//  DEBUG EOP
