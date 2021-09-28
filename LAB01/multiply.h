#ifndef _MULTIPLY_H_
#define _MULTIPLY_H_

#include "my_utils.h"
#include "normalization.h"

int multiply(huge_float_t *first_num, huge_float_t *second_num, huge_float_t *result_num);
int is_num_null(mantisa_t mantisa);
void get_product(huge_float_t *first_num, huge_float_t *second_num, huge_float_t *result_num);
void addition(int *product, int *buffer, size_t i);

#endif