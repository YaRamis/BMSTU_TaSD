#ifndef _VALIDATION_H_
#define _VALIDATION_H_

short checking_validity(char *num_str);
short checking_input_len(char *str);
short is_there_exp(char *str);
void split_by_exp(char *num_str, char *mant_str, char *order_str);
short checking_mantisa(char *mant_str);
short checking_mantisa_len(char *str);
short checking_for_point(char *str);
short my_is_num(char *str);
short checking_order(char *order_str);

#endif