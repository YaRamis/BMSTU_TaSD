#include "my_utils.h"
#include "print_input.h"
#include "validation.h"

void print_intro()
{
    printf("MULTIPLY NUMBER TO NUMBER\n))))^-^((((\n");
}

short input_huge_float(char *str)
{
    short rc = 0;
    char num_str[MAX_MANTISA_LEN];
    gets(num_str);

    rc = checking_validity(num_str);
    if (rc == EXIT_SUCCESS)
    {
        normalization();
    }

    return rc;
}

void print_error(const short rc)
{
    switch (rc)
    {
        case INPUT_OVERFLOW:
            printf("Вы ввели слишком длинную строку (больше 38 возможных)\n"
                "+123456789012345678901234567890E+99999\n");
            break;
        case TOO_MANY_POINTS:
            printf("В мантисе точек больше чем одна\n");
            break;
        case IS_NOT_NUM_M:
            printf("Введенная мантиса не является корректной\n");
            break;
        case IS_NOT_NUM_O:
            printf("Введенный порядок не является корректным\n");
            break;
        case TOO_LONG_ORDER:
            printf("Длина введенного порядка больше 5-ти символов, без учета знака\n");
            break;
        case TOO_LONG_MANTISA:
            printf("Длина введенной мантисы больше 30-ти символов, без учета точки и знака\n");
        default:
            break;
    }
}