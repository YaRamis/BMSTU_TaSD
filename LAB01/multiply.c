#include "multiply.h"

int multiply(huge_float_t *first_num, huge_float_t *second_num, huge_float_t *result_num)
{
    if (is_num_null(first_num->mantisa) != EXIT_SUCCESS && is_num_null(second_num->mantisa) != EXIT_SUCCESS)
    {
        result_num->order = first_num->order + second_num->order;

        if (first_num->sign_m != second_num->sign_m)
            result_num->sign_m = '-';

        get_product(first_num, second_num, result_num);
        
        normalize_num(result_num);
        
        int i = MAX_MANTISA_DIGITS * 2;
        while (result_num->mantisa[i] == 0)
            i--;
        
        if (i > MAX_MANTISA_DIGITS && result_num->mantisa[MAX_MANTISA_DIGITS + 1] >= 5)
            round_product(result_num);
        
        if (result_num->order < MIN_ORDER_VALUE || result_num->order > MAX_ORDER_VALUE)
            return ORDER_OVERFLOW;
    }
    return EXIT_SUCCESS;
}

int is_num_null(mantisa_t mantisa)
{
    for (size_t i = 1; i < MAX_MANTISA_DIGITS + 1; i++)
        if (mantisa[i] != 0)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void get_product(huge_float_t *first_num, huge_float_t *second_num, huge_float_t *result_num)
{
    int buffer[MAX_MANTISA_DIGITS + 1] = {0};
    int tens_digit = 0;
    int digits_product = 0;
    int flag_i = 0, flag_j = 0;
    size_t buff_i = 0;
    size_t step = 0;
    for (size_t i = MAX_MANTISA_DIGITS; i > 0; i--)
    {
        if (first_num->mantisa[i] != 0 && flag_i == 0)
            flag_i = i;
        if (flag_i != 0)
        {
            tens_digit = 0;
            buff_i = MAX_MANTISA_DIGITS;
            flag_j = 0;
            for (size_t j = MAX_MANTISA_DIGITS; j > 0; j--)
            {
                if (second_num->mantisa[j] != 0 && flag_j == 0)
                    flag_j = j;
                if (flag_j != 0)
                {
                    digits_product = first_num->mantisa[i] * second_num->mantisa[j] + tens_digit;
                    buffer[buff_i] = digits_product % 10;
                    buff_i--;
                    tens_digit = digits_product / 10;
                }
            }
            buffer[buff_i] = tens_digit;
            addition(result_num->mantisa, buffer, step);
            step++;
        }
    }
    result_num->mantisa[MAX_MANTISA_DIGITS * 2 - flag_j -flag_i] = POINT;
}

void addition(int *product, int *buffer, size_t i)
{
    int tens_digit = 0;
    int sum = 0;
    for (size_t j = 0; j < MAX_MANTISA_DIGITS + 1; j++)
    {
        sum = product[MAX_MANTISA_DIGITS * 2 - j - i] + buffer[MAX_MANTISA_DIGITS - j] + tens_digit;
        product[MAX_MANTISA_DIGITS * 2 - j - i] = sum % 10;
        tens_digit = sum / 10;
    }
}