cmake_minimum_required(VERSION 2.8)

project(Caches)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wconversion -Wsizeof-pointer-memaccess \
                     -Wfloat-equal -Wconversion-null -Woverflow -Wshadow \
                     -D_FILE_OFFSET_BITS=64 -D_GNU_SOURCE -pthread -g -O3")

include_directories(src test)

add_executable(Example
        src/CacheBase.h
        src/CacheMD5.cpp src/CacheMD5.h
        src/CacheFIFO.cpp src/CacheFIFO.h
        src/CacheLRU.cpp src/CacheLRU.h
        src/CacheLFU.cpp src/CacheLFU.h
        src/CacheQ2.cpp src/CacheQ2.h
        src/CacheMgr.cpp src/CacheMgr.h
        test/Example.cpp)

add_executable(Generator
        test/Generator.cpp
        src/CacheMD5.cpp
        src/CacheMD5.h)