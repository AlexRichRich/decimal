#include "../arithmetic/arithmetic_handlers.h"

int s21_is_equal(s21_decimal num_1, s21_decimal num_2) {
    int sign = 0;
    decimal_prepare(&num_1, &num_2, &sign);
    int match = 0;
    if (sign == 0 || sign == 3) {
        for(int i = 0; i < 4; i++) {
            if ((num_1.bits[i] ^ num_2.bits[i]) == 0) {
                match = 1;
            } else {
                match = 0;
                break;
            }
        }
    }
    return match;
}
