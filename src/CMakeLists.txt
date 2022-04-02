# Пакет без которого все крашится
find_package (Threads REQUIRED)
add_compile_options(-pthread)

# Обработка ворнингов
add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

# Поиск файлов в директории include
include_directories("../include")

# Библиотека с общими функциями
set(COMMON_LIB_SOURCE func_calculation.c)
# Библиотека с последовательной реализацией
set(STATIC_LIB_SOURCE ${COMMON_LIB_SOURCE} direct_calculation.c)
# Библиотека с параллельной реализацией
set(SHARED_LIB_SOURCE ${COMMON_LIB_SOURCE} parallel_calculation.c)

# Cоздание статической библиотеки
add_library(sum_calc_lib_static STATIC ${STATIC_LIB_SOURCE})
# Cоздание динамической библиотеки
add_library(sum_calc_lib_shared SHARED ${SHARED_LIB_SOURCE})

# Создание бинарников
add_executable(main_static main.c)
add_executable(main_shared main.c)

# Соединение библиотеки и основного бинарного файла
target_link_libraries(main_static sum_calc_lib_static pthread)
target_link_libraries(main_shared sum_calc_lib_shared pthread)
