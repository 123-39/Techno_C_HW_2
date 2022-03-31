//
// Tests
//
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include "gtest/gtest.h"

extern "C" {
#include "func_calculation.h"
}

TEST(MMAP_TEST, SUCCESS_READ) {
    size_t test_arr_size = 1000;
    int *test_arr = read_file_to_memory("data_test.bin", test_arr_size);
    EXPECT_TRUE(test_arr != nullptr);
}

TEST(DIRECT_CALC_TEST, SUCCESS_DIRECT_SUM) {
    size_t test_arr_size = 1000;
    int64_t test_result = 0;
    int *test_arr = read_file_to_memory("data_test.bin", test_arr_size);
    direct_sum_calculation(&test_result, test_arr, test_arr_size);
    EXPECT_EQ(test_result, 1000);
}

TEST(PARALLEL_CALC_TEST, SUCCESS_PARALLEL_SUM) {
    size_t test_arr_size = 1000;
    int *test_arr = read_file_to_memory("data_test.bin", test_arr_size);
    int init_pid = getpid();
    size_t num_cores = sysconf(_SC_NPROCESSORS_ONLN);
    auto *test_result = static_cast<int64_t *>
            (mmap(nullptr, sizeof(int), PROT_READ | PROT_WRITE,
                  MAP_SHARED | MAP_ANONYMOUS, -1, 0));
    *test_result = 0;
    parrallel_sum_calculation(test_arr, num_cores, test_result, test_arr_size);
    if (getpid() != init_pid) {
        while (wait(nullptr) > 0) {}
        exit(0);
    }
    while (wait(nullptr) > 0) {}
    EXPECT_EQ(*test_result, 1000);
}

TEST(MMAP_CLEAR_TEST, SUCCESS_CLEAR) {
    size_t test_arr_size = 1000;
    int *test_arr = read_file_to_memory("data_test.bin", test_arr_size);
    int flag = clear_mem(test_arr, test_arr_size);
    EXPECT_EQ(flag, 0);
}

TEST(DIRECT_TEST, SUCCESS_DIRECT) {
    size_t test_arr_size = 1000;
    int *test_arr = read_file_to_memory("data_test.bin", test_arr_size);
    int64_t test_result = calculate_sum(test_arr, test_arr_size);
    EXPECT_EQ(test_result, 1000);
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
