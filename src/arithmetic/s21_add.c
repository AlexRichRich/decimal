#include "arithmetic_handlers.h"

// int main() {
//     s21_decimal target_1 = {3,0,0,0};
//     s21_decimal target_2 = {3,0,0,0};
//     s21_decimal target_3 = {0,0,0,0};
//     int result = 0;
//     s21_add(target_1, target_2, &target_3);
//     print_decimal(target_3);
//     s21_from_decimal_to_int(target_3, &result);
//     printf("num - %d\n", result);
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int is_negative = 0;
    int res = 0;
    is_negative = decimal_is_negative(value_1) + decimal_is_negative(value_2);
    if (is_negative == 1) {
        res = s21_sub(value_1, value_2, result);
    } else {
        decimal_set_zero(result);
        res = add_handler(value_1, value_2, result, 0);
    }
    return res;
}

int add_handler(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int operation) {
    int adress = 0, bit = 0, result_1 = 0, result_2 = 0, num_in_mind = 0, mod = 0, sign = 0, shift = 0;
    if (operation == 0) shift = decimal_prepare(&value_1, &value_2, &sign);
    if (operation == 1) mod = 32;
    for (int i = 0+mod*3; i < 96+mod; i++) {
        pilling_bits(value_1, value_2, &adress, &bit, &result_1, &result_2, i);
        if (result_1 == 1 && result_2 == 1 && num_in_mind == 0) {
            add_bit(result, adress, bit, 0);
            num_in_mind = 1;
        } else if (result_1 == 1 && result_2 == 1 && num_in_mind == 1) {
            add_bit(result, adress, bit, 1);
        } else if(result_1+result_2+num_in_mind > 1) {
            add_bit(result, adress, bit, 0);
            num_in_mind = 1;
        } else {
                add_bit(result, adress, bit, result_1+result_2+num_in_mind);
                if(num_in_mind > 0) num_in_mind = 0;
        }
    }
    while (shift-- > 0) mantissa_changer(result, 1);
    decimal_shifter(result, 1);
    if (sign > 0) decimal_minus_plus(result);
    if (decimal_is_negative(*result) && num_in_mind) num_in_mind += 1;
    return num_in_mind;
}