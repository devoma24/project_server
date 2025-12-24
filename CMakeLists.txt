cmake_minimum_required(VERSION 3.16)

project(server VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(server src/ClientSession.cpp 
                    src/CommandParser.cpp 
                    src/Logger.cpp 
                    src/main.cpp 
                    src/Server.cpp 
                    src/Socket.cpp 
                    src/Storage.cpp 
                    src/ThreadPool.cpp)

target_include_directories(server
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(server PRIVATE Threads::Threads)

if(WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()

if(MSVC)
    target_compile_options(server PRIVATE /W4 /permissive-)
else()
    target_compile_options(server PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    )
endif()

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_library(server_core
    src/CommandParser.cpp
    src/Storage.cpp
    src/Socket.cpp
    src/ClientSession.cpp
)

target_include_directories(server_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

find_package(Threads REQUIRED)
target_link_libraries(server_core PUBLIC Threads::Threads)