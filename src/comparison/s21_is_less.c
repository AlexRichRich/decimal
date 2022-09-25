#include "../arithmetic/arithmetic_handlers.h"

int s21_is_less(s21_decimal num_1, s21_decimal num_2) {
    return !s21_is_greater_or_equal(num_1, num_2);
}