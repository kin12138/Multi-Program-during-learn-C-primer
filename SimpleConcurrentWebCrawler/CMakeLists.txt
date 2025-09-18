cmake_minimum_required(VERSION 3.27)
project(SimpleConcurrentWebCrawler)

set(CMAKE_CXX_STANDARD 17)

# 1. 找到 libcurl
find_package(CURL REQUIRED)

# 2. 包含头文件目录（一般 find_package 自动设置）
include_directories(${CURL_INCLUDE_DIRS})

add_executable(SimpleConcurrentWebCrawler main.cpp
        queue.h
        ThreadPool.h
        UrlDepth.h
        CrawlerController.cpp
        CrawlerController.h
        Fetcher.cpp
        Fetcher.h
        Parser.cpp
        Parser.h)

# 4. 链接 libcurl
target_link_libraries(SimpleConcurrentWebCrawler
        ${CURL_LIBRARIES}
)