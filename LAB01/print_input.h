#ifndef _PRINT_INPUT_H_
#define _PRINT_INPUT_H_

#include "my_utils.h"
#include "validation.h"
#include "normalization.h"
#include "multiply.h"

void print_intro();
int input_huge_float(huge_float_t *num);
void str_to_huge_float(char *str, huge_float_t *num);
void print_result(huge_float_t result_num);
void print_mantisa(mantisa_t mantisa);
void print_error(const int rc);

#endif