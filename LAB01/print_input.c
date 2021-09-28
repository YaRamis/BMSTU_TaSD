#include "print_input.h"

void print_intro()
{
    printf("┏━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━┓\n"
    "┣━━━━━━━━━━┫Умножение двух действительных чисел (вещественных)┣━━━━━━━━━━┫\n"
    "┣━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━┫\n"
    "┃-Формат ввода:                                                          ┃\n"
    "┃   1. Знаки мантисы и порядка вводить не обязательно (по умолчанию '+') ┃\n"
    "┃   2. Можно воодить как с точкой так и без                              ┃\n"
    "┃   3. Можно вводить как 'Е' так и 'е'                                   ┃\n"
    "┃   4. В мантисе должно быть не больше 30-ти цифр                        ┃\n"
    "┃   5. В порядке должно быть не болеше 5-ти цифр                         ┃\n"
    "┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n"
    "┃-Формат вывода:                                                         ┃\n"
    "┃   ±0.{mantisa}E±{order}                                                ┃\n"
    "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n");
}

int input_huge_float(huge_float_t *num)
{
    int rc = 0;
    char num_str[MAX_INPUT_LEN + 2];
    puts("Введите число (снизу ориентир для количества символов)\n"
        " 1        10        20        30 1   5\n"
        "±|--------|---------|---------|E±|---|");
    fgets(num_str, MAX_INPUT_LEN + 1, stdin);
    printf("\n");

    rc = checking_validity(num_str);
    if (rc == EXIT_SUCCESS)
    {
        str_to_huge_float(num_str, num);
        rc = normalize_num(num);
    }

    return rc;
}

void str_to_huge_float(char *str, huge_float_t *num)
{
    if (strchr(str, '\n') != NULL)
        (*strchr(str, '\n')) = '\0';
    char mant_str[MAX_MANTISA_LEN + 1];
    if (is_there_exp(str) == EXIT_SUCCESS)
    {
        char order_str[MAX_ORDER_DIGITS + 2];
        split_by_exp(str, mant_str, order_str);
        sscanf(order_str, "%d", &(num->order));
    }
    else
        strncpy(mant_str, str, MAX_MANTISA_LEN + 1);

    size_t i = 0; // переменная для хранения индекса элемента мантисы в виде строки

    if (mant_str[i] == '+' || mant_str[i] == '-')
    {
        num->sign_m = mant_str[i];
        i++;
    }
    
    int is_there_point = 0;
    size_t j = 0; // переменная для хранения индекса элемента мантисы в структуре
    while (mant_str[i] != '\0')
    {
        if (mant_str[i] == '.')
        {
            is_there_point = 1;
            num->mantisa[j] = POINT;
            i++;
            j++;
            continue;
        }
        num->mantisa[j] = mant_str[i] - '0';
        i++;
        j++;
    }
    if (is_there_point == 0)
        num->mantisa[j] = POINT;
}

void print_result(huge_float_t result_num)
{
    printf("Результат умножения:\n");
    printf("%c0.",result_num.sign_m);
    if (is_num_null(result_num.mantisa) == EXIT_SUCCESS)
        printf("0");
    else
        print_mantisa(result_num.mantisa);
    printf("E");
    if (result_num.order < 0)
        printf("%d\n\n", result_num.order);
    else
        printf("+%d\n\n", result_num.order);
}

void print_mantisa(mantisa_t mantisa)
{
    size_t i = MAX_MANTISA_DIGITS;
    while (mantisa[i] == 0)
        i--;
    for (size_t j = 1; j < i + 1; j++)
        printf("%d", mantisa[j]);
}

void print_error(const int rc)
{
    switch (rc)
    {
        case INPUT_OVERFLOW:
            printf("!Вы ввели слишком длинную строку (больше 39 возможных)!\n"
                "+.123456789012345678901234567890E+99999\n");
            break;
        case TOO_MANY_POINTS:
            printf("!В мантиссе точек больше чем одна!\n");
            break;
        case IS_NOT_NUM_M:
            printf("!Введенная мантисса не является корректной!\n");
            break;
        case IS_NOT_NUM_O:
            printf("!Введенный порядок не является корректным!\n");
            break;
        case TOO_LONG_ORDER:
            printf("!Длина введенного порядка больше 5-ти символов, без учета знака!\n");
            break;
        case TOO_LONG_MANTISA:
            printf("!Длина введенной мантиссы больше 30-ти символов, без учета точки и знака!\n");
            break;
        case ORDER_OVERFLOW:
            printf("!При попытке приведения числа к нормализованному виду\n"
                "переполнился порядок!\n");
            break;
        default:
            break;
    }
}