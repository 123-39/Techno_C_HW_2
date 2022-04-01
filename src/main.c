//
// Main part of the program
//

#include <stdio.h>
#include <time.h>
#include "func_calculation.h"

#define LAUNCH_COUNT 4
#define NANO_SEC_CONVERT 1000000000


int main() {
    // ======================Отображение в память=================== //
    const char *file_name = "../data.bin";
    int *array = read_file_to_memory(file_name, DEFAULT_LEN);
    if (!array) {
        return EXIT_FAILURE;
    }
    // ==========================Реализация ======================== //
    struct timespec start, finish;
    int64_t result = 0;

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < LAUNCH_COUNT; ++i) {
        // Результат суммирования (одинаковый заголовок для обоих реализаций)
        result = calculate_sum(array, DEFAULT_LEN);
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);

    // Считаем затраченное время
    double time_spent = ((double)(finish.tv_sec - start.tv_sec) +
            (double)(finish.tv_nsec - start.tv_nsec) / NANO_SEC_CONVERT)
                    / LAUNCH_COUNT;
    // Очищаем память
    clear_mem(array, DEFAULT_LEN * sizeof(int));
    printf("Result: %li\n", result);
    printf("Time: %lf с\n", time_spent);
    return 0;
}
