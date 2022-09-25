#include "../s21_decimal.h"
#include "s21_converters.h"
#include "../additional/decimal_aditional.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return ERROR;
  memset(dst, 0, sizeof(*dst));
  if (src != 0) {
    char intStr[97] = "\0";
    unsigned long long int ullint = abs(src);
    if (src < 0) set_neg_sign(dst);
    int_to_str(ullint, intStr);
    str_to_decimal(intStr, dst);
  }
  return NO_ERROR;
}
