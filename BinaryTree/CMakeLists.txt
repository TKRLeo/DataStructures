cmake_minimum_required(VERSION 3.22)
project(ProjectCPP)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_HEADERS
        Tree.h
        )
set(PROJECT_SOURCE
        main.cpp
        )
add_executable(ProjectCPP ${PROJECT_SOURCE} ${PROJECT_HEADERS})