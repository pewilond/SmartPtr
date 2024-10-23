cmake_minimum_required(VERSION 3.16)
project(lab1_3)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)

add_executable(lab1_3
        main.cpp
        interface.cpp
        test.cpp
#        displayCharts.cpp
        DynamicArray.h
        DynamicArraySmart.h
        LinkedList.h
        LinkedListSmart.h
        Sequence.h
        ShrdPtr.h
        UnqPtr.h
        test.h
#        displayCharts.h
        interface.h
)

target_link_libraries(lab1_3 Qt6::Widgets Qt6::Charts)
