cmake_minimum_required(VERSION 3.6)
project(projectZapdos)


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
    myHash.cpp
    myHash.h
    Q.cpp
    Q.h
    updateIndex.cpp
    updateIndex.h grail.cpp grail.h component.cpp component.h stronglyConnectedComponents.cpp stronglyConnectedComponents.h stack.cpp stack.h)

add_executable(projectZapdos ${SOURCE_FILES})