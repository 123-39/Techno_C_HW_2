//
// All functions for calculations and work with files
//
#include "func_calculation.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

// Функция записи файла в память
int *read_file_to_memory(const char *file_name, size_t file_size) {
    // Открываем файл
    FILE *ptrFile = NULL;
    ptrFile = fopen(file_name, "rb");
    // Проверка открытия файла
    if (ptrFile == NULL) {
        return NULL;
    }
    // Получаем дескриптор файла
    int df = fileno(ptrFile);
    // Отображаем файл в память
    int *file = mmap(NULL, file_size * sizeof(int), PROT_READ, MAP_FILE | MAP_SHARED, df, 0);
    // Закрываем файл
    fclose(ptrFile);
    return file;
}

// Функция для инициализации массива
void create_file(size_t len, const int upper_bound) {
    // Создаем бинарник для записи элементов массива
    FILE *output = NULL;
    output = fopen("../data.bin", "wb");
    // Элемент массива
    int number;
    // Сохраняем случайность для последовательного и параллельного запуска
    srand(time(NULL));
    // Генерируем случайные числа и записываем в файл
    for (size_t i = 0; i < len; i++) {
        number = rand() % upper_bound;
        fwrite(&number, sizeof(int), 1, output);
    }
    // Перемещает указатель в начало файла
    fseek(output, 0, SEEK_SET);
    // Закрываем файл
    fclose(output);
}

// Функция для вычисления суммы элементов массива
void direct_sum_calculation(int64_t *result, const int *array, size_t len) {
    *result = 0;
    for (size_t k = 0; k < 10 && k < len; ++k) {
        for (size_t i = 0; k + 10 * i < len; ++i) {
            *result += array[k + 10 * i];
        }
    }
}

// Функция для параллельного вычисления суммы элементов массива
void parrallel_sum_calculation(const int *array, size_t num_cores, int64_t *shareable_var, size_t len) {
    // Процесс, на котором будем проводить вычисления
    size_t current_proc = 0;
    // Размер массива для одного процессаDEFAULT_LEN
    size_t size_one_proc = (size_t) (len / num_cores);    // Считаем сумму
    // Уникальный process ID
    int pid;
    // Результат суммирования на каждом процессе
    int64_t result = 0;
    for (const int *short_arr = array; current_proc < num_cores; ++current_proc, short_arr += size_one_proc) {
        // Распараллеливаем
        pid = fork();
        // Для дочернего класса выполняем
        if (pid == 0) {
            // Обновляем размер массива для последнего процесса
            if (current_proc + 1 == num_cores) {
                size_one_proc = len - current_proc * size_one_proc;
            }
            direct_sum_calculation(&result, short_arr, size_one_proc);
            *shareable_var += result;
            exit(EXIT_SUCCESS);
        }
    }
}

// Функция очистки памяти
int clear_mem(int *file, size_t file_size) {
    int flag = munmap(file, file_size);
    if (!flag) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
