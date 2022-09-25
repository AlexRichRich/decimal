#include "../arithmetic/arithmetic_handlers.h"
#include "../converters/s21_converters.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
    decimal_set_zero(result);
    int sign = decimal_is_negative(value);
    if (sign == 1) decimal_minus_plus(&value);
    s21_decimal val_trunc, remainder;
    s21_truncate(value, &val_trunc);
    s21_sub(value, val_trunc, &remainder);
    s21_sub(value, remainder, result);
    if (sign == 1) {
        s21_decimal one;
        s21_from_int_to_decimal(1, &one);
        s21_add(*result, one, result);
        decimal_minus_plus(result);
    }
    return 0;
}