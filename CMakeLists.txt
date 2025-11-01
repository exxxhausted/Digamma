cmake_minimum_required(VERSION 3.28)
project(Digamma)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(eigen
        URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
)
FetchContent_Declare(nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip
)
FetchContent_Declare(exprtk
        GIT_REPOSITORY https://github.com/ArashPartow/exprtk.git
        GIT_TAG master
)

FetchContent_MakeAvailable(eigen nlohmann_json exprtk)

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
        src/geometry/kernel/Ray.cpp
        src/io/writeOBJ.cpp
        src/physics/Objects/DGObject.cpp
        src/physics/entities/Photon.cpp
        src/physics/objects/Detector.cpp
        src/physics/objects/RadiationSource.cpp
        src/geometry/intersection/AccelerationCache.cpp
        src/geometry/intersection/IntersectionResult.cpp
)

target_compile_options(Digamma PRIVATE /bigobj)

target_include_directories(Digamma PRIVATE ./include
        ${eigen_SOURCE_DIR}
        ${nlohmann_json_SOURCE_DIR}/include
        ${exprtk_SOURCE_DIR}
        ./third_party/embree/include
        ./third_party/libigl/include)


target_link_directories(Digamma PRIVATE ./third_party/embree/lib)
target_link_libraries(Digamma PRIVATE embree4)