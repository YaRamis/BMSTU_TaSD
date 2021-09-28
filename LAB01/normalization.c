#include "normalization.h"

int normalize_num(huge_float_t *num)
{
    remove_first_nulls(num->mantisa);

    move_point(num);
    
    return EXIT_SUCCESS;
}

void remove_first_nulls(int *arr)
{
    size_t nulls_count = 0;
    while (arr[nulls_count] == 0)
        nulls_count++;

    shift_arr_left(arr, nulls_count, 0, MAX_MANTISA_DIGITS * 2);
}

void shift_arr_left(int *arr, int n, int start, int end)
{
    for (int i = 0; i < n; i++)
    {
        if (i == 1 && end >= MAX_MANTISA_DIGITS + 1)
            arr[end] = 0;
        for (int j = start; j < end; j++)
            arr[j] = arr[j + 1];
    }
}

void shift_arr_right(int *arr, int n, int start, int end)
{
    for (int i = 0; i < n; i++)
    {
        if (i == 1 && start == 0)
            arr[start] = 0;
        for (int j = end; j > start; j--)
            arr[j] = arr[j - 1];
    }
}

void move_point(huge_float_t *num)
{
    int i = 0;

    if (num->mantisa[i] == POINT)
    {
        i++;
        while (num->mantisa[i] == 0)
            i++;
        num->order -= (i - 1);
        shift_arr_left(num->mantisa, i - 1, 1, MAX_MANTISA_DIGITS * 2);
    }
    else
    {
        for (i = 0; i < MAX_MANTISA_DIGITS + 1; i++)
            if (num->mantisa[i] == POINT)
            {
                shift_arr_left(num->mantisa, 1, i, MAX_MANTISA_DIGITS + 1);
                break;
            }
        num->order += i;
        shift_arr_right(num->mantisa, 1, 0, MAX_MANTISA_DIGITS + 1);
        num->mantisa[0] = POINT;
    }
}

void round_product(huge_float_t *num)
{
    int tens_digit = 1;
    int sum = 0;
    for (size_t i = MAX_MANTISA_DIGITS; i > 0; i--)
    {
        sum = num->mantisa[i] + tens_digit;
        num->mantisa[i] = sum % 10;
        tens_digit = sum / 10;
        if (tens_digit == 0)
            break;
    }
    if (tens_digit != 0)
    {
        shift_arr_right(num->mantisa, 1, 0, MAX_MANTISA_DIGITS);
        num->order++;
    }
}