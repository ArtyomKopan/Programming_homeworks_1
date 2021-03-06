cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB

        library/commonUtils/numericOperations.c
        library/list/list.c
        library/values/values.c
        )

add_library(library ${SOURCE_LIB})

add_executable(task_1.5 Homework1/task_5.c)

add_executable(task_1.4 Homework1/task_4.c)

add_executable(task_1.1 Homework1/task_1.c)

add_executable(task_1.2 Homework1/task_2.c)

add_executable(task_1.3 Homework1/task_3.c)

add_executable(task_2.2 Homework2/task_2.2.c Homework2/list.c)

add_executable(task_3.3 Homework3/task_3.3.c Homework3/binary_number.c)

add_executable(task_3.2 Homework3/task_3.2.c)

add_executable(task_2.1 Homework2/task_2.1.c Homework2/dictionary.c)

add_executable(test_task_1 Testwork1/test_task_1.c Testwork1/vector.c)

add_executable(test_task_2 Testwork1/test_task_2.c Testwork1/list.c)

add_executable(task_4.1 Homework4/task_4.1.c Homework4/mergeSort.c)

add_executable(task_5.3 Homework5/task_5.3.c)

target_link_libraries(task_5.3 m)

add_executable(task_3.1 Homework3/task_3.1.c Homework3/binary_number.c)

add_executable(task_6.4 Homework6/task_6.4.c Homework6/values.c Homework6/list.c Homework6/dictionary.c Homework6/AVL_tree.c Homework6/hash_map.c)

add_executable(task_6.2 Homework6/task_6.2.c Homework6/values.c Homework6/list.c Homework6/hash_map.c)

add_executable(task_6.1 Homework6/task_6.1.c Homework6/hash_map.c Homework6/values.c Homework6/list.c)

add_executable(task_5.1 Homework5/task_5.1.c Homework5/AVL_tree.c Homework5/values.c)

add_executable(test_task_2.1 Testwork2/test_task_2.1.c)

add_executable(task_5.2 Homework5/task_5.2.c Homework5/AVL_tree.c Homework5/values.c Homework5/list.c)

add_executable(task_7.1 Homework7/task_7.1.c Homework7/heap.c)

add_executable(task_8.2 Homework8/task_8.2.c Homework8/automaton.c Homework8/automaton.h)

target_link_libraries(task_8.2 library)

add_executable(retest_1.3 Retest1/retest_task_1.3.c)

add_executable(final_task_2 Final/final_task_2.c)

add_executable(retest_2.3 Retest2/retest_2.3.c Retest2/AVL_tree.c)
target_link_libraries(retest_2.3 library)

add_executable(retest_2.5 Retest2/retest_2.5.c)
target_link_libraries(retest_2.5 library)
