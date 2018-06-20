cmake_minimum_required (VERSION 2.8.11)
project(DINEMIC)

add_definitions(-DDINEMIC_BUILD)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE Debug)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static-libc -static")

include_directories( BEFORE ../include/ )
link_directories( /usr/lib/x86_64-linux-gnu/ /usr/local/lib/ /usr/local/Cellar/boost/1.60.0_2/lib/ /usr/local/Cellar/hiredis/0.13.3/lib/ /usr/local/Cellar/libevent/2.0.22/lib/ /usr/local/Cellar/zeromq/4.1.4/lib/ /usr/local/Cellar/libsodium/1.0.12/lib/ )

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libc")
add_library(libboost_regex STATIC IMPORTED)
SET_TARGET_PROPERTIES(libboost_regex PROPERTIES IMPORTED_LOCATION ../lib/libboost_regex.a)

add_library(libboost_filesystem STATIC IMPORTED)
SET_TARGET_PROPERTIES(libboost_filesystem PROPERTIES IMPORTED_LOCATION ../lib/libboost_filesystem.a)

add_library(libboost_system STATIC IMPORTED)
SET_TARGET_PROPERTIES(libboost_system PROPERTIES IMPORTED_LOCATION ../lib/libboost_system.a)

add_library(libboost_chrono STATIC IMPORTED)
SET_TARGET_PROPERTIES(libboost_chrono PROPERTIES IMPORTED_LOCATION ../lib/libboost_chrono.a)

add_library(libboost_iostreams STATIC IMPORTED)
SET_TARGET_PROPERTIES(libboost_iostreams PROPERTIES IMPORTED_LOCATION ../lib/libboost_iostreams.a)

add_library(libhiredis STATIC IMPORTED)
SET_TARGET_PROPERTIES(libhiredis PROPERTIES IMPORTED_LOCATION ../lib/libhiredis.a)

add_library(libzmq STATIC IMPORTED)
SET_TARGET_PROPERTIES(libzmq PROPERTIES IMPORTED_LOCATION ../lib/libzmq.a)

add_library(libsodium STATIC IMPORTED)
SET_TARGET_PROPERTIES(libsodium PROPERTIES IMPORTED_LOCATION ../lib/libsodium.a)

add_library(libevent STATIC IMPORTED)
SET_TARGET_PROPERTIES(libevent PROPERTIES IMPORTED_LOCATION ../lib/libevent.a)

# libc-pic
add_library(libc STATIC IMPORTED)
SET_TARGET_PROPERTIES(libc PROPERTIES IMPORTED_LOCATION ../lib/libc_nonshared.a)

add_library(libm STATIC IMPORTED)
SET_TARGET_PROPERTIES(libm PROPERTIES IMPORTED_LOCATION ../lib/libm.a)

# libstdc++-5-pic
add_library(libstdc++ STATIC IMPORTED)
SET_TARGET_PROPERTIES(libstdc++ PROPERTIES IMPORTED_LOCATION /usr/lib/gcc/x86_64-linux-gnu/5/libstdc++_pic.a)


file(GLOB dinemic_src
    "*.cpp"
    "*/*.cpp"
)

add_library(dinemic SHARED ${dinemic_src})
target_include_directories(dinemic PUBLIC ../ /usr/local/include/ /usr/local/Cellar/hiredis/0.13.3/include/ /usr/local/Cellar/boost/1.60.0_2/include/ /usr/local/Cellar/libevent/2.0.22/include/ )
target_link_libraries (dinemic libboost_chrono libboost_regex libboost_filesystem libboost_system libevent libzmq libsodium libhiredis )

add_library(dinemicstatic STATIC ${dinemic_src})
target_include_directories(dinemicstatic PUBLIC ../ /usr/local/include/ /usr/local/Cellar/hiredis/0.13.3/include/ /usr/local/Cellar/boost/1.60.0_2/include/ /usr/local/Cellar/libevent/2.0.22/include/ )
target_link_libraries (dinemicstatic libboost_chrono libboost_regex libboost_filesystem libboost_system libevent libzmq libsodium libhiredis )
