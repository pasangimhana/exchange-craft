cmake_minimum_required(VERSION 3.16)
project(exchange_craft)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(exchange_craft
        CSVProcessor.cpp
        CSVProcessor.h
        ExchangeCore.cpp
        ExchangeCore.h
        main.cpp
        Order.cpp
        Order.h
        OrderTypeConverter.cpp
        OrderTypeConverter.h)
