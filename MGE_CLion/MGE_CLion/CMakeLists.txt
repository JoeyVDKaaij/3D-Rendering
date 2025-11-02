cmake_minimum_required(VERSION 3.26)
project(MGE_CLion)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SOURCES
        mge/*.h
        mge/*.cpp
)

add_executable(MGE_CLion ${SOURCE_FILES} ${SOURCES}
        glm.hpp main.cpp
        mge/AssignmentsScenes/Assignment2Demo.cpp
        mge/AssignmentsScenes/Assignment2Demo.h
        mge/behaviours/CameraOrbitBehaviour.cpp
        mge/behaviours/MovementBehaviour.cpp
        mge/behaviours/MovementBehaviour.hpp
        mge/AssignmentsScenes/Assignment4Demo.cpp
        mge/AssignmentsScenes/Assignment3Demo.cpp
        mge/Structs/Lighting.cpp
        mge/Structs/Lighting.hpp
        mge/materials/TerrainMaterial.cpp
        mge/materials/TerrainMaterial.hpp
        mge/materials/TerrainMaterial.hpp
        mge/behaviours/RotatingByKeybindsBehaviour.cpp
        mge/behaviours/RotatingByKeyBindsBehaviour.hpp)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(MGE_CLion PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
find_package(GLEW REQUIRED)
target_link_libraries(MGE_CLion PRIVATE GLEW::GLEW)
