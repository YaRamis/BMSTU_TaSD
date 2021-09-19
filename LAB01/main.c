#include "my_utils.h" // Заголовочник с общими константами, типами, библиотеками
#include "print_input.h" // Заголовочник с функциями ввода и вывода
#include "multiply.h" // Заголовочник с функциями для выолнения умножения над двумя числами

int main(void)
{
    setbuf(stdout, NULL); // Отключаю буферизацию

    print_intro(); // Вывод информации для пользователя: что делает программа, правила ввода и т.д.

    huge_float_t first_num; // Объявление первого числа
    huge_float_t second_num; // Объявление второго числа
    huge_float_t result_num; // Объявление переменной для хранения результата действий над двумя числами
    short rc = 0; // Переменная для хранения кода возврата

    rc = input_huge_float(first_num); // Пользовательский ввод первого числа
    if (rc == EXIT_SUCCESS)
    {
        rc = input_huge_float(second_num); // Пользовательский ввод второго числа
        if (rc == EXIT_SUCCESS)
        {
            rc = multiply(first_num, second_num, result_num); // Умножение введенных чисел, получение и запись результата в переменную
            if (rc == EXIT_SUCCESS)
                print_result(result_num); // Вывод результата умножения двух чисел
        }
    }
    print_error(rc); // Вывод ошибки, если она была
    return rc; // Завершение программы с кодом возврата
}