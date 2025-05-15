cmake_minimum_required(VERSION 3.27)
project(Query_Test)

set(CMAKE_CXX_STANDARD 11)

add_executable(Query_Test main.cpp
        TextQuery.cpp
        TextQuery.h
        QueryResult.cpp
        QueryResult.h
        Query_base.h
        Query.cpp
        Query.h
        WordQuery.cpp
        WordQuery.h
        NotQuery.cpp
        NotQuery.h
        BinaryQuery.h
        AndQuery.cpp
        AndQuery.h
        OrQuery.cpp
        OrQuery.h
        QueryTest.h)
