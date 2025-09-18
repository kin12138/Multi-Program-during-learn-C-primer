cmake_minimum_required(VERSION 3.27)
project(DataStructure)

set(CMAKE_CXX_STANDARD 17)

add_executable(DataStructure main.cpp
        AdjacencyList.h
        SinglyLinkedList.h
        test.h
        DoubleLinkedList.h
        CircularLinkedList.h
        SequenceStack.h
        LinkedStack.h
        PracticeOfStack.h
        SequenceQueue.h
        LinkedQueue.h
        String.h)
