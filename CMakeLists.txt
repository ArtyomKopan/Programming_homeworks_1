cmake_minimum_required(VERSION 3.17)
project(spbu_c_homeworks C)

set(CMAKE_C_STANDARD 11)

set(SOURCE_LIB
    library/commonUtils/numericOperations.c
)
add_library(library ${SOURCE_LIB})

<<<<<<< HEAD
add_executable(task_1.2 Homework1/task_2.c)
=======
add_executable(task_1.3 Homework1/task_3.c)
>>>>>>> 95038a0f0cf4c5cd5c4667f3905abbf8cfe1cb9c
