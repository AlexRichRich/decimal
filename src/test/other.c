// https://www.youtube.com/watch?v=U0U8Ddx4TgE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int bits[4];
} s21_decimal;

#define IS_SET(X, POS) ((X >> POS) & 1U);
#define D_SIGN 31

bool get_sign(int num);
void my_revstr(char *str1);
int float_from_string(float* num, char* str, int exp);
int string_from_float(float num, char* str);
int int_from_string(int* num, char* str);
int get_exponent(float num);
int get_not_exponent(float num);
int create_binary_M(char* before, char* after, char* mpart);
void get_binary_from_int(int num, char* buf);
void get_binary_from_exp(char* after, char* buf);
int converter(float fnum, char* result);

int main() {
  float fnum = 0;
  char result[100] = "\0";
  printf("Enter float to convert: ");
  scanf("%f", &fnum);
  converter(fnum, result);
  printf("Result: %s", result);
  return 0;
}

int converter(float fnum, char* result) {
  char before[50] = "\0";
  char after[50] = "\0";
  bool S = 0;
  char str[50]= "\0";
  
  string_from_float(fabsf(fnum), str);
  if(fnum < 0) 
    S = 1;
  else 
    S = 0;

  sprintf(before, "%.*s", get_not_exponent(fabsf(fnum)), str);
  if(get_exponent(fabsf(fnum))) sprintf(after, "%s", str + get_not_exponent(fabsf(fnum)));
  char mpart[50] = "\0";
  int epart = create_binary_M(before, after, mpart);
  sprintf(result, "(-1)^%d*1.%s*10^%d", S, mpart, epart);
  return 0;
}

int create_binary_M(char* before, char* after, char* mpart) {
  int E = 0;
  char binary_before[50] = "\0";
  get_binary_from_int(atoi(before), binary_before);
  char binary_after[50] = "\0";
  get_binary_from_exp(after, binary_after);
  if(strpbrk(binary_before, "1"))
    E = (int)strlen(binary_before) - 1;
  else
    E = ((int)(strspn(binary_after, "0")) + 1) * (-1);
  if(E == 0)
    sprintf(mpart, "%s", binary_after);
  else if (E > 0)
    sprintf(mpart, "%s%s", binary_before + 1, binary_after);
  else if (E < 0)
    sprintf(mpart, "%s", binary_after + (E * (-1)));
  return E;
}

void get_binary_from_exp(char* after, char* buf) {
  float buffer = 0;
  float_from_string(&buffer, after, strlen(after));
  for (size_t i = 0; i < 500 && buffer != floorf(buffer); i++, buffer *= 2) {
    if(floorf(buffer * 2) == 0)
      buf[i] = '0';
    else
      buf[i] = '1';
  }
}

void get_binary_from_int(int num, char* buf) { 
  for (int i = 0; num > 0 && i < 500; i++, num /= 2) {
    if ((num % 2) == 0)
      buf[i] = '0';
    else 
      buf[i] = '1';
  }
  my_revstr(buf);
}

void my_revstr(char *str1) {    
  int i, len, temp;  
  len = strlen(str1);  
       
  for (i = 0; i < len/2; i++) {  
    temp = str1[i];  
    str1[i] = str1[len - i - 1];  
    str1[len - i - 1] = temp;  
  }  
}  

bool get_sign(int num) {
    return IS_SET(num, D_SIGN);
}

int string_from_float(float num, char* str) {
  int exp = get_exponent(num);
  int not_exp = get_not_exponent(num);
  num *= pow(10, exp);
  int ndigit = exp + not_exp;
  gcvt(num, ndigit, str);
  return 0;
}

int int_from_string(int* num, char* str) {
  *num = atoi(str);
  return 0;
}

int float_from_string(float* num, char* str, int exp) {
  *num = atof(str);
  *num /= pow(10, exp);
  return 0;
}

int get_exponent(float num) {
  int exponent = 0;
  for (; num != floorf(num); exponent++)
    num *= 10;
  return exponent;
}

int get_not_exponent(float num) {
  int exponent = 0;
  for (; num >= 1; exponent++)
    num /= 10;
  return exponent;
}