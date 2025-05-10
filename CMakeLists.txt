cmake_minimum_required(VERSION 3.31)
project(finm-32700-phase5)

set(CMAKE_CXX_STANDARD 20)

add_executable(finm-32700-phase5 main.cpp
        OrderBook.cpp
        OrderBookTests.cpp
        OptimizedOrderBook.cpp
        OptimizedOrderBookTests.cpp
        Order.hpp)

target_compile_options(finm-32700-phase5 PRIVATE -O2)
