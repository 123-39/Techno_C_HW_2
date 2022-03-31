//
// Library
//

#ifndef INCLUDE_FUNC_CALCULATION_H_
#define INCLUDE_FUNC_CALCULATION_H_

#include <stdlib.h>

#define DEFAULT_LEN 100000000
#define DEFAULT_UP_BOUND 10

// Функция для инициализации массива
void create_file(size_t len, int upper_bound);

// Функция записи файла в память
int *read_file_to_memory(const char *file_name, size_t file_size);

// Функция для вычисления суммы элементов
void direct_sum_calculation(int64_t *result, const int *array, size_t len);

// Функция для параллельного вычисления суммы элементов массива
void parrallel_sum_calculation(const int *array, size_t num_cores,
                               int64_t *shareable_var, size_t len);

// Параллельный подсчет суммы
int64_t calculate_sum(int *file, size_t len);

// Функция очистки памяти
int clear_mem(int *file, size_t file_size);


#endif  // INCLUDE_FUNC_CALCULATION_H_
