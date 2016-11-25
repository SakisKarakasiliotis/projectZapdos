cmake_minimum_required(VERSION 3.6)
project(projectZapdosClion)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    bfs.cpp
    bfs.h
    buffer.cpp
    buffer.h
    defines.h
    index.cpp
    index.h
    list_node.cpp
    list_node.h
    main.cpp
    my_hash.cpp
    my_hash.h
    Q.cpp
    Q.h)

add_executable(projectZapdosClion ${SOURCE_FILES})