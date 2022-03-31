//
// Main part of the program
//

#include <stdio.h>
#include <time.h>
#include "func_calculation.h"


int main() {
    //==========================================Создание файла==============================================//
//     Создаем текстовый файл
//    create_file(DEFAULT_LEN, DEFAULT_UP_BOUND);
    //=======================================Отображение в память===========================================//
    const char *file_name = "../data.bin";
    int *array = read_file_to_memory(file_name, DEFAULT_LEN);
    if (!array) {
        return EXIT_FAILURE;
    }
    //============================================Реализация ===============================================//
    clock_t begin = clock();
    // Результат суммирования
    int64_t result = calculate_sum(array, DEFAULT_LEN);
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("Result: %li\n", result);
    printf("Time: %lf с\n", time_spent);
    return 0;
}
