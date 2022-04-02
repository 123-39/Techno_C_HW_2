//
// Parallel calculation of the sum of array elements
//

#include "func_calculation.h"

// Параллельный подсчет суммы
int64_t calculate_sum(int *file, size_t len) {
    // pid процесса, порождающего группу
    int init_pid = getpid();
    // Количество доступных ядер
    size_t num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    // Результат суммирования (шарим память для процессов)
    int64_t *result_parallel = mmap(NULL, sizeof(int),
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *result_parallel = 0;
    parrallel_sum_calculation(file, num_cores, result_parallel, len);
    // Проверка на родительский процесс
    // Ждем закрытия всех дочерних процессов
    if (getpid() != init_pid) {
        while (wait(NULL) > 0) {}
        exit(EXIT_SUCCESS);
    }
    while (wait(NULL) > 0) {}
    // Выводим результат
    return *result_parallel;
}
