#ifndef _NORMALIZATION_H_
#define _NORMALIZATION_H_

#include "my_utils.h"
#include "validation.h"

int normalize_num(huge_float_t *num);
void remove_first_nulls(int *arr);
void shift_arr_left(int *arr, int n, int start, int end);
void shift_arr_right(int *arr, int n, int start, int end);
void move_point(huge_float_t *num);
void round_product(huge_float_t *num);

#endif