#include "../arithmetic/arithmetic_handlers.h"
#include "../converters/s21_converters.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
    decimal_set_zero(result);
    int shift = 0, sign = decimal_is_negative(value);
    if (sign == 0) decimal_minus_plus(&value);
    decimal_shifter(&value, 0);
    s21_decimal ten;
    s21_from_int_to_decimal(10, &ten);
    while (decimal_is_null(value, 3) != 0) {
        mantissa_changer(&value, 0);
        shift++;
    }
    while (shift--) div_handler(value, ten, &value, 1);
    *result = value;
    if (sign == 1) decimal_minus_plus(result);
    return 0;
}