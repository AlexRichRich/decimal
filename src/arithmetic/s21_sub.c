#include "arithmetic_handlers.h"

// int main() {
//     s21_decimal target_1 = {0,0,0,0};
//     s21_from_int_to_decimal(-2147483648, &target_1);
//     s21_decimal target_2 = {0,0,0,0};
//     s21_from_int_to_decimal(-2147483648, &target_2);
//     s21_decimal target_3 = {0,0,0,0};
//     int result = 0;
//     s21_sub(target_1, target_2, &target_3);
//     print_decimal(target_3);
//     s21_from_decimal_to_int(target_3, &result);
//     printf("num - %d\n", result);
// }

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int status = 0, adress, bit, result_1, result_2, sign, shift, less = 0;
    if ((decimal_is_negative(value_1) == 0 && decimal_is_negative(value_2) == 1) ||
        (decimal_is_negative(value_1) == 1 && decimal_is_negative(value_2) == 0)) {
            decimal_minus_plus(&value_2);
            status = s21_add(value_1, value_2, result);
    } else {
        decimal_set_zero(result);
        shift = decimal_prepare(&value_1, &value_2, &sign);
        if (s21_is_less(value_1, value_2)) {
        s21_decimal boofer = value_1;
        value_1 = value_2;
        value_2 = boofer;
        less = 1;
    }
        for(int i = 0; i < 96; i++) {
            pilling_bits(value_1, value_2, &adress, &bit, &result_1, &result_2, i);
            if(result_1 == 0 && result_2 == 1) {
                if(loan_num(&value_1, adress, bit, 96) == 0) {
                    add_bit(result, adress, bit, 1);
                } else {
                    status = 1;
                    break;
                }
            } else {
                add_bit(result, adress, bit, result_1-result_2);
            }
        }
    while(shift-- > 0) mantissa_changer(result, 1);
    decimal_shifter(result, 1);
    if (sign == 3) decimal_minus_plus(result);
    if (less == 1) decimal_minus_plus(result);
    }
    decimal_normalize(result);
    return status;
}
