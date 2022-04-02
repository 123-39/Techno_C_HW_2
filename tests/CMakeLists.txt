# Пакет без которого все крашится
find_package (Threads REQUIRED)

# Обработка ворнингов
add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

# Поиск файлов в директории include и src
include_directories("../include")
include_directories("../src")

# Подключение тестирования
enable_testing()

# Загрузка гугловской библиотеки тестов
find_package(GTest REQUIRED)
# Поиск тестов
include_directories(${GTEST_INCLUDE_DIRS})

# Создаем исполняемый файл для статической библиотеки и последовательной реализации
add_executable(test_static test.cpp)
# Создаем исполняемый файл для динамической библиотеки и параллельной реализации
add_executable(test_shared test.cpp)

# Линкуем программу со статической библиотекой
target_link_libraries(test_static ${GTEST_LIBRARIES} sum_calc_lib_static pthread)
# Линкуем программу с динамической библиотекой
target_link_libraries(test_shared ${GTEST_LIBRARIES} sum_calc_lib_shared pthread)