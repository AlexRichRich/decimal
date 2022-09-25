#include "../arithmetic/arithmetic_handlers.h"

int s21_is_less_or_equal(s21_decimal num_1, s21_decimal num_2) {
    int result = 0;
    if (s21_is_greater(num_1, num_2) == 0) result = 1;
    return result;
}