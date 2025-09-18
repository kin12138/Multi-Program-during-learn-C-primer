cmake_minimum_required(VERSION 3.27)
project(MultithreadingPractice)

set(CMAKE_CXX_STANDARD 17)

add_executable(MultithreadingPractice main.cpp
        ThreadBasics.h
        TaskQueue.cpp
        TaskQueue.h
        Scoped_Thread.h
        Accumulate.h
        ThreadSafe_Stack.cpp
        ThreadSafe_Stack.h
        hierarchical_mutex.h
        threadsafe_queue.cpp
        threadsafe_queue.h
        Quick_sort.h
        Parallel_merge_sort.h)
