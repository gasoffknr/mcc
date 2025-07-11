cmake_minimum_required(VERSION 3.30)
project(minecraftremake)

set(CMAKE_CXX_STANDARD 17)

# GLFW - Désactiver les exemples/tests pour aller plus vite
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)

# GLAD - Compiler le source
add_library(glad libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# GLM - Header-only
add_subdirectory(libs/glm)

# STB - Header-only, juste les includes
set(STB_INCLUDE_DIR libs/stb)

# Ton exécutable
add_executable(minecraftremake
        src/main.cpp
        src/core/Window.class.cpp
        src/core/Application.class.cpp
        src/renderer/Shader.class.cpp
        src/renderer/Camera.class.cpp
)

# Inclure le dossier src pour les headers
target_include_directories(minecraftremake PRIVATE src)

# Lier toutes les libs
target_link_libraries(minecraftremake
        glfw
        glad
        glm::glm
        ${CMAKE_DL_LIBS}  # Pour dlopen sur Linux
)

# Inclure STB
target_include_directories(minecraftremake PRIVATE ${STB_INCLUDE_DIR})

# OpenGL (système)
find_package(OpenGL REQUIRED)
target_link_libraries(minecraftremake OpenGL::GL)