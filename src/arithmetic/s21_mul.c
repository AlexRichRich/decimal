#include "arithmetic_handlers.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    decimal_set_zero(result);
    int sign = decimal_is_negative(value_1) + (decimal_is_negative(value_2)*2);
    unsigned int res = 0;
    if (sign == 1 || sign == 3) decimal_minus_plus(&value_1);
    if (sign == 2 || sign == 3) decimal_minus_plus(&value_2);
    decimal_shifter(&value_1, 0);
    decimal_shifter(&value_2, 0);
    for(int i = 0; i <= where_is_begin(value_2); i++) {
        if (what_bit(value_2.bits[i/32], i%32) == 1) add_handler(*result, value_1, result, 2);
        if (div_shifter(&value_1, 1, 1) == 1) {
            res = 1;
            break;
        }
    }
    if (res == 0) add_handler(value_1, value_2, result, 1);
    if (sign == 1 || sign == 2) decimal_minus_plus(result);
    decimal_normalize(result);
    return res;
}
