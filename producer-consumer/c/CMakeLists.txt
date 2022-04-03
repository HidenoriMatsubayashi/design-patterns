cmake_minimum_required(VERSION 3.10)

project("producer-consumer" LANGUAGES C)

find_package(Threads REQUIRED)

set(TARGET "producer-consumer")
add_executable(${TARGET} "main.c" "queue.c")
target_include_directories(${TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(${TARGET} PRIVATE Threads::Threads)
