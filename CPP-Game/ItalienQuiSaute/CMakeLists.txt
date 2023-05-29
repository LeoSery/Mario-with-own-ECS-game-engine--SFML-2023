cmake_minimum_required(VERSION 3.8)

project(ItalienQuiSaute)

# Set C++ version
set(CMAKE_CXX_STANDARD 20)

# Tell CMake to use Vcpkg for package management
set(VCPKG_TARGET_TRIPLET "x64-windows-debug")
set(CMAKE_TOOLCHAIN_FILE D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake)

set(SFML_DIR D:/vcpkg/vcpkg/installed/x64-windows/share/sfml)
set(CURL_INCLUDE_DIR D:/vcpkg/vcpkg/installed/x64-windows/share/curl)
set(libcurl-simple-https_DIR D:/vcpkg/vcpkg/installed/x64-windows/share/libcurl-simple-https)
set(jsoncpp_DIR D:/vcpkg/vcpkg/installed/x64-windows/share/jsoncpp)

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
    Game/Source/FileReader.hpp
    Game/Source/GameManager.hpp
    Game/Source/ItalienQuiSaute.cpp
    Game/Source/Level.hpp
    Game/Source/Menu.hpp
    
    Engine/API/RequestManager.hpp
    
    Engine/Components/CameraComponent.hpp
    Engine/Components/ColliderComponent.hpp
    Engine/Components/Component.hpp
    Engine/Components/GravityComponent.hpp
    Engine/Components/HealthComponent.hpp
    Engine/Components/PlayerControllerComponent.hpp
    Engine/Components/PlayerStateComponent.hpp
    Engine/Components/SpriteRendererComponent.hpp
    Engine/Components/TransformComponent.hpp
    
    Engine/Entities/Background.hpp
    Engine/Entities/Enemy.hpp
    Engine/Entities/Entity.hpp
    Engine/Entities/Flag.hpp
    Engine/Entities/GameObject.hpp
    Engine/Entities/PlayerEntity.hpp
    
    Engine/System/Libraries/Maths/Vector2.h
    
    Engine/System/Managers/AnimationsManager.hpp
    Engine/System/Managers/EntityManager.hpp
    Engine/System/Managers/InputManager.hpp
    Engine/System/Managers/TexturesManager.hpp
)

# Add executable
add_executable(ItalienQuiSaute ${SOURCES})

# Link SFML libraries
target_link_libraries(ItalienQuiSaute sfml-graphics sfml-window sfml-system)

# Link jsoncpp library
target_link_libraries(ItalienQuiSaute jsoncpp)

# Link libcurl-simple-https library
target_link_libraries(ItalienQuiSaute libcurl-simple-https)


