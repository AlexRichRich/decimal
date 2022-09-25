#include "../arithmetic/arithmetic_handlers.h"

int s21_is_greater(s21_decimal num_1, s21_decimal num_2) {
    int result = 0, sign;
    decimal_prepare(&num_1, &num_2, &sign);
    if (sign == 0) {
        for (int i = 2; i >= 0; i--) {
            if (num_1.bits[i] > num_2.bits[i]) {
                result = 1;
                break;
            }
        }
    } else if (sign == 2) {
        result = 1;
    } else if (sign == 3) {
        for (int i = 2; i >= 0; i--) {
            // printf("%d -- %d, %d\n", num_1.bits[i], num_2.bits[i], i);
            if (num_1.bits[i] < num_2.bits[i]) {
                result = 1;
                break;
            }
        }
    }
    return result;
}
