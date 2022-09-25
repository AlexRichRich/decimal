#include "../s21_decimal.h"
#include "../additional/decimal_aditional.h"

int s21_float_to_decimal(float src, s21_decimal* dst) {
  if (!dst) return ERROR;  //  Need to check is float src normal
  memset(dst, 0, sizeof(*dst));
  if (src != 0) {
    if (src < 0) set_neg_sign(dst);
    char floatStr[98] = "\0";
    int exp = get_exponent(src);
    exp_to_decimal(exp, dst);
    long long int llint = (src * (exp ? (float)pow(10, exp) : 1));
    if (src < 0) llint *= (-1);
    int_to_str(llint, floatStr);
    str_to_decimal(floatStr, dst);
  }
  return NO_ERROR;
}
