cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

add_executable(task_1.5 Homework1/task_5.c)

add_executable(task_1.4 Homework1/task_4.c)

add_executable(task_1.1 Homework1/task_1.c)

add_executable(task_1.2 Homework1/task_2.c)

add_executable(task_1.3 Homework1/task_3.c)

add_executable(task_3.3 Homework3/task_3.3.c Homework3/binary_number.c)

add_executable(task_2.1 Homework2/task_2.1.c Homework2/dictionary.c)

add_executable(test_task_1 Testwork1/test_task_1.c Testwork1/vector.c)

add_executable(test_task_2 Testwork1/test_task_2.c Testwork1/list.c)
