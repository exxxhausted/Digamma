cmake_minimum_required(VERSION 3.28)
project(Digamma)

set(CMAKE_CXX_STANDARD 20)

add_executable(Digamma main.cpp
        src/geometry/kernel/Surface.cpp
        src/geometry/kernel/Body.cpp
        src/geometry/factories/SurfaceFactory.cpp)

target_include_directories(Digamma PRIVATE ./third_party/libigl/include
                                           ./include
                                           ./third_party/eigen)