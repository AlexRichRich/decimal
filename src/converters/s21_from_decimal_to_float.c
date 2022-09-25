#include "../arithmetic/arithmetic_handlers.h"
#include "../additional/decimal_aditional.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int exp = get_exp_from_decimal(src);
  char bufferStr[97] = "\0";
  decimal_to_str(src, bufferStr);
  unsigned long long int ullfloat = str_to_int(bufferStr);
  long double result = ullfloat;
  result *= get_sign(src) ? (-1) : 1;
  result /= exp ? pow(10, exp) : 1;
  *dst = (float)result;
  return NO_ERROR;
}
