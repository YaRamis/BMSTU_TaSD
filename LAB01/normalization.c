#include "my_utils.h"
#include "validation.h"
#include "normalization.h"

short normalize_num(char *num_str, short *mant, int *order, char *sign_m)
{
    mantisa_t mant_temp;
    int order_temp;
    char sign_m_temp;
    char mant_temp_str[MAX_MANTISA_LEN + 1];
    
    if (is_there_exp(num_str) == EXIT_SUCCESS)
    {
        char order_temp_str[MAX_ORDER_LEN + 1];
        split_by_exp(num_str, mant_temp_str, order_temp_str);
        sscanf(order_temp_str, "%d", &order_temp);
    }
    else
    {
        strncpy(mant_temp_str, num_str, MAX_MANTISA_LEN + 1);
        order_temp = 0;
    }

    int extra_order = 0;
    normalize_mant(mant_temp_str, mant_temp, &sign_m_temp);
    // add_extra_order();

    return EXIT_SUCCESS;
}

void normalize_mant(char *mant_temp_str, mantisa_t *mant_temp, char *sign_m_temp)
{

}