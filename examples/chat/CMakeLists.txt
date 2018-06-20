cmake_minimum_required(VERSION 2.8)
include_directories("/usr/local/include")

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

project(chat)
add_executable(${PROJECT_NAME} "main.cpp" "person.cpp" "chat.cpp" "chatlistener.cpp")
target_link_libraries (${PROJECT_NAME} LINK_PUBLIC pthread dinemic )
