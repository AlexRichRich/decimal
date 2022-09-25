#include "arithmetic_handlers.h"
#include "../converters/s21_converters.h"

int decimal_is_zero(s21_decimal num) {
    int result = 0;
    for (int i = 0; i < 3; i++) result += decimal_is_null(num, i);
    return result > 0 ? 0 : 1;
}

int decimal_prepare(s21_decimal *target_1, s21_decimal *target_2, int *sign) {  // sign 0 if both positive
    decimal_normalize(target_1);
    decimal_normalize(target_2);
    *sign = decimal_is_negative(*target_1); // sign 1 if first negative
    if (decimal_is_negative(*target_2) == 1) *sign += 2;  // sign 3 if both negative, sign 2 if second negative
    if (*sign == 1 || *sign == 3) decimal_minus_plus(target_1);
    if (*sign == 2 || *sign == 3) decimal_minus_plus(target_2);
    decimal_shifter(target_1, 0);
    decimal_shifter(target_2, 0);
    int shift = 0;
    while(decimal_is_null(*target_1, 3) != 0 && decimal_is_null(*target_2, 3) != 0) {
        mantissa_changer(target_1, 0);
        mantissa_changer(target_2, 0);
        shift++;
    }
    s21_decimal ten;
    s21_from_int_to_decimal(10, &ten);
    while (decimal_is_null(*target_1, 3) != 0) {
        s21_mul(*target_2, ten, target_2);
        mantissa_changer(target_1, 0);
        shift++;
    }
    while (decimal_is_null(*target_2, 3) != 0) {
        // printf("1");
        s21_mul(*target_1, ten, target_1);
        mantissa_changer(target_2, 0);
        shift++;
    }
    return shift;
}

void mantissa_changer(s21_decimal *target, int operation) {
    int result;
    result = what_bit(target->bits[3], 0);
    if (operation == 0) {
        if(result == 0) {
            if(loan_mantissa_num(target) == 0) add_bit(target, 3, 0, 1);
        } else {
            add_bit(target, 3, 0, 0);
        }
    } else if (operation == 1) {
        target->bits[3] += 1;
    }
}

int loan_mantissa_num(s21_decimal* borrower) {
    int status = 1;
    for (int i = 0; i < 32; i++) {
        if(what_bit(borrower->bits[3], i%32) == 1) {
            status = 0;
            add_bit(borrower, 3, i, 0);
            for (int y = i-1; y > 0; y--) add_bit(borrower, 3, y, 1);
            break;
        }
    }
    return status;
}

void decimal_shifter(s21_decimal *target, int operation) {
    if (operation == 0) target->bits[3] >>= 16;  // if operation == 0 shift mantissa bits at begin
    else target-> bits[3] <<= 16;  // if operation == 1 restore mantissa bits
}

int decimal_is_null(s21_decimal target, int adress) {return target.bits[adress] == 0 ? 0 : 1;}

int decimal_is_negative(s21_decimal target_1) {return what_bit(target_1.bits[3], 31);}

int decimal_minus_plus(s21_decimal *pacient) {  // if mod == 1 - decimal from negative to positive
    int result = 0;                                      // else if mod == 0 - decimal from positive to negative
    if ((pacient->bits[3] & (1 << 31)) != 0) {
        add_bit(pacient, 3, 31, 0);
    } else {
        add_bit(pacient, 3, 31, 1);
    }
    return result;
}

void pilling_bits(s21_decimal value_1, s21_decimal value_2, int* adress,
                    int* bit, int* result_1, int* result_2, int i) {
    *adress = i/32;
    *bit = i%32;
    *result_1 = what_bit(value_1.bits[*adress], *bit);
    *result_2 = what_bit(value_2.bits[*adress], *bit);
}

void decimal_set_zero(s21_decimal* target) {for(int i = 0; i < 4; i++) target->bits[i] = 0;}


int what_bit(int target, int bit) {
    int check = 1 << bit;
    int result = 0;
    if ((target & check) != 0) result = 1;
    // printf("bit - %d\n", result);
    return result;
}

void add_bit(s21_decimal* target, int adress, int bit, int value) {  // add bit *value* in decimal *target.bits[adress]* on position *bit*
    int check = 1 << bit;
    if (value == 0) {  // if value == 0 reverse all bits. example: 110101110 & 111110111 = 110100110
        check = ~check;
        target->bits[adress] &= check;
    } else {
    target->bits[adress]  |= check;  // if value == 1 compare with operator "|" example: 01010100 | 00001000 = 01011100
    }
}

void print_decimal(s21_decimal decimal) {
    for (int i = 0; i < 128; i++) {
        if(i%32 == 0) printf("Bits[%d] - ", i/32);
        printf("%d", what_bit(decimal.bits[i/32], 31-i%32));
        if(i%32 == 31) printf("\n");
    }
}

int loan_num(s21_decimal* borrower, int adress, int bit, int len) {
    if(adress != 0) bit = bit+(adress*32);
    int status = 1;
    if (len != 96) len = where_is_begin(*borrower);
    // printf("\nBEFORE\n");
    // print_decimal(*borrower);
    for (int i = bit+1; i < 96; i++) {
        if(what_bit(borrower->bits[i/32], i%32) == 1) {
            status = 0;
            add_bit(borrower, i/32, i%32, 0);
            // add_bit(borrower, i/32, i%32, 0);
            // print_decimal(*borrower);
            for (int y = i-1; y >= bit; y--) add_bit(borrower, y/32, y%32, 1);
            break;
        }
    }
    // printf("status - %d\n", status);
    // printf("\nAFTER\n|\n");
    // print_decimal(*borrower);
    return status;
}

int where_is_begin(s21_decimal target) {  // return position of first number == 1 in decimal
    int result = 0;
    for (int i = 95; i >= 0; i--) {
        if (what_bit(target.bits[i/32], i%32) == 1) {
            result = i;
            break;
        }
    }
    return result;
}

int div_shifter(s21_decimal* divider, int operation, int shift) {  // move bits[0-2] in decimal
    int result = 0;
    for (int i = 0; i < shift; i++) {                           // if operation == 0 move in left,
        if (operation == 1) {
            if (what_bit(divider->bits[2], 31) == 1) {
                result = 1;
            } else {
                for (int y = 94; y >= 0; y--) {                      // if operation == 1 move in right
                    add_bit(divider, (y+1)/32, (y+1)%32, what_bit(divider->bits[y/32], y%32));
                }
            }
        } else if (operation == 0) {
            for (int y = 1; y < 96; y++) {
                add_bit(divider, (y-1)/32, (y-1)%32, what_bit(divider->bits[y/32], y%32));
            }
        }
        operation == 0 ? add_bit(divider, (95-i)/32, (95-i)%32, 0) : add_bit(divider, i/32, i%32, 0);
    }
    return result;
}

int div_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result, int num_2_len) {
    s21_decimal reserve;
    int status = 0;
    int adress = 0;
    int bit = 0;
    int result_1 = 0;
    int result_2 = 0;
    reserve = *result;
    for(int i = where_is_begin(value_2)-num_2_len; i <= where_is_begin(value_2)+1; i++) {
        pilling_bits(value_1, value_2, &adress, &bit, &result_1, &result_2, i);
        if(result_1 == 0 && result_2 == 1) {
            if(loan_num(&value_1, adress, bit, num_2_len) == 0) {
                add_bit(result, adress, bit, 1);
            } else {
                // print_decimal(reserve);
                status = 1;
                for(int i = 0; i < 4; i++) result->bits[i] = reserve.bits[i];
                break;
            }
        } else {
            add_bit(result, adress, bit, result_1-result_2);
        }
    }
    return status;
}

int decimal_normalize(s21_decimal *target) {
    s21_decimal boofer = *target, normalize, ten;
    s21_from_int_to_decimal(10, &ten);
    int shift = 0, sign = 0;
    if(decimal_is_negative(boofer)) {
        decimal_minus_plus(&boofer);
        sign = 1;
    }
    decimal_shifter(&boofer, 0);
    while(decimal_is_null(boofer, 3)) {
        mantissa_changer(&boofer, 0);
        shift++;
    }
    while(shift > 0) {
        div_handler(boofer, ten, &normalize, 1);
        s21_mul(normalize, ten, &normalize);
        if(!s21_is_equal(boofer, normalize)) break;
        shift--;
        div_handler(boofer, ten, &boofer, 1);
    }
    while(shift-- > 0) mantissa_changer(&boofer, 1);
    *target = boofer;
    decimal_shifter(target, 1);
    if (sign == 1) decimal_minus_plus(target);
    return 0;
}
