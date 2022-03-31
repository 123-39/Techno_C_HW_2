//
// Direct calculation of the sum of array elements
//

#include <sys/mman.h>
#include "func_calculation.h"

// Прямой подсчет суммы
int64_t calculate_sum(int *file, size_t len) {
    int64_t result_direct = 0;
    // Считаем
    direct_sum_calculation(&result_direct, file, len);
    // Очищаем память
    clear_mem(file, len * sizeof(int));
    return result_direct;
}

