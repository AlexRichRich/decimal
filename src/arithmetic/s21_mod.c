#include "arithmetic_handlers.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int is_empty = 0, status = 0, sign;
    decimal_set_zero(result);
    is_empty = decimal_is_zero(value_2);
    if (is_empty == 0) {
        int shift = decimal_prepare(&value_1, &value_2, &sign);
        s21_decimal boofer;
        div_handler(value_1, value_2, &boofer, 1);
        s21_mul(boofer, value_2, &boofer);
        s21_sub(value_1, boofer, result);
        while (shift-- > 0) mantissa_changer(result, 1);
        decimal_shifter(result, 1);
        if (sign == 1 || sign == 3) decimal_minus_plus(result);
    } else {
        status = 3;
    }
    decimal_normalize(result);
    return status;
}