#include "validation.h"

int checking_validity(char *str)
{
    int rc = 0;
    char num_str[MAX_INPUT_LEN + 1];
    strncpy(num_str, str, MAX_INPUT_LEN + 1);

    rc = checking_input_len(num_str);
    if (rc == EXIT_SUCCESS)
    {   
        if (is_there_exp(num_str) == EXIT_SUCCESS)
        {
            char order_str[MAX_ORDER_LEN + 1];
            char mant_str[MAX_MANTISA_LEN + 1];

            rc = split_by_exp(num_str, mant_str, order_str);
            if (rc == EXIT_SUCCESS)
            {
                strcpy(mant_str, num_str);
                rc = checking_mantisa(mant_str);
                if (rc == EXIT_SUCCESS)
                    rc = checking_order(order_str);
            }
        }
        else
            rc = checking_mantisa(num_str);
    }
    return rc;
}

int checking_input_len(char *str)
{
    if (strchr(str, '\n') != NULL)
        (*strchr(str, '\n')) = '\0';
    if (strlen(str) > MAX_INPUT_LEN)
        return INPUT_OVERFLOW;
    return EXIT_SUCCESS;
}

int is_there_exp(char *str) // проверка наличия 'Е' или 'е'
{
    if (strchr(str, 'E') == NULL)
    {    
        if (strchr(str, 'e') == NULL)
            return EXIT_FAILURE;
        (*strchr(str, 'e')) = 'E';
    }
    return EXIT_SUCCESS;
}

int split_by_exp(char *num_str, char *mant_str, char *order_str)
{
    if (num_str[0] == 'E')
        return IS_NOT_NUM_M;
    strcpy(mant_str, strtok(num_str, "E"));
    strcpy(order_str, strtok(NULL, "E"));
    return EXIT_SUCCESS;
}

int checking_mantisa(char *mant_str)
{
    int rc = 0;
    
    rc = checking_for_point(mant_str);
    if (rc == EXIT_SUCCESS)
    {
        rc = my_is_num(mant_str);
        if (rc == EXIT_SUCCESS)
            rc = checking_mantisa_len(mant_str);
    }
    return rc;
}

int checking_mantisa_len(char *str)
{
    int count_of_not_digits = 0;
    size_t i = 0;

    if (str[i] == '+' || str[i] == '-')
        count_of_not_digits++;
    if (strchr(str, '.') != NULL)
        count_of_not_digits++;

    if (strlen(str) - count_of_not_digits > MAX_MANTISA_DIGITS)
        return TOO_LONG_MANTISA;

    return EXIT_SUCCESS;
}

int checking_for_point(char *str)
{
    if (strchr(str, '.') != NULL)
        if (strchr(str, '.') != strrchr(str, '.'))
            return TOO_MANY_POINTS;

    return EXIT_SUCCESS;
}

int my_is_num(char *str)
{
    size_t i = 0;
    int has_digit = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    
    while (str[i] != '\0')
    {
        if (isdigit(str[i]) != 0)
            has_digit = 1;
        if (isdigit(str[i]) == 0 && str[i] != '.')
            return IS_NOT_NUM_M;
        i++;
    }
    if (has_digit == 0)
        return IS_NOT_NUM_M;
    return EXIT_SUCCESS;
}

int checking_order(char *order_str)
{
    int is_sign = 0;
    size_t i = 0;

    if (order_str[i] == '+' || order_str[i] == '-')
    {
        is_sign++;
        i++;
    }

    if (strlen(order_str) - is_sign > MAX_ORDER_DIGITS)
        return TOO_LONG_ORDER;
    
    int temp_order_to_check = 0;

    while (order_str[i] != '\0')
    {
        if (isdigit(order_str[i]) == 0)
            return IS_NOT_NUM_O;
        i++;
    }
    
    if (sscanf(order_str, "%d", &temp_order_to_check) != 1)
        return IS_NOT_NUM_O;

    return EXIT_SUCCESS;
}