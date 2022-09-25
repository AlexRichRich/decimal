#include "arithmetic_handlers.h"
#include "../converters/s21_converters.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int is_empty = 0, status = 0, sign;
    is_empty = decimal_is_zero(value_2);
    if (is_empty == 0) {
        decimal_prepare(&value_1, &value_2, &sign);
        div_handler(value_1, value_2, result, 0);
        if (sign == 1 || sign == 2) decimal_minus_plus(result);
    } else {
        status = 3;
    }
    return status;
}

int div_handler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int operation) {
    int mantiss_count = 0, is_empty = 0; 
    s21_decimal val_1_temp = value_1, ten;
    s21_from_int_to_decimal(10, &ten);
    decimal_set_zero(result);
    int val_1_start = where_is_begin(value_1);
    int val_2_start = where_is_begin(value_2);
    div_shifter(&value_2, 1, val_1_start-val_2_start);
    for(int i = 0; i <= val_1_start-val_2_start; i++) {
        div_shifter(result, 1, 1);
        if (div_sub(value_1, value_2, &value_1, val_2_start) == 0) {
            add_bit(result, 0, 0, 1);
    } else {
        add_bit(result, 0, 0, 0);
    }
    if (i < val_1_start-val_2_start) div_shifter(&value_2, 0, 1);
    if (i == val_1_start-val_2_start) {
        is_empty = 0;
        is_empty = decimal_is_zero(value_1);
        if (operation == 0 && is_empty == 0 && mantiss_count < 7) {
            i = -1;
            s21_mul(val_1_temp, ten, &val_1_temp);
            val_1_start = where_is_begin(val_1_temp);
            mantiss_count++;
            decimal_set_zero(result);
            value_1 = val_1_temp;
            div_shifter(&value_2, 1, val_1_start-val_2_start);
        }
    }
    }
    while (mantiss_count-- > 0) mantissa_changer(result, 1);
    if (operation == 0) decimal_shifter(result, 1);
    decimal_normalize(result);
    return 0;
}
