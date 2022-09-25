#include "../arithmetic/arithmetic_handlers.h"
#include "../converters/s21_converters.h"

int s21_round(s21_decimal value, s21_decimal *result) {
    decimal_set_zero(result);
    int sign = decimal_is_negative(value);
    if (sign == 1) decimal_minus_plus(&value);
    s21_decimal val_trunc, remainder;
    s21_floor(value, &val_trunc);
    s21_sub(value, val_trunc, &remainder);
    s21_sub(value, remainder, result);
    s21_decimal half_life = {{5, 0, 0, 1}}, one;
    s21_from_int_to_decimal(1, &one);
    decimal_shifter(&half_life, 1);
    if (s21_is_greater_or_equal(remainder, half_life)) {
        s21_add(*result, one, result);
    }
    if (sign == 1) decimal_minus_plus(result);
    return 0;
}