cmake_minimum_required(VERSION 3.8)

project(ItalienQuiSaute)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Tell CMake to use Vcpkg for package management
set(VCPKG_TARGET_TRIPLET "x64-windows-debug")
set(CMAKE_TOOLCHAIN_FILE C:/Users/Lyrym/Desktop/Cours/VCPKG/vcpkg/scripts/buildsystems/vcpkg.cmake)


# Find SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Find CURL
find_package(CURL REQUIRED)

# Find libcurl-simple-https
find_package(libcurl-simple-https REQUIRED)

# Find jsoncpp
find_package(jsoncpp REQUIRED)


# Add source files
set(SOURCES
    ItalienQuiSaute/Component.hpp
    ItalienQuiSaute/Enemy.hpp
    ItalienQuiSaute/Entity.hpp
    ItalienQuiSaute/EntityHealthComponent.hpp
    ItalienQuiSaute/EntityManager.hpp
    ItalienQuiSaute/GameManager.hpp
    ItalienQuiSaute/GravityComponent.hpp
    ItalienQuiSaute/InputManager.hpp
    ItalienQuiSaute/ItalienQuiSaute.cpp
    ItalienQuiSaute/PlayerControllerComponent.hpp
    ItalienQuiSaute/PlayerEntity.hpp
    ItalienQuiSaute/SpriteRendererComponent.hpp
    ItalienQuiSaute/Textures.hpp
    ItalienQuiSaute/TransformComponent.hpp
    ItalienQuiSaute/API/RequestManager.hpp
    ItalienQuiSaute/Assets/Sprites/BlueContainer.png
    ItalienQuiSaute/Assets/Sprites/rat.png
    ItalienQuiSaute/Maths/Vector2.h
)

# Add executable
add_executable(ItalienQuiSaute ${SOURCES})

# Link SFML libraries
target_link_libraries(ItalienQuiSaute sfml-graphics sfml-window sfml-system)

# Link jsoncpp library
target_link_libraries(ItalienQuiSaute jsoncpp)

# Link libcurl-simple-https library
target_link_libraries(ItalienQuiSaute libcurl-simple-https)


