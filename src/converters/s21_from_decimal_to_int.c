#include "../arithmetic/arithmetic_handlers.h"
#include "../additional/decimal_aditional.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  char bufferStr[97] = "\0";
  unsigned long long int ullint = 0;
  *dst = 0;
  if (int_min_check(src)) {
     *dst = INT32_MIN;
  } else {
    decimal_to_str(src, bufferStr);
    ullint = str_to_int(bufferStr);
  }
  if (!not_valid_int(src) && !get_exp_from_decimal(src)) *dst = get_sign(src) ? ullint * (-1) : ullint;
  if (get_exp_from_decimal(src)) {
    float buffer = 0;
    s21_from_decimal_to_float(src , &buffer);
    *dst = (int) buffer;
  }
  return not_valid_int(src);
}
