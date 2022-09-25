#include "../arithmetic/arithmetic_handlers.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
    decimal_set_zero(result);
    *result = value;
    decimal_minus_plus(result);
    return 0;
}