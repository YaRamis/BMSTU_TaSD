#include "my_utils.h"
#include "validation.h"

short checking_validity(char *num_str)
{
    short rc = 0;

    rc = checking_input_len(num_str);
    if (rc == EXIT_SUCCESS)
    {
        if (is_there_exp(num_str) == EXIT_SUCCESS)
        {
            char mant_str[MAX_MANTISA_LEN + 1];
            char order_str[MAX_ORDER_LEN + 1];

            split_by_exp(num_str, mant_str, order_str);
            rc = checking_mantisa(mant_str);
            if (rc == EXIT_SUCCESS)
                rc = checking_order(order_str);
        }
        else
        {
            rc = checking_mantisa(num_str);
        }
    }
    return rc;
}

short checking_input_len(char *str)
{
    if (strchr(str, '\n') != NULL)
        *strchr(str, '\n') == '\0';
    if (strlen(str) >= MAX_INPUT_LEN)
        return INPUT_OVERFLOW;
    return EXIT_SUCCESS;
}

short is_there_exp(char *str)
{
    if (strchr(str, 'E') == NULL)
    {    
        if (strchr(str, 'e') == NULL)
            return EXIT_FAILURE;
        *strchr(str, 'e') = 'E';
    }
    return EXIT_SUCCESS;
}

void split_by_exp(char *num_str, char *mant_str, char *order_str)
{
    mant_str = strtok(num_str, "E");
    order_str = strtok(NULL, "E");
}

short checking_mantisa(char *mant_str)
{
    short rc = 0;
    
    rc = checking_for_point(mant_str);
    if (rc == EXIT_SUCCESS)
    {
        rc = my_is_num(mant_str);
        if (rc == EXIT_SUCCESS)
            rc = checking_mantisa_len(mant_str);
    }
    return rc;
}

short checking_mantisa_len(char *str)
{
    short count_of_not_digits = 0;
    size_t first_elem = 0;

    if (str[first_elem] == '+' || str[first_elem] == '=')
        count_of_not_digits++;
    if (strchr(str, '.') != NULL)
        count_of_not_digits++;

    if (strlen(str) > MAX_MANTISA_LEN - count_of_not_digits)
        return TOO_LONG_MANTISA;

    return EXIT_SUCCESS;
}

short checking_for_point(char *str)
{
    if (strchr(str, '.') != NULL)
        if (strchr(str, '.') != strrchr(str, '.'))
            return TOO_MANY_POINTS;

    return EXIT_SUCCESS;
}

short my_is_num(char *str)
{
    size_t i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    
    while (str[i] != '\0')
    {
        if (isdigit(str[i]) != 0 && str[i] != '.')
            return IS_NOT_NUM_M;
        i++;
    }
    return EXIT_SUCCESS;
}

short checking_order(char *order_str)
{
    short is_sign = 0;
    size_t first_elem = 0;

    if (order_str[first_elem] == '+' || order_str[first_elem] == '-')
        is_sign++;

    if (strlen(order_str) > MAX_ORDER_LEN - is_sign)
        return TOO_LONG_ORDER;
    
    int temp_order_to_check = 0;

    if (sscanf(order_str, "%d", &temp_order_to_check) != 1)
        return IS_NOT_NUM_O;

    return EXIT_SUCCESS;
}