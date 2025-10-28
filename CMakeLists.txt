cmake_minimum_required(VERSION 3.28)
project(Digamma)

set(CMAKE_CXX_STANDARD 20)

add_executable(Digamma main.cpp
        src/geometry/kernel/Surface.cpp
        src/geometry/kernel/Body.cpp
        src/geometry/factories/SurfaceFactory.cpp
        src/physics/material/Atom.cpp
        src/io/AtomLoader.cpp
        src/physics/material/Molecule.cpp
        src/io/MoleculeLoader.cpp
        src/io/MaterialLoader.cpp
        src/physics/material/Material.cpp
)

target_compile_options(Digamma PRIVATE /bigobj)

target_include_directories(Digamma PRIVATE ./third_party/libigl/include
                                           ./include
                                           ./third_party/eigen
                                           ./third_party/nlohmann_json/include
                                           ./third_party/exprtk)