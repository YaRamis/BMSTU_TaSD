#ifndef _VALIDATION_H_
#define _VALIDATION_H_

#include "my_utils.h"

int checking_validity(char *num_str);
int checking_input_len(char *str);
int is_there_exp(char *str);
int split_by_exp(char *num_str, char *mant_str, char *order_str);
int checking_mantisa(char *mant_str);
int checking_mantisa_len(char *str);
int checking_for_point(char *str);
int my_is_num(char *str);
int checking_order(char *order_str);

#endif